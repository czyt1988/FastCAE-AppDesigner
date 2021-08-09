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


    //更新范围参数
    void updateBoundingRect();

    //通过两个点形成一个矩形，两个点总能形成一个矩形，如果重合，返回一个空矩形
    static QRectF rectFromTwoPoint(const QPointF& p0, const QPointF& p1);

public:
    FCAbstractNodeLinkGraphicsItem(QGraphicsItem *p = nullptr);
    FCAbstractNodeLinkGraphicsItem(FCAbstractNodeGraphicsItem *from, FCNodeLinkPoint pl, QGraphicsItem *p = nullptr);
    virtual ~FCAbstractNodeLinkGraphicsItem();
    QRectF boundingRect() const;
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
    //添加事件处理
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value);

    //连接的item在销毁，销毁过程对应的item会调用此函数，把link记录的item信息消除
    void callItemIsDestroying(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl);
};



#endif // FCABSTRACTNODELINKGRAPHICSITEM_H
