#include "FCAbstractNodeGraphicsItem.h"

class FCAbstractNodeGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeGraphicsItem)
public:
    FCAbstractNodeGraphicsItemPrivate(FCAbstractNodeGraphicsItem *p);
    FCNodeMetaData _meta;
};

FCAbstractNodeGraphicsItemPrivate::FCAbstractNodeGraphicsItemPrivate(FCAbstractNodeGraphicsItem *p)
    : q_ptr(p)
{
}


FCAbstractNodeGraphicsItem::FCAbstractNodeGraphicsItem(QGraphicsItem *p) : QGraphicsItem(p)
    , d_ptr(new FCAbstractNodeGraphicsItemPrivate(this))
{
    d_ptr->_meta.setNodePrototype("FC.FCNodeGraphicsItem");
}


FCAbstractNodeGraphicsItem::~FCAbstractNodeGraphicsItem()
{
}


QString FCAbstractNodeGraphicsItem::getNodeName() const
{
    return (d_ptr->_meta.getNodeName());
}


void FCAbstractNodeGraphicsItem::setNodeName(const QString& name)
{
    d_ptr->_meta.setNodeName(name);
}


QString FCAbstractNodeGraphicsItem::getNodePrototype() const
{
    return (d_ptr->_meta.getNodePrototype());
}


/**
 * @brief FCAbstractNodeGraphicsItem::getIcon
 * @return
 */
QIcon FCAbstractNodeGraphicsItem::getIcon() const
{
    return (d_ptr->_meta.getIcon());
}


/**
 * @brief 设置图标
 * @param icon
 */
void FCAbstractNodeGraphicsItem::setIcon(const QIcon& icon)
{
    d_ptr->_meta.setIcon(icon);
}


/**
 * @brief 获取节点元数据
 * @return
 */
const FCNodeMetaData& FCAbstractNodeGraphicsItem::metaData() const
{
    return (d_ptr->_meta);
}


/**
 * @brief 获取节点元数据
 * @return
 */
FCNodeMetaData& FCAbstractNodeGraphicsItem::metaData()
{
    return (d_ptr->_meta);
}


/**
 * @brief 设置元数据
 * @param metadata
 */
void FCAbstractNodeGraphicsItem::setMetaData(const FCNodeMetaData& metadata)
{
    d_ptr->_meta = metadata;
}
