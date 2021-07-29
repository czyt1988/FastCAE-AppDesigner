#include "FCPluginManager.h"
#include <QDir>
#include <QDebug>
#include "FCPluginOption.h"
class FCPluginManagerPrivate {
    FC_IMPL_PUBLIC(FCPluginManager)
public:
    FCPluginManagerPrivate(FCPluginManager *p);
    bool hasIID(const QString& iid);

    QDir _pluginDir;
    QString _suffix;///< 插件的后缀
    QHash<QString, FCPluginOption> _pluginOptMap;
};

FCPluginManagerPrivate::FCPluginManagerPrivate(FCPluginManager *p) : q_ptr(p)
    , _pluginDir("./plugin")
#if defined(Q_OS_WIN)
    , _suffix("dll")
#elif defined(Q_OS_UNIX)
    , _suffix("so")
#endif
{
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

    for (const QFileInfo& fi : fileInfos)
    {
        if (fi.suffix().toLower() != d_ptr->_suffix.toLower()) {
            continue;
        }
        FCPluginOption pluginopt;
        if (!pluginopt.load(fi.absoluteFilePath())) {
            continue;
        }
        QString iid = pluginopt.iid();
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
}


/**
 * @brief 设置插件路径，可以多次load，同一个插件（插件名称和类型组成一个key）只会加载一次
 */
void FCPluginManager::setPluginPath(const QString& path)
{
    d_ptr->_pluginDir.setPath(path);
}


int FCPluginManager::getPluginCount() const
{
    return (d_ptr->_pluginOptMap.size());
}
