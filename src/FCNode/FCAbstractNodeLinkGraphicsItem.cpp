#include "FCAbstractNodeLinkGraphicsItem.h"
#include <QPainter>
#include <QDebug>
#include "FCAbstractNodeGraphicsItem.h"

class FCAbstractNodeLinkGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeLinkGraphicsItem)
public:
    FCAbstractNodeLinkGraphicsItemPrivate(FCAbstractNodeLinkGraphicsItem *p);
    FCAbstractNodeGraphicsItem *_fromItem;
    FCAbstractNodeGraphicsItem *_toItem;
    FCNodeLinkPoint _fromPoint;
    FCNodeLinkPoint _toPoint;
    QPointF _tempToPos;///< 定义结束点的位置
};

FCAbstractNodeLinkGraphicsItemPrivate::FCAbstractNodeLinkGraphicsItemPrivate(FCAbstractNodeLinkGraphicsItem *p)
    : q_ptr(p)
    , _fromItem(nullptr)
    , _toItem(nullptr)
{
}


////////////////////////////////////////////////////////////////////////

FCAbstractNodeLinkGraphicsItem::FCAbstractNodeLinkGraphicsItem(QGraphicsItem *p)
    : QGraphicsItem(p)
    , d_ptr(new FCAbstractNodeLinkGraphicsItemPrivate(this))
{
}


FCAbstractNodeLinkGraphicsItem::FCAbstractNodeLinkGraphicsItem(FCAbstractNodeGraphicsItem *from, FCNodeLinkPoint pl, QGraphicsItem *p)
    : QGraphicsItem(p)
    , d_ptr(new FCAbstractNodeLinkGraphicsItemPrivate(this))
{
    attachFrom(from, pl);
}


FCAbstractNodeLinkGraphicsItem::~FCAbstractNodeLinkGraphicsItem()
{
}


QRectF FCAbstractNodeLinkGraphicsItem::boundingRect() const
{
}


QPainterPath FCAbstractNodeLinkGraphicsItem::shape() const
{
}


void FCAbstractNodeLinkGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}


bool FCAbstractNodeLinkGraphicsItem::attachFrom(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl)
{
    if (!item->isHaveLinkPoint(pl)) {
        qDebug() << QObject::tr("item have not in put link point:") << pl;
        return (false);
    }
    if (!pl.isOutput()) {
        //from必须从out出发
        qDebug() << QObject::tr("link from must attach an output point");
        return (false);
    }
    d_ptr->_fromItem = item;
    d_ptr->_fromPoint = pl;
    return (true);
}


/**
 * @brief 清空from节点
 *
 * 在nodeitem删除时会触发
 */
void FCAbstractNodeLinkGraphicsItem::resetAttachFrom()
{
    d_ptr->_fromItem = nullptr;
    d_ptr->_fromPoint = FCNodeLinkPoint();
}


bool FCAbstractNodeLinkGraphicsItem::attachTo(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl)
{
    if (!item->isHaveLinkPoint(pl)) {
        qDebug() << QObject::tr("item have not in put link point:") << pl;
        return (false);
    }
    if (!pl.isInput()) {
        //to必须到in
        qDebug() << QObject::tr("link to must attach an input point");
        return (false);
    }
    d_ptr->_toItem = item;
    d_ptr->_toPoint = pl;
    return (true);
}


void FCAbstractNodeLinkGraphicsItem::resetAttachTo()
{
    d_ptr->_toItem = nullptr;
    d_ptr->_toPoint = FCNodeLinkPoint();
}


void FCAbstractNodeLinkGraphicsItem::itemIsDestroying(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl)
{
}
