#include "FCMethodEditorPluginManager.h"
#include "FCAbstractNodePlugin.h"
#include "FCAbstractPlugin.h"
#include "FCPluginManager.h"
#include "FCAbstractNodeGraphicsFactory.h"

class _FCAbstractNodePluginData {
public:
    _FCAbstractNodePluginData();
    ~_FCAbstractNodePluginData();
    FCAbstractNodePlugin *plugin = { nullptr };
    FCAbstractNodeGraphicsFactory *factory = { nullptr };
};
_FCAbstractNodePluginData::_FCAbstractNodePluginData()
{
}


_FCAbstractNodePluginData::~_FCAbstractNodePluginData()
{
    if (plugin && factory) {
        plugin->destoryNodeFactory(factory);
    }
}


FCMethodEditorPluginManager::FCMethodEditorPluginManager(QObject *p) : QObject(p)
{
    //加载插件
    FCPluginManager& plugin = FCPluginManager::instance();

    if (!plugin.isLoaded()) {
        plugin.load();
    }
    //获取插件
    QList<FCPluginOption> plugins = plugin.getPluginOptions();

    for (int i = 0; i < plugins.size(); ++i)
    {
        FCPluginOption opt = plugins[i];
        if (!opt.isValid()) {
            continue;
        }
        FCAbstractPlugin *p = opt.plugin();
        //开始通过dynamic_cast判断插件的具体类型
        if (FCAbstractNodePlugin *np = dynamic_cast<FCAbstractNodePlugin *>(p)) {
            //说明是节点插件
            _FCAbstractNodePluginData *data = new _FCAbstractNodePluginData();
            data->plugin = np;
            data->factory = np->createNodeFactory();
            m_nodePlugins.append(data);
        }
    }
}


FCMethodEditorPluginManager::~FCMethodEditorPluginManager()
{
    for (_FCAbstractNodePluginData *d : m_nodePlugins)
    {
        delete d;
    }
}


FCMethodEditorPluginManager& FCMethodEditorPluginManager::instance()
{
    static FCMethodEditorPluginManager s_mgr;

    return (s_mgr);
}


/**
 * @brief 获取所有的节点插件
 * @return
 */
QList<FCAbstractNodePlugin *> FCMethodEditorPluginManager::getNodePlugins() const
{
    QList<FCAbstractNodePlugin *> res;

    for (_FCAbstractNodePluginData *d : m_nodePlugins)
    {
        res.append(d->plugin);
    }
    return (res);
}


/**
 * @brief 获取所有的节点工厂
 * @return
 */
QList<FCAbstractNodeGraphicsFactory *> FCMethodEditorPluginManager::getNodeFactorys() const
{
    QList<FCAbstractNodeGraphicsFactory *> res;

    for (_FCAbstractNodePluginData *d : m_nodePlugins)
    {
        res.append(d->factory);
    }
    return (res);
}
