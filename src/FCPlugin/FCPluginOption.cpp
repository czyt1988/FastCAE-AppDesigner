#include "FCPluginOption.h"
#include <QObject>
#include <QLibrary>
#include <memory>
class FCPluginOptionPrivate {
    FC_IMPL_PUBLIC(FCPluginOption)
public:
    FCPluginOptionPrivate(FCPluginOption *p);
    FP_PluginGetIID _fpGetIID = { nullptr };
    FP_PluginGetName _fpGetName = { nullptr };
    FP_PluginGetVersion _fpGetVersion = { nullptr };
    FP_PluginGetDescription _fpGetDescription = { nullptr };
    FP_PluginCreate _fpCreate = { nullptr };
    FP_PluginDestory _fpDestory = { nullptr };
    FCAbstractPlugin *_plugin = { nullptr };
    std::shared_ptr<QLibrary> _lib;
};

FCPluginOptionPrivate::FCPluginOptionPrivate(FCPluginOption *p) : q_ptr(p)
{
}


FCPluginOption::FCPluginOption() : d_ptr(new FCPluginOptionPrivate(this))
{
    d_ptr->_lib.reset(new QLibrary);
}


/**
 * @brief 复制构造函数
 *
 * 这时候会共享QLibrary的内存
 * @param other
 */
FCPluginOption::FCPluginOption(const FCPluginOption& other)
{
    d_ptr.reset(new FCPluginOptionPrivate(this));
    (*d_ptr) = *(other.d_ptr);
}


FCPluginOption::FCPluginOption(FCPluginOption&& other)
{
    d_ptr.reset(other.d_ptr.take());
}


FCPluginOption& FCPluginOption::operator =(const FCPluginOption& other)
{
    if (d_ptr.isNull()) {
        d_ptr.reset(new FCPluginOptionPrivate(this));
    }
    (*d_ptr) = *(other.d_ptr);
    return (*this);
}


FCPluginOption::~FCPluginOption()
{
    if (d_ptr->_lib && (d_ptr->_lib.use_count() == 1)) {
        //最后一个引用计数，要销毁
        if (d_ptr->_fpDestory) {
            d_ptr->_fpDestory(d_ptr->_plugin);
        }
    }
}


/**
 * @brief 判断是否是有效的
 * @return
 */
bool FCPluginOption::isValid() const
{
    if ((d_ptr->_fpGetIID == nullptr) ||
        (d_ptr->_fpGetName == nullptr) ||
        (d_ptr->_fpGetVersion == nullptr) ||
        (d_ptr->_fpGetDescription == nullptr) ||
        (d_ptr->_fpCreate == nullptr) ||
        (d_ptr->_fpDestory == nullptr)) {
        return (false);
    }
    return (true);
}


bool FCPluginOption::load(const QString& pluginPath)
{
    if (d_ptr->_lib == nullptr) {
        d_ptr->_lib.reset(new QLibrary);
    }
    d_ptr->_lib->setFileName(pluginPath);
    bool isLoaded = d_ptr->_lib->load();

    if (!isLoaded) {
        qWarning() << QObject::tr("Failed to load %1 (Reason: %2)").arg(getFileName(), getErrorString());
        return (false);
    }
    FP_PluginGetIID getIID = (FP_PluginGetIID)(d_ptr->_lib->resolve("plugin_get_iid"));
    FP_PluginGetName getName = (FP_PluginGetName)(d_ptr->_lib->resolve("plugin_get_name"));
    FP_PluginGetVersion getVersion = (FP_PluginGetVersion)(d_ptr->_lib->resolve("plugin_get_version"));
    FP_PluginGetDescription getDescription = (FP_PluginGetDescription)(d_ptr->_lib->resolve("plugin_get_description"));
    FP_PluginCreate createplugin = (FP_PluginCreate)(d_ptr->_lib->resolve("plugin_create"));
    FP_PluginDestory destoryplugin = (FP_PluginDestory)(d_ptr->_lib->resolve("plugin_destory"));
    bool isok = true;

    if (getIID == nullptr) {
        isok = false;
        qDebug() << QObject::tr("cannot resolve plugin_get_iid");
    }
    if (getName == nullptr) {
        isok = false;
        qDebug() << QObject::tr("cannot resolve plugin_get_name");
    }
    if (getVersion == nullptr) {
        isok = false;
        qDebug() << QObject::tr("cannot resolve plugin_get_version");
    }
    if (getDescription == nullptr) {
        isok = false;
        qDebug() << QObject::tr("cannot resolve plugin_get_description");
    }
    if (createplugin == nullptr) {
        isok = false;
        qDebug() << QObject::tr("cannot resolve plugin_create");
    }
    if (destoryplugin == nullptr) {
        isok = false;
        qDebug() << QObject::tr("cannot resolve plugin_destory");
    }
    if (!isok) {
        return (false);
    }
    d_ptr->_fpGetIID = getIID;
    d_ptr->_fpGetName = getName;
    d_ptr->_fpGetVersion = getVersion;
    d_ptr->_fpGetDescription = getDescription;
    d_ptr->_fpCreate = createplugin;
    d_ptr->_fpDestory = destoryplugin;
    //最后创建一个插件
    d_ptr->_plugin = createplugin();

    return (true);
}


/**
 * @brief 错误信息
 * @return
 */
QString FCPluginOption::getErrorString() const
{
    return (d_ptr->_lib->errorString());
}


QString FCPluginOption::getFileName() const
{
    return (d_ptr->_lib->fileName());
}


/**
 * @brief 获取iid
 * @return
 */
QString FCPluginOption::getIid() const
{
    if (d_ptr->_fpGetIID) {
        return (d_ptr->_fpGetIID());
    }
    return (QString());
}


/**
 * @brief 获取插件
 * @return
 */
FCAbstractPlugin *FCPluginOption::plugin() const
{
    return (d_ptr->_plugin);
}


/**
 * @brief 获取插件的名称
 * @return
 */
QString FCPluginOption::getPluginName() const
{
    if (d_ptr->_fpGetName) {
        return (d_ptr->_fpGetName());
    }
    return (QString());
}


/**
 * @brief 获取插件描述
 * @return
 */
QString FCPluginOption::getPluginDescription() const
{
    if (d_ptr->_fpGetDescription) {
        return (d_ptr->_fpGetDescription());
    }
    return (QString());
}


/**
 * @brief 获取插件版本
 * @return
 */
QString FCPluginOption::getPluginVersion() const
{
    if (d_ptr->_fpGetVersion) {
        return (d_ptr->_fpGetVersion());
    }
    return (QString());
}


/**
 * @brief operator <<
 * @param debug
 * @param po
 * @return
 */
QDebug operator <<(QDebug debug, const FCPluginOption& po)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << QObject::tr("plugin file name:") << po.getFileName()
            << QObject::tr(",iid:") << po.getIid()
            << QObject::tr(",name:") << po.getPluginName()
            << QObject::tr(",description:") << po.getPluginDescription()
            << QObject::tr(",version:") << po.getPluginVersion()
            << QObject::tr(",error string:") <<po.getErrorString()
            << endl;
    return (debug);
}
