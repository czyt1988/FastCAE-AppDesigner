#include "FCAbstractNodeGraphicsItem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "FCNodeGraphicsScene.h"
#include "FCNodePalette.h"
////////////////////////////////////////////////////////////////////////


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
    QColor clr = FCNodePalette::getGlobalLinkColor();
    QRect pointrange = getlinkPointRect(pl);// 横版矩形，对应East，West

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
 * @brief 鼠标按下
 * @param event
 */
void FCAbstractNodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<FCNodeLinkPoint> lps = getLinkPoints();

    //左键点击
    for (const FCNodeLinkPoint& lp : lps)
    {
        if (getlinkPointRect(lp).contains(event->pos().toPoint())) {
            //说明这个link point点击了
            //这时候调用sence的信号
            FCNodeGraphicsScene *sc = qobject_cast<FCNodeGraphicsScene *>(scene());
            if (nullptr == sc) {
                qDebug() << "FCAbstractNodeGraphicsItem must be add in FCNodeGraphicsScene";
                return;//异常直接退出
            }
            //scene发射nodeItemLinkPointSelected信号
            sc->callNodeItemLinkPointSelected(this, lp, event);
            //处理完一个就跳出
            return;
        }
    }
}
