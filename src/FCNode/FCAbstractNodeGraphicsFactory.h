#ifndef FCABSTRACTNODEGRAPHICSFACTORY_H
#define FCABSTRACTNODEGRAPHICSFACTORY_H
#include "FCNodeGlobal.h"
#include "FCAbstractNodeGraphicsItem.h"
#include <QObject>
#include <FCNodeMetaData.h>

/**
 * @brief FCNodeGraphicsItem的工厂基类，所有自定义的node集合最后都需要提供一个工厂
 *
 * 工厂将通过prototype来创建一个FCAbstractNode,FCAbstractNode可以生成FCAbstractNodeGraphicsItem实现前端的渲染，
 * 因此，任何节点都需要实现一个FCAbstractNode和一个FCAbstractNodeGraphicsItem，一个实现逻辑节点的描述，
 * 一个实现前端的渲染,另外FCAbstractNodeGraphicsItem可以生成FCAbstractNodeWidget，用于设置FCAbstractNodeGraphicsItem
 */
class FCNODE_API FCAbstractNodeGraphicsFactory : public QObject
{
    Q_OBJECT
public:
    FCAbstractNodeGraphicsFactory(QObject *p = nullptr);
    virtual ~FCAbstractNodeGraphicsFactory();

    //工厂名称
    virtual QString factoryName() const = 0;

    //工厂函数，创建一个FCNodeGraphicsItem，工厂不持有FCNodeGraphicsItem的管理权
    virtual FCAbstractNodeGraphicsItem *create(const QString& prototype) = 0;

    //获取所有注册的Prototypes
    virtual QStringList getPrototypes() const = 0;

    //获取所有类型的元数据
    virtual QList<FCNodeMetaData> getNodesMetaData() const = 0;
};

#endif // FCNODEGRAPHICSFACTORY_H
