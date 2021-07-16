#ifndef FCGRAPHICSNODELINKLINEITEM_H
#define FCGRAPHICSNODELINKLINEITEM_H
#include <QGraphicsItem>
#include <QPainterPath>
#include <QPen>
#include "FCNodeLink.h"
#include "FCGraphicsItemType.h"
class GGraphicsNodeItem;
///
/// \brief node之间连接线的item
///
class FCGraphicsNodeLinkLineItem : public QGraphicsItem
{
    friend class GGraphicsNodeItem;
public:
    enum { Type = FastCAE::GraphicsNodeLinkLineItem };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return (Type);
    }


    FCGraphicsNodeLinkLineItem(FCNodeLink *link, QGraphicsItem *parent = 0);
    ~FCGraphicsNodeLinkLineItem();
    void setLinkPen(const QPen& pen);
    QPen getLinkPen() const;
    bool attach(GGraphicsNodeItem *item, int index);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void updateNodePos();

    //获取代理的连接指针
    FCNodeLink *getLink() const;

    //更新显示-在FCNodeLink内容更新后调用此函数刷新
    void updateDataByValue();


protected:
    //生成箭头的painterPath虚函数，使用虚函数是为了以后可能改为策略模式
    virtual QPainterPath generateArrowPath(const QPointF& from, const QPointF& end);

    //生成连接点
    virtual QVector<QPointF> generateConnectPoints(const QPointF& p0, const QPointF& pExtern0
        , const QPointF& p1, const QPointF& pExtern1);

private:

    //根据m_p0，m_p1，m_pExtern0，m_pExtern1更新线条
    void updateLine();

    //更新区域
    void updateBoundingRect();

private:
    QPen m_linkPen;
    FCNodeLink *m_link;
    QColor m_hoverColor;
    int m_lineWidth;
    QPointF m_p0;           ///< 原始链接节点1
    QPointF m_p1;           ///< 原始链接节点2
    QPointF m_pExtern0;     ///< 申出的连接节点1
    QPointF m_pExtern1;     ///< 申出的连接节点2
    QVector<QLineF> m_drawLines;
    mutable QRectF m_boundingRect;
    QPainterPath m_arrowPainterPath;        ///<箭头的绘图路径
    QPainterPath m_linePainterPath;         ///< 连接线的路径
    QPointF m_mapOrigionPoint;              ///< 记录映射的点
    int m_externLength;                     ///< 延生线的长度
    bool m_updateAndCallScene;              ///< 更新数值且会通知场景触发节点改变的信号
};

#endif // FCGRAPHICSNODELINKLINEITEM_H
