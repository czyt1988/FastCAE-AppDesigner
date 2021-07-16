#ifndef FCNODESLOADER_H
#define FCNODESLOADER_H
#include "FCNodeGlobal.h"
#include "FCNode.h"
#include "FCNodesManager.h"
FC_IMPL_FORWARD_DECL(FCNodesLoader)

/**
 * @brief 把node按标准xml文件加载到manager中
 */
class FCNODE_API FCNodesLoader
{
    FC_IMPL(FCNodesLoader)
public:
    FCNodesLoader(FCNodesManager *mgr);
    ~FCNodesLoader();
    //加载一个xml节点
    FCNode *load(const QString& filepath);
};

#endif // FCNODESLOADER_H
