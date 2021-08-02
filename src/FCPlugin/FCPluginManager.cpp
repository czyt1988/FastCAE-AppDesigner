#include "FCPluginManager.h"
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include "FCPluginOption.h"
class FCPluginManagerPrivate {
    FC_IMPL_PUBLIC(FCPluginManager)
public:
    FCPluginManagerPrivate(FCPluginManager *p);

    QDir _pluginDir;
    QString _suffix;        ///< 插件的后缀
    QList<FCPluginOption> _pluginOptions;
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
 * @brief FCPluginManager::setIgnoreList
 * @param ignorePluginsName
 */
void FCPluginManager::setIgnoreList(const QStringList ignorePluginsName)
{
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
        d_ptr->_pluginOptions.append(pluginopt);
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
    return (d_ptr->_pluginOptions.size());
}


/**
 * @brief 获取加载成功插件的插件名
 * @return
 */
QList<QString> FCPluginManager::getPluginNames() const
{
    QList<QString> res;

    for (const FCPluginOption& opt : d_ptr->_pluginOptions)
    {
        res.append(opt.getPluginName());
    }
    return (res);
}


/**
 * @brief 获取所有插件信息
 * @return
 */
QList<FCPluginOption> FCPluginManager::getPluginOptions() const
{
    return (d_ptr->_pluginOptions);
}


QDebug operator <<(QDebug debug, const FCPluginManager& fmg)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << FCPluginManager::tr("Plugin Manager Info -> is loaded:") << fmg.isLoaded()
            << FCPluginManager::tr(",plugin counts:") << fmg.getPluginCount()
            << endl;
    QList<FCPluginOption> opts = fmg.getPluginOptions();

    for (const FCPluginOption& opt : opts)
    {
        debug.nospace() << opt;
    }
    return (debug);
}
