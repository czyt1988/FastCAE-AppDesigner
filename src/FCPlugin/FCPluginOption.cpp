#include "FCPluginOption.h"
#include <QObject>
#include <QLibrary>
#include <QSharedPointer>
#include <QDebug>
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
    QSharedPointer<QLibrary> _lib;
};

FCPluginOptionPrivate::FCPluginOptionPrivate(FCPluginOption *p) : q_ptr(p)
{
}


FCPluginOption::FCPluginOption() : d_ptr(new FCPluginOptionPrivate(this))
{
    d_ptr->_lib.reset(new QLibrary);
}


FCPluginOption::FCPluginOption(const FCPluginOption& other)
{
    (*d_ptr) = *(other.d_ptr);
}


FCPluginOption::FCPluginOption(FCPluginOption&& other)
{
    d_ptr.reset(other.d_ptr.take());
}


FCPluginOption& FCPluginOption::operator =(const FCPluginOption& other)
{
    (*d_ptr) = *(other.d_ptr);
    return (*this);
}


FCPluginOption::~FCPluginOption()
{
}


bool FCPluginOption::load(const QString& pluginPath)
{
    if (d_ptr->_lib == nullptr) {
        d_ptr->_lib.reset(new QLibrary);
    }
    d_ptr->_lib->setFileName(pluginPath);
    bool isLoaded = d_ptr->_lib->load();

    if (!isLoaded) {
        qWarning() << QObject::tr("Failed to load %1 (Reason: %2)").arg(fileName(), errorString());
        return (false);
    }
    FP_PluginGetIID getIID = (FP_PluginGetIID)(d_ptr->_lib->resolve("plugin_get_iid"));
    FP_PluginGetName getName = (FP_PluginGetName)(d_ptr->_lib->resolve("plugin_get_name"));
    FP_PluginGetVersion getVersion = (FP_PluginGetVersion)(d_ptr->_lib->resolve("plugin_get_version"));
    FP_PluginGetDescription getDescription = (FP_PluginGetDescription)(d_ptr->_lib->resolve("plugin_get_description"));
    FP_PluginCreate createplugin = (FP_PluginCreate)(d_ptr->_lib->resolve("plugin_create"));
    FP_PluginDestory destoryplugin = (FP_PluginDestory)(d_ptr->_lib->resolve("plugin_destory"));

    if ((getIID == nullptr) ||
        (getName == nullptr) ||
        (getVersion == nullptr) ||
        (getDescription == nullptr) ||
        (createplugin == nullptr) ||
        (destoryplugin == nullptr)) {
        qWarning() << QObject::tr("%1 is load,but can not resolve some necessary function").arg(fileName());
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
QString FCPluginOption::errorString() const
{
    return (d_ptr->_lib->errorString());
}


QString FCPluginOption::fileName() const
{
    return (d_ptr->_lib->fileName());
}


/**
 * @brief 获取iid
 * @return
 */
QString FCPluginOption::iid() const
{
    if (d_ptr->_plugin) {
        return (d_ptr->_plugin->getIID());
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
