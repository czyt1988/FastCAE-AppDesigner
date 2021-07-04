#include "FCNodeLink.h"
#include "FCNode.h"
#include "FCNode_p.h"
class FCNodeLinkPrivate {
public:
    FC_IMPL_PUBLIC(FCNodeLink)
    FCNodeLinkPrivate(FCNodeLink *p);
    FCNode *_fromNode;
    FCNode *_toNode;
};

FCNodeLinkPrivate::FCNodeLinkPrivate(FCNodeLink *p) : q_ptr(p)
    , _fromNode(nullptr)
    , _toNode(nullptr)
{
}


////////////////////////////////////////////////////////////////

FCNodeLink::FCNodeLink()
{
}


FCNodeLink::~FCNodeLink()
{
}


/**
 * @brief 连接起始节点
 * @param node
 * @param connectPointName
 * @return
 */
bool FCNodeLink::attachFrom(FCNode *node, const QString& connectPointName)
{
    if (d_ptr->_fromNode) {
        //不需要判断名字，有可能改变连接，仅仅需要断开之前的连接
        //node断开此链接
        d_ptr->_fromNode->d_ptr->removeLink(this);
    }
    if (nullptr == node) {
        d_ptr->_fromNode = nullptr;
        return (true);
    }
    if (node->isHaveConnectPoint(connectPointName)) {
        d_ptr->_fromNode = node;
        return (true);
    }
    return (false);
}


bool FCNodeLink::attachTo(FCNode *node, const QString& connectPointName)
{
    if (d_ptr->_toNode) {
        //不需要判断名字，有可能改变连接，仅仅需要断开之前的连接
        //node断开此链接
        d_ptr->_toNode->d_ptr->removeLink(this);
    }
    if (nullptr == node) {
        d_ptr->_toNode = nullptr;
        return (true);
    }
    if (node->isHaveConnectPoint(connectPointName)) {
        d_ptr->_toNode = node;
        return (true);
    }
    return (false);
}


FCNode *FCNodeLink::from()
{
    return (d_ptr->_fromNode);
}


const FCNode *FCNodeLink::from() const
{
    return (d_ptr->_fromNode);
}


FCNode *FCNodeLink::to()
{
    return (d_ptr->_toNode);
}


const FCNode *FCNodeLink::to() const
{
    return (d_ptr->_toNode);
}


bool FCNodeLink::isHaveFromNode() const
{
    return (d_ptr->_fromNode != nullptr);
}


bool FCNodeLink::isHaveToNode() const
{
    return (d_ptr->_toNode != nullptr);
}
