#include "FCAbstractNodeGraphicsItem.h"
#include <QPainter>
#include <QDebug>

class FCAbstractNodeGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeGraphicsItem)
public:
    FCAbstractNodeGraphicsItemPrivate(FCAbstractNodeGraphicsItem *p);
    FCNodeMetaData _meta;
};

FCAbstractNodeGraphicsItemPrivate::FCAbstractNodeGraphicsItemPrivate(FCAbstractNodeGraphicsItem *p)
    : q_ptr(p)
{
}


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
    QColor clr(80, 103, 247);
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
