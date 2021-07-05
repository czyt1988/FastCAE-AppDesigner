#ifndef FCNODESMANAGER_H
#define FCNODESMANAGER_H
#include "FCNodeGlobal.h"
#include "FCNode.h"
#include "FCNodeLink.h"
FC_IMPL_FORWARD_DECL(FCNodesManager)

/**
 * @brief 实现对FCNode\FCNodeLink的管理
 *
 * 节点的回收和创建，都通过FCNodesManager来进行操作
 *
 * 通过@sa FCNodesManager 创建的节点和连接都会自动回收
 *
 * @sa createNode @sa createNodeLink 函数用来创建节点和连接
 *
 * @sa deleteNode @sa deleteNodeLink 函数用来销毁节点和连接
 */
class FCNODE_API FCNodesManager
{
    FC_IMPL(FCNodesManager)
public:
    FCNodesManager();
    virtual ~FCNodesManager();

    //创建一个节点
    FCNode *createNode();

    //创建连接
    FCNodeLink *createNodeLink();

    //销毁节点
    void deleteNode(FCNode *node);

    //销毁连接
    void deleteNodeLink(FCNodeLink *link);

    //获取所有节点
    QList<FCNode *> allNodes() const;

    //获取所有连接
    QList<FCNodeLink *> allNodeLinks() const;

    //复制一个节点
    FCNode *copyNode(FCNode *other);
};

#endif // FCNODESMANAGER_H
