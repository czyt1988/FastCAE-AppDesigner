#ifndef FCABSTRACTNODEPLUGIN_H
#define FCABSTRACTNODEPLUGIN_H
#include <QtPlugin>
#include "FCNodeGlobal.h"
#include "FCAbstractNodeGraphicsFactory.h"
#include "FCAbstractPlugin.h"

/**
 * @brief 节点插件
 */
class FCNODE_API FCAbstractNodePlugin : public FCAbstractPlugin
{
public:
    FCAbstractNodePlugin();
    virtual ~FCAbstractNodePlugin();

    /**
     * @brief 创建一个节点工厂
     * @return
     */
    virtual FCAbstractNodeGraphicsFactory *createNodeFactory() = 0;

    /**
     * @brief 删除一个节点工厂(谁创建谁删除原则)
     * @param p
     */
    virtual void destoryNodeFactory(FCAbstractNodeGraphicsFactory *p) = 0;
};

#endif // FCABSTRACTNODEPLUGIN_H
