#ifndef FCABSTRACTNODEGRAPHICSFACTORY_H
#define FCABSTRACTNODEGRAPHICSFACTORY_H
#include "FCNodeGlobal.h"
#include "FCAbstractNodeGraphicsItem.h"
#include <QObject>
#include <FCNodeMetaData.h>

/**
 * @brief FCNodeGraphicsItem的工厂基类，所有自定义的node集合最后都需要提供一个工厂
 *
 * 工厂将通过prototype来创建一个FCNodeGraphicsItem，因此，对于自定义的FCNodeGraphicsItem，都需要给对应的工厂
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
