#include "FCNodesManager.h"
class FCNodesManagerPrivate {
public:
    FC_IMPL_PUBLIC(FCNodesManager)
    FCNodesManagerPrivate(FCNodesManager *p);
    void destory();

    QList<FCNode *> _nodes;
    QList<FCNodeLink *> _links;
};


FCNodesManagerPrivate::FCNodesManagerPrivate(FCNodesManager *p) : q_ptr(p)
{
}


void FCNodesManagerPrivate::destory()
{
    for (FCNode *n : _nodes)
    {
        delete n;
    }
    for (FCNodeLink *n : _links)
    {
        delete n;
    }
    _nodes.clear();
    _links.clear();
}


////////////////////////////////////////////////////

FCNodesManager::FCNodesManager() : d_ptr(new FCNodesManagerPrivate(this))
{
}


FCNodesManager::~FCNodesManager()
{
    d_ptr->destory();
}


/**
 * @brief 创建一个节点,并管理
 * @note 节点的内存由FCNodesManager来管理
 * @return
 */
FCNode *FCNodesManager::createNode()
{
    FCNode *n = new FCNode();

    d_ptr->_nodes.append(n);
    return (n);
}


/**
 * @brief 创建节点连接,并管理
 * @note 节点连接的内存由FCNodesManager来管理
 * @return
 */
FCNodeLink *FCNodesManager::createNodeLink()
{
    FCNodeLink *n = new FCNodeLink();

    d_ptr->_links.append(n);
    return (n);
}


/**
 * @brief 销毁一个节点
 * @param node
 */
void FCNodesManager::deleteNode(FCNode *node)
{
    d_ptr->_nodes.removeOne(node);
    delete node;
}


/**
 * @brief 销毁一个链接
 * @param link
 */
void FCNodesManager::deleteNodeLink(FCNodeLink *link)
{
    d_ptr->_links.removeOne(link);
    delete link;
}


/**
 * @brief 获取所有节点
 * @return
 */
QList<FCNode *> FCNodesManager::allNodes() const
{
    return (d_ptr->_nodes);
}


/**
 * @brief 获取所有连接
 * @return
 */
QList<FCNodeLink *> FCNodesManager::allNodeLinks() const
{
    return (d_ptr->_links);
}


/**
 * @brief 根据节点复制出一个节点，并进行管理
 * @note other节点可以并非FCNodesManager管理的节点
 * @param other 其他节点实例
 * @return 返回复制出来的节点，此时节点的内存归FCNodesManager管理
 */
FCNode *FCNodesManager::copyNode(FCNode *other)
{
    FCNode *n = new FCNode(*other);

    d_ptr->_nodes.append(n);
    return (n);
}
