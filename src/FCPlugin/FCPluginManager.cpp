#include "FCPluginManager.h"
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include "FCPluginOption.h"
class FCPluginManagerPrivate {
    FC_IMPL_PUBLIC(FCPluginManager)
public:
    FCPluginManagerPrivate(FCPluginManager *p);
    bool hasIID(const QString& iid);

    QDir _pluginDir;
    QString _suffix;        ///< 插件的后缀
    QHash<QString, FCPluginOption> _pluginOptMap;
    bool _isLoaded;         ///< 标记是否加载了，可以只加载一次
};

FCPluginManagerPrivate::FCPluginManagerPrivate(FCPluginManager *p) : q_ptr(p)
#if defined(Q_OS_WIN)
    , _suffix("dll")
#elif defined(Q_OS_UNIX)
    , _suffix("so")
#endif
    , _isLoaded(false)
{
    _pluginDir.setPath(QCoreApplication::applicationDirPath()+QDir::separator()+"plugins");
}


bool FCPluginManagerPrivate::hasIID(const QString& iid)
{
    return (_pluginOptMap.contains(iid));
}


FCPluginManager::FCPluginManager(QObject *p) : QObject(p)
    , d_ptr(new FCPluginManagerPrivate(this))
{
}


FCPluginManager& FCPluginManager::instance()
{
    static FCPluginManager s_plugin_mgr;

    return (s_plugin_mgr);
}


/**
 * @brief 加载插件
 */
void FCPluginManager::load()
{
    QFileInfoList fileInfos = d_ptr->_pluginDir.entryInfoList(QDir::Files);

    qInfo() << tr("plugin dir is:") << d_ptr->_pluginDir.absolutePath();
    for (const QFileInfo& fi : fileInfos)
    {
        qDebug() << tr("start load plugin:") << fi.absoluteFilePath();
        if (fi.suffix().toLower() != d_ptr->_suffix.toLower()) {
            qDebug() << tr(" ignore invalid suffix:") << fi.suffix().toLower() << tr(" file is:") << fi.absoluteFilePath();
            continue;
        }
        FCPluginOption pluginopt;
        if (!pluginopt.load(fi.absoluteFilePath())) {
            qDebug() << tr("can not load plugin:") << fi.absoluteFilePath();
            continue;
        }
        QString iid = pluginopt.getIid();
        if (iid.isEmpty()) {
            qWarning() << tr("iid is null,plugin path is:") << fi.absoluteFilePath();
            continue;
        }
        if (d_ptr->hasIID(iid)) {
            //已经加载过，释放掉
            qDebug() << tr("iid has been loaded,iid is ") << iid << tr(",from file:") << fi.absoluteFilePath();
            continue;
        }
        d_ptr->_pluginOptMap[iid] = pluginopt;
    }
    d_ptr->_isLoaded = true;
}


bool FCPluginManager::isLoaded() const
{
    return (d_ptr->_isLoaded);
}


/**
 * @brief 设置插件路径，可以多次load，同一个插件（插件名称和类型组成一个key）只会加载一次
 */
void FCPluginManager::setPluginPath(const QString& path)
{
    d_ptr->_pluginDir.setPath(path);
}


/**
 * @brief 获取加载成功插件的数量
 * @return
 */
int FCPluginManager::getPluginCount() const
{
    return (d_ptr->_pluginOptMap.size());
}


/**
 * @brief 获取加载成功插件的插件名
 * @return
 */
QList<QString> FCPluginManager::getPluginNames() const
{
    return (d_ptr->_pluginOptMap.keys());
}


/**
 * @brief 获取插件的设置
 * @param name
 * @return
 */
FCPluginOption FCPluginManager::getPluginOption(const QString& name) const
{
    return (d_ptr->_pluginOptMap.value(name, FCPluginOption()));
}


QDebug operator <<(QDebug debug, const FCPluginManager& fmg)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << FCPluginManager::tr("Plugin Manager Info -> is loaded:") << fmg.isLoaded()
            << FCPluginManager::tr(",plugin counts:") << fmg.getPluginCount()
            << endl;
    QList<QString> names = fmg.getPluginNames();

    for (const QString& n : names)
    {
        FCPluginOption opt = fmg.getPluginOption(n);
        debug.nospace() << FCPluginManager::tr("plugin name:") << n << " " << opt;
    }
    return (debug);
}
