﻿#include "FCNode.h"
#include "FCNode_p.h"
#include <QMultiHash>
#include "FCNodeLink.h"


////////////////////////////////////////////////////////////////

FCNode::FCNode() : d_ptr(new FCNodePrivate(this))
{
}


/**
 * @brief 拷贝构造
 * @param other
 */
FCNode::FCNode(const FCNode& other) : d_ptr(new FCNodePrivate(this))
{
    d_ptr->copy(other.d_ptr.data());
}


/**
 * @brief 移动构造
 * @param other
 */
FCNode::FCNode(FCNode&& other)
{
    d_ptr.reset(other.d_ptr.take());
}


FCNode::~FCNode()
{
    //析构过程，所有连接进行清除操作
}


/**
 * @brief 节点描述
 * @return
 */
QString FCNode::getDescribe() const
{
    return (d_ptr->_describe);
}


/**
 * @brief 设置节点描述
 * @param describe
 */
void FCNode::setDescribe(const QString& describe)
{
    d_ptr->_describe = describe;
}


/**
 * @brief 节点的范围，主要用于QGraphView中
 * @param describe
 */
QRectF FCNode::getBoundingRect() const
{
    return (d_ptr->_boundingRect);
}


/**
 * @brief 设置节点的范围，主要用于QGraphView中
 * @param boundingRect
 */
void FCNode::setBoundingRect(const QRectF& boundingRect)
{
    d_ptr->_boundingRect = boundingRect;
}


/**
 * @brief 节点的绘图
 * @return
 */
QPixmap FCNode::getPixmap() const
{
    return (d_ptr->_pixmap);
}


/**
 * @brief 设置节点的绘图
 * @param pixmap
 */
void FCNode::setPixmap(const QPixmap& pixmap)
{
    d_ptr->_pixmap = pixmap;
}


/**
 * @brief 节点绘图范围，相对于getBoundingRect
 * @return
 */
QRect FCNode::getPixmapRect() const
{
    return (d_ptr->_pixmapRect);
}


/**
 * @brief 设置节点绘图范围，相对于getBoundingRect
 * @param pixmapRect
 */
void FCNode::setPixmapRect(const QRect& pixmapRect)
{
    d_ptr->_pixmapRect = pixmapRect;
}


/**
 * @brief 节点的连接点数
 * @return
 */
int FCNode::getConnectPointCount() const
{
    return (d_ptr->_connectPoints.size());
}


/**
 * @brief 获取节点的连接点，连接点的位置相对于getBoundingRect
 * @param name
 * @return
 */
QPointF FCNode::getConnectPoint(const QString& name) const
{
    return (d_ptr->_connectPoints.value(name));
}


/**
 * @brief 通过索引获取连接点的位置
 * @param index
 * @return
 */
QPointF FCNode::getConnectPointByIndex(int index) const
{
    Q_ASSERT_X(index < getConnectPointCount(), "FCNode::getConnectPointByIndex", "index out of range");
    return ((d_ptr->_connectPoints.begin()+index).value());
}


/**
 * @brief 添加连接点
 * @param name
 * @param p
 */
void FCNode::addConnectPoint(const QString& name, const QPointF& p)
{
    d_ptr->_connectPoints.insert(name, p);
}


/**
 * @brief 判断是否存在连接点
 * @param name
 * @return
 */
bool FCNode::isHaveConnectPoint(const QString& name) const
{
    return (d_ptr->_connectPoints.contains(name));
}


/**
 * @brief 获取节点所有连接点的名字
 * @return
 */
QList<QString> FCNode::connectPointNames() const
{
    return (d_ptr->_connectPoints.keys());
}


/**
 * @brief 获取节点在Graph View中的位置信息
 * @return
 */
QPointF FCNode::getPos() const
{
    return (d_ptr->_pos);
}


/**
 * @brief 设置节点在Graph View中的位置信息
 * @return
 */
void FCNode::setPos(const QPointF& pos)
{
    d_ptr->_pos = pos;
}


/**
 * @brief 设置节点在Graph View中的位置信息
 * @param x
 * @param y
 */
void FCNode::setPos(double x, double y)
{
    d_ptr->_pos = QPointF(x, y);
}


/**
 * @brief 设置节点的旋转
 * @param rotation
 */
void FCNode::setRotation(qreal rotation)
{
    d_ptr->_rotation = rotation;
}


/**
 * @brief 获取旋转角度
 * @return
 */
qreal FCNode::getRotation() const
{
    return (d_ptr->_rotation);
}


/**
 * @brief 复制一个实例，这个是一个工厂函数，需要自己手动销毁
 * @note linkMap不会进行复制操作，因此得到的节点将是没有连接的
 * @return
 */
FCNode *FCNode::copy() const
{
    FCNode *node = new FCNode(*this);

    return (node);
}


/**
 * @brief 设置节点的数据
 * @param d
 * @param role 角色，默认为0，如果需要设置多个数据可以使用其他角色
 */
void FCNode::setData(QVariant d, int role)
{
    d_ptr->_dataMap.insert(role, d);
}


/**
 * @brief 获取数据
 * @param role
 * @return
 */
QVariant FCNode::getData(int role) const
{
    return (d_ptr->_dataMap.value(role));
}