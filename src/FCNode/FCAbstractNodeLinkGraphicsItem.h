#ifndef FCABSTRACTNODELINKGRAPHICSITEM_H
#define FCABSTRACTNODELINKGRAPHICSITEM_H
#include "FCNodeGlobal.h"
#include <QGraphicsItem>
#include <QtCore/qglobal.h>
#include "FCNodeLinkPoint.h"
FC_IMPL_FORWARD_DECL(FCAbstractNodeLinkGraphicsItem)
class FCAbstractNodeGraphicsItem;

/**
 * @brief 绘制连接线的item
 */
class FCNODE_API FCAbstractNodeLinkGraphicsItem : public QGraphicsItem
{
    FC_IMPL(FCAbstractNodeLinkGraphicsItem)
public:
    enum { Type = FastCAE::GraphicsLinkItem };
    int type() const
    {
        return (Type);
    }


public:
    FCAbstractNodeLinkGraphicsItem(QGraphicsItem *p = nullptr);
    FCAbstractNodeLinkGraphicsItem(FCAbstractNodeGraphicsItem *from, FCNodeLinkPoint pl, QGraphicsItem *p = nullptr);
    virtual ~FCAbstractNodeLinkGraphicsItem();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //开始节点连接
    bool attachFrom(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl);

    //结束节点连接
    bool attachTo(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl);
};

#endif // FCABSTRACTNODELINKGRAPHICSITEM_H
