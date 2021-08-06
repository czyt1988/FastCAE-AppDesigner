#include "FCAbstractNodeLinkGraphicsItem.h"
#include <QPainter>
#include "FCAbstractNodeGraphicsItem.h"

class FCAbstractNodeLinkGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeLinkGraphicsItem)
public:
    FCAbstractNodeLinkGraphicsItemPrivate(FCAbstractNodeLinkGraphicsItem *p);
    FCAbstractNodeGraphicsItem *_fromItem;
    FCAbstractNodeGraphicsItem *_toItem;
    FCNodeLinkPoint _fromPoint;
    FCNodeLinkPoint _toPoint;
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
}


bool FCAbstractNodeLinkGraphicsItem::attachTo(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl)
{
}
