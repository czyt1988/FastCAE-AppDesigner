#ifndef FCNODESTANDARDLINKGRAPHICSITEM_H
#define FCNODESTANDARDLINKGRAPHICSITEM_H
#include "FCAbstractNodeLinkGraphicsItem.h"
#include <QtCore/qglobal.h>

class FCNODE_API FCNodeStandardLinkGraphicsItem : public FCAbstractNodeLinkGraphicsItem
{
public:
    FCNodeStandardLinkGraphicsItem(QGraphicsItem *p = nullptr);
    FCNodeStandardLinkGraphicsItem(FCAbstractNodeGraphicsItem *from, FCNodeLinkPoint pl, QGraphicsItem *p = nullptr);
};

#endif // FCSTANDARDNODELINKGRAPHICSITEM_H
