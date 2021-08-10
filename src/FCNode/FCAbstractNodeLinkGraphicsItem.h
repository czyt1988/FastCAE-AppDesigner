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
 *
 * 注意，boundingRect的改变前需要调用prepareGeometryChange，避免出现残影
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


    //自动根据fromitem来更新位置
    void updatePos();

    //更新范围参数
    void updateBoundingRect();

    //通过两个点形成一个矩形，两个点总能形成一个矩形，如果重合，返回一个空矩形
    static QRectF rectFromTwoPoint(const QPointF& p0, const QPointF& p1);

    //通过伸出点方向，得到贝塞尔曲线控制点的位置
    static QPointF calcCubicControlPoint(const QPointF& orgPoint, FCNodeLinkPoint::Direction d, qreal externLen);

    //计算两个点的距离
    static qreal pointLength(const QPointF& a, const QPointF& b);

    //生成一个相反的方向
    static FCNodeLinkPoint::Direction generateOppositeDirection(FCNodeLinkPoint::Direction ad);

    //设置贝塞尔曲线的控制点的缩放比例，FCAbstractNodeLinkGraphicsItem在连线时按照控制点的方向延伸出贝塞尔曲线的控制点，延伸的控制点的长度w = length * bezierControlScale
    void setBezierControlScale(qreal rate = 0.25);

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
    //添加事件处理
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value);

    //连接的item在销毁，销毁过程对应的item会调用此函数，把link记录的item信息消除
    void callItemIsDestroying(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl);

private:
    //生成painterpath
    void generatePainterPath();
};



#endif // FCABSTRACTNODELINKGRAPHICSITEM_H
