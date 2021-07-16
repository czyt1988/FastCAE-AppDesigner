#include "FCNodeLink.h"
#include "FCNode.h"
#include "FCNode_p.h"

FCNodeLink::FCNodeLink() : d_ptr(new FCNodeLinkPrivate(this))
{
}


FCNodeLink::~FCNodeLink()
{
    //节点删除时，把node的连接剔除
    disattachFrom();
    disattachTo();
}


/**
 * @brief 连接起始节点
 * @param node
 * @param connectPointName
 * @return
 */
bool FCNodeLink::attachFrom(FCNode *node, const QString& connectPointName)
{
    if (nullptr == node) {
        disattachFrom();
        return (true);
    }else if (node->isHaveConnectPoint(connectPointName)) {
        disattachFrom();
        d_ptr->_fromNode = node;
        d_ptr->_fromConnectName = connectPointName;
        return (true);
    }
    return (false);
}


bool FCNodeLink::attachTo(FCNode *node, const QString& connectPointName)
{
    if (nullptr == node) {
        disattachTo();
        return (true);
    }else if (node->isHaveConnectPoint(connectPointName)) {
        disattachTo();
        d_ptr->_toNode = node;
        d_ptr->_toConnectName = connectPointName;
        return (true);
    }
    return (false);
}


void FCNodeLink::disattachFrom()
{
    if (d_ptr->_fromNode) {
        //不需要判断名字，有可能改变连接，仅仅需要断开之前的连接
        //node断开此链接
        d_ptr->_fromNode->d_ptr->removeLink(this);
    }
    d_ptr->_fromNode = nullptr;
    d_ptr->_fromConnectName = QString();
}


void FCNodeLink::disattachTo()
{
    if (d_ptr->_toNode) {
        //不需要判断名字，有可能改变连接，仅仅需要断开之前的连接
        //node断开此链接
        d_ptr->_toNode->d_ptr->removeLink(this);
    }
    d_ptr->_toNode = nullptr;
    d_ptr->_toConnectName = QString();
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


/**
 * @brief 得到连接点名字
 * @return
 */
QString FCNodeLink::fromConnectName() const
{
    return (d_ptr->_fromConnectName);
}


/**
 * @brief 得到连接点名字
 * @return
 */
QString FCNodeLink::toConnectName() const
{
    return (d_ptr->_toConnectName);
}


/**
 * @brief 获取连接点的点相对node的位置，如果没有node将返回一个无效的QPointF
 * @return
 */
QPointF FCNodeLink::getFromNodeConnectPoint() const
{
    if (d_ptr->_fromNode) {
        return (d_ptr->_fromNode->getConnectPoint(d_ptr->_fromConnectName));
    }
    return (QPointF());
}


/**
 * @brief 获取连接点的点相对node的位置，如果没有node将返回一个无效的QPointF
 * @return
 */
QPointF FCNodeLink::getToNodeConnectPoint() const
{
    if (d_ptr->_toNode) {
        return (d_ptr->_toNode->getConnectPoint(d_ptr->_toConnectName));
    }
    return (QPointF());
}


void FCNodeLink::_disattachTo()
{
    d_ptr->_toNode = nullptr;
}


void FCNodeLink::_disattachFrom()
{
    d_ptr->_fromNode = nullptr;
}
