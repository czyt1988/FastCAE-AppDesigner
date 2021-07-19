#ifndef FCABSTRACTNODEGRAPHICSFACTORY_H
#define FCABSTRACTNODEGRAPHICSFACTORY_H
#include "FCNodeGlobal.h"
#include "FCNodeGraphicsItem.h"

/**
 * @brief FCNodeGraphicsItem的工厂基类，所有自定义的node集合最后都需要提供一个工厂
 *
 * 工厂将通过prototype来创建一个FCNodeGraphicsItem，因此，对于自定义的FCNodeGraphicsItem，都需要给对应的工厂
 */
class FCNODE_API FCAbstractNodeGraphicsFactory
{
public:
    FCAbstractNodeGraphicsFactory();
    virtual ~FCAbstractNodeGraphicsFactory();

    //工厂名称
    virtual QString factoryName() const = 0;

    //工厂函数，创建一个FCNodeGraphicsItem，工厂不持有FCNodeGraphicsItem的管理权
    virtual FCNodeGraphicsItem *create(const QString& prototype) = 0;

    //获取所有注册的Prototypes
    virtual QStringList getPrototypes() const = 0;

    //获取所有类型的分组，同样的分组会放置在一起，这样一个工厂不仅仅只对应一个分组
    virtual QHash<QString, QString> getPrototypesGroup() const = 0;
};

#endif // FCNODEGRAPHICSFACTORY_H
