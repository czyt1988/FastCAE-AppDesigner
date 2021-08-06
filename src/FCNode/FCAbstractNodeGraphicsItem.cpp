#include "FCAbstractNodeGraphicsItem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

////////////////////////////////////////////////////////////////////////

FCNodeLinkPoint::FCNodeLinkPoint()
    : direction(East)
    , way(OutPut)
{
}


FCNodeLinkPoint::FCNodeLinkPoint(const QPoint& p, const QString& n, FCNodeLinkPoint::Way w, FCNodeLinkPoint::Direction d)
    : position(p)
    , name(n)
    , way(w)
    , direction(d)
{
}


/**
 * @brief FCNodeLinkPoint 的等于号操作符
 * @param a
 * @param b
 * @return
 */
bool operator ==(const FCNodeLinkPoint& a, const FCNodeLinkPoint& b)
{
    return ((a.name == b.name) &&
           (a.direction == b.direction) &&
           (a.position == b.position) &&
           (a.way == b.way));
}


////////////////////////////////////////////////////////////////////////

class FCAbstractNodeGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeGraphicsItem)
public:
    FCAbstractNodeGraphicsItemPrivate(FCAbstractNodeGraphicsItem *p);
    FCNodeMetaData _meta;
    QColor _linkPointColor;
};

FCAbstractNodeGraphicsItemPrivate::FCAbstractNodeGraphicsItemPrivate(FCAbstractNodeGraphicsItem *p)
    : q_ptr(p)
    , _linkPointColor(80, 103, 247)
{
}


////////////////////////////////////////////////////////////////////////

FCAbstractNodeGraphicsItem::FCAbstractNodeGraphicsItem(QGraphicsItem *p) : QGraphicsItem(p)
    , d_ptr(new FCAbstractNodeGraphicsItemPrivate(this))
{
    d_ptr->_meta.setNodePrototype("FC.FCNodeGraphicsItem");
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}


FCAbstractNodeGraphicsItem::~FCAbstractNodeGraphicsItem()
{
}


QString FCAbstractNodeGraphicsItem::getNodeName() const
{
    return (d_ptr->_meta.getNodeName());
}


void FCAbstractNodeGraphicsItem::setNodeName(const QString& name)
{
    d_ptr->_meta.setNodeName(name);
}


QString FCAbstractNodeGraphicsItem::getNodePrototype() const
{
    return (d_ptr->_meta.getNodePrototype());
}


/**
 * @brief FCAbstractNodeGraphicsItem::getIcon
 * @return
 */
QIcon FCAbstractNodeGraphicsItem::getIcon() const
{
    return (d_ptr->_meta.getIcon());
}


/**
 * @brief 设置图标
 * @param icon
 */
void FCAbstractNodeGraphicsItem::setIcon(const QIcon& icon)
{
    d_ptr->_meta.setIcon(icon);
}


/**
 * @brief 获取节点元数据
 * @return
 */
const FCNodeMetaData& FCAbstractNodeGraphicsItem::metaData() const
{
    return (d_ptr->_meta);
}


/**
 * @brief 获取节点元数据
 * @return
 */
FCNodeMetaData& FCAbstractNodeGraphicsItem::metaData()
{
    return (d_ptr->_meta);
}


/**
 * @brief 设置元数据
 * @param metadata
 */
void FCAbstractNodeGraphicsItem::setMetaData(const FCNodeMetaData& metadata)
{
    d_ptr->_meta = metadata;
}


/**
 * @brief 绘制默认连接点
 *
 * 每个连接点的绘制调用@sa paintLinkPoint 函数,因此实例化重载应该重载@sa paintLinkPoint 函数
 */
void FCAbstractNodeGraphicsItem::paintLinkPoints(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QList<FCNodeLinkPoint> lps = getLinkPoints();

    for (const FCNodeLinkPoint& lp : lps)
    {
        paintLinkPoint(lp, painter);
    }
}


/**
 * @brief 绘制某个连接点
 * @param pl
 * @param painter
 */
void FCAbstractNodeGraphicsItem::paintLinkPoint(const FCNodeLinkPoint& pl, QPainter *painter)
{
    painter->save();
    //连接点是一个长方形，6X8,点中心是长方形中心
    //先把painter坐标变换到点处
    QColor clr = getLinkPointColor();
    QRect pointrange = getlinkPointRect(pl);// 横版矩形，对应East，West

    qDebug() << pointrange;
    painter->setPen(clr);
    painter->drawRect(pointrange);
    if (FCNodeLinkPoint::OutPut == pl.way) {
        painter->fillRect(pointrange, clr);
    }
    painter->restore();
}


/**
 * @brief 获取连接点对应的矩形区域
 * @param pl
 * @return
 */
QRect FCAbstractNodeGraphicsItem::getlinkPointRect(const FCNodeLinkPoint& pl) const
{
    switch (pl.direction)
    {
    case FCNodeLinkPoint::East:
    case FCNodeLinkPoint::West:
        return (QRect(pl.position.x()-4, pl.position.y()-3, 8, 6));

    case FCNodeLinkPoint::North:
    case FCNodeLinkPoint::South:
        return (QRect(pl.position.x()-3, pl.position.y()-4, 6, 8));

    default:
        break;
    }
    return (QRect(pl.position.x()-3, pl.position.y()-3, 6, 6));
}


/**
 * @brief 设置连接点的颜色
 * @param clr
 */
void FCAbstractNodeGraphicsItem::setLinkPointColor(const QColor& clr)
{
    d_ptr->_linkPointColor = clr;
}


/**
 * @brief 返回连接点的颜色
 * @return
 */
const QColor& FCAbstractNodeGraphicsItem::getLinkPointColor() const
{
    return (d_ptr->_linkPointColor);
}


/**
 * @brief 鼠标按下
 * @param event
 */
void FCAbstractNodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<FCNodeLinkPoint> lps = getLinkPoints();

    for (const FCNodeLinkPoint& lp : lps)
    {
        if (getlinkPointRect(lp).contains(event->pos().toPoint())) {
            //说明这个link point点击了
        }
    }
}
