#ifndef FCMETHODEDITORPLUGINMANAGER_H
#define FCMETHODEDITORPLUGINMANAGER_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <QList>
class _FCAbstractNodePluginData;
class FCAbstractNodePlugin;
class FCAbstractNodeGraphicsFactory;

/**
 * @brief 此app的插件管理类
 *
 */
class FCMethodEditorPluginManager : public QObject
{
    Q_OBJECT
    FCMethodEditorPluginManager(QObject *p = nullptr);
    ~FCMethodEditorPluginManager();
public:
    static FCMethodEditorPluginManager& instance();

    //获取所有的节点插件
    QList<FCAbstractNodePlugin *> getNodePlugins() const;

    //获取所有的节点工厂
    QList<FCAbstractNodeGraphicsFactory *> getNodeFactorys() const;

private:
    QList<_FCAbstractNodePluginData *> m_nodePlugins;
};

#endif // FCMETHODEDITORPLUGINMANAGER_H
