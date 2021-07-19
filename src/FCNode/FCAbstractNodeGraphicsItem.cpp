#include "FCNodeGraphicsItem.h"

class FCNodeGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCNodeGraphicsItem);
public:
    FCNodeGraphicsItemPrivate(FCNodeGraphicsItem *p);
    QString _name;
};

FCNodeGraphicsItemPrivate::FCNodeGraphicsItemPrivate(FCNodeGraphicsItem *p)
    : q_ptr(p)
{
}


FCNodeGraphicsItem::FCNodeGraphicsItem(QGraphicsItem *p) : QGraphicsItem(p)
    , d_ptr(new FCNodeGraphicsItemPrivate(this))
{
}


FCNodeGraphicsItem::~FCNodeGraphicsItem()
{
}


QString FCNodeGraphicsItem::getNodeName() const
{
    return (d_ptr->_name);
}


void FCNodeGraphicsItem::setNodeName(const QString& name)
{
    d_ptr->_name = name;
}


QString FCNodeGraphicsItem::getNodePrototype() const
{
    return ("FC.FCNodeGraphicsItem");
}
