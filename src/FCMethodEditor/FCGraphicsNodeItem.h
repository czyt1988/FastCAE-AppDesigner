#ifndef GGRAPHICSNODEITEM_H
#define GGRAPHICSNODEITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QSet>
#include "FCNode.h"
#include "FCGraphicsItemType.h"
class FCGraphicsNodeLinkLineItem;
class FCGraphicsNodeItem : public QGraphicsItem
{
public:
    enum { Type = FastCAE::GraphicsNodeItem };
    int type() const
    {
        return (Type);
    }


    friend class FCGraphicsNodeLinkLineItem;
    FCGraphicsNodeItem(FCNode *node, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //获取链接线的相对点
    int getConnectPointCount() const;

    //获取连接点位置
    QPointF getConnectPointByIndex(int index) const;
    QPointF getConnectPoint(const QString& name) const;

    //添加连接
    void addLink(FCGraphicsNodeLinkLineItem *item);

    //
    FCNode *getNode() const;

    //通过节点的内容更新信息，此函数不会触发scene的变换信号防止递归调用信号
    void updateDataByValue();

    //获取移动前的位置，鼠标点击时会记录此坐标
    QPointF getLastMovePos() const;

protected:

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

private:
    void callLinkDelete(FCGraphicsNodeLinkLineItem *link);
    void updateLinkItem();

private:
    FCNode *m_node;
    static QColor s_hoverColor;
    static QColor s_selectEdgetColor;
    bool m_showConnectPointName;
    bool m_updateAndCallScene;      ///< 更新数值且会通知场景触发节点改变的信号
    QSet<FCGraphicsNodeLinkLineItem *> m_links;
    QPointF m_lastMovePos;          ///< 记录移动前的位置信息
};

#endif // GGRAPHICSNODEITEM_H
