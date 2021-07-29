#ifndef FCNODEGRAPHICSFACTORY_H
#define FCNODEGRAPHICSFACTORY_H
#include "FCUtilNodePluginGlobal.h"
#include "FCAbstractNodeGraphicsFactory.h"
#include <functional>

/**
 * @brief 主节点工厂
 *
 * 其他的插件可参看主节点工厂进行编写
 */
class FCUTILNODEPLUGIN_API FCNodeGraphicsFactory : public FCAbstractNodeGraphicsFactory
{
public:
    FCNodeGraphicsFactory(QObject *p = nullptr);

    //工厂名称
    virtual QString factoryName() const;

    //工厂函数，创建一个FCNodeGraphicsItem，工厂不持有FCNodeGraphicsItem的管理权
    virtual FCAbstractNodeGraphicsItem *create(const QString& prototype);

    //获取所有注册的Prototypes
    virtual QStringList getPrototypes() const;

    //获取所有类型的分组，同样的分组会放置在一起，这样一个工厂不仅仅只对应一个分组
    virtual QList<FCNodeMetaData> getNodesMetaData() const;

protected:
    void createMetaData();

private:
    FCNodeMetaData saveGetMetaType(FCAbstractNodeGraphicsItem *t);

private:
    typedef std::function<FCAbstractNodeGraphicsItem *(void)> FpCreate;
    QMap<FCNodeMetaData, FpCreate> m_prototypeTpfp;
};

#endif // FCNODEGRAPHICSFACTORY_H
