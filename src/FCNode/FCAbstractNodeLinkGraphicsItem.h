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
    friend class FCAbstractNodeGraphicsItem;
    friend class FCNodeGraphicsScene;
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

    //清空from节点
    void resetAttachFrom();

    //结束节点连接
    bool attachTo(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl);

    //清空to节点
    void resetAttachTo();

protected:
    //连接的item在销毁，销毁过程对应的item会调用此函数，刷新link内容
    void itemIsDestroying(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl);
};



#endif // FCABSTRACTNODELINKGRAPHICSITEM_H
