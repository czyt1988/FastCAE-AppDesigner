#include "FCNodeStandardLinkGraphicsItem.h"


FCNodeStandardLinkGraphicsItem::FCNodeStandardLinkGraphicsItem(QGraphicsItem *p)
    : FCAbstractNodeLinkGraphicsItem(p)
{
}


FCNodeStandardLinkGraphicsItem::FCNodeStandardLinkGraphicsItem(FCAbstractNodeGraphicsItem *from,
    FCNodeLinkPoint pl,
    QGraphicsItem *p)
    : FCAbstractNodeLinkGraphicsItem(from, pl, p)
{
}
