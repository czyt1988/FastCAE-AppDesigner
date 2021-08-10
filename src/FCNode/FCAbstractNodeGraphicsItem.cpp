#include "FCAbstractNodeGraphicsItem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "FCNodeGraphicsScene.h"
#include "FCNodePalette.h"
#include "FCAbstractNodeLinkGraphicsItem.h"
////////////////////////////////////////////////////////////////////////
class _LinkData {
public:
    _LinkData();
    _LinkData(FCAbstractNodeLinkGraphicsItem *i, const FCNodeLinkPoint& p);
    FCAbstractNodeLinkGraphicsItem *linkitem;
    FCNodeLinkPoint point;
};

bool operator ==(const _LinkData& a, const _LinkData& b);

bool operator ==(const _LinkData& a, const _LinkData& b)
{
    return ((a.linkitem == b.linkitem) && (a.point == b.point));
}


_LinkData::_LinkData() : linkitem(nullptr)
{
}


_LinkData::_LinkData(FCAbstractNodeLinkGraphicsItem *i, const FCNodeLinkPoint& p)
    : linkitem(i),
    point(p)
{
}


class FCAbstractNodeGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeGraphicsItem)
public:
    FCAbstractNodeGraphicsItemPrivate(FCAbstractNodeGraphicsItem *p);
    FCNodeMetaData _meta;
    QList<FCNodeLinkPoint> _linkPoints;     ///< 这里存放所有的linkpoint
    QList<_LinkData> _linkDatas;            ///< 这里记录所有的link
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
    setFlags(ItemIsSelectable
        | ItemIsMovable
        | ItemSendsGeometryChanges //确保位置改变时能发出QGraphicsItem::ItemPositionHasChanged
        );
    setAcceptHoverEvents(true);
}


FCAbstractNodeGraphicsItem::~FCAbstractNodeGraphicsItem()
{
    //item在删除时要通知相关的link把记录删除，否则会出现问题
    for (const _LinkData& ld : d_ptr->_linkDatas)
    {
        ld.linkitem->callItemIsDestroying(this, ld.point);
    }
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
 * @brief 获取连接点群
 * @return
 */
const QList<FCNodeLinkPoint>& FCAbstractNodeGraphicsItem::getLinkPoints() const
{
    return (d_ptr->_linkPoints);
}


/**
 * @brief 获取连接点
 * @param name
 * @return
 */
FCNodeLinkPoint FCAbstractNodeGraphicsItem::getLinkPoint(const QString& name) const
{
    const QList<FCNodeLinkPoint>& lps = getLinkPoints();

    for (const FCNodeLinkPoint& lp : lps)
    {
        if (lp == name) {
            return (lp);
        }
    }
    return (FCNodeLinkPoint());
}


/**
 * @brief 判断是否存在连接点
 * @param pl
 * @return
 */
bool FCAbstractNodeGraphicsItem::isHaveLinkPoint(const FCNodeLinkPoint& pl) const
{
    const QList<FCNodeLinkPoint>& lps = getLinkPoints();

    for (const FCNodeLinkPoint& p : lps)
    {
        if (p == pl) {
            return (true);
        }
    }
    return (false);
}


/**
 * @brief 绘制默认连接点
 *
 * 每个连接点的绘制调用@sa paintLinkPoint 函数,因此实例化重载应该重载@sa paintLinkPoint 函数
 */
void FCAbstractNodeGraphicsItem::paintLinkPoints(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const QList<FCNodeLinkPoint>& lps = getLinkPoints();

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
    QColor clr = FCNodePalette::getGlobalLinkPointColor();
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
 * @brief 处理一些联动事件，如和FCAbstractNodeLinkGraphicsItem的联动
 * @param change
 * @param value
 * @return
 */
QVariant FCAbstractNodeGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if ((ItemPositionHasChanged == change) && scene()) {
        // 变化了位置,需要更新link item
        for (const _LinkData& ld : d_ptr->_linkDatas)
        {
            ld.linkitem->updatePos();
        }
    }
    return (QGraphicsItem::itemChange(change, value));
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


QList<FCNodeLinkPoint>& FCAbstractNodeGraphicsItem::linkPoints()
{
    return (d_ptr->_linkPoints);
}


/**
 * @brief 此函数用于FCAbstractNodeLinkGraphicsItem在调用attachedTo/From过程中调用
 * @param item
 * @param pl
 * @return 如果返回false，说明记录不成功，已经有相同的连接了
 */
bool FCAbstractNodeGraphicsItem::recordLink(FCAbstractNodeLinkGraphicsItem *link, const FCNodeLinkPoint& pl)
{
    _LinkData d(link, pl);

    if (d_ptr->_linkDatas.contains(d)) {
        return (false);
    }
    d_ptr->_linkDatas.append(d);
    return (true);
}


/**
 * @brief 连接的link在销毁时调用，把item记录的link信息消除
 * @param item
 * @param pl
 * @return
 */
bool FCAbstractNodeGraphicsItem::callItemLinkIsDestroying(FCAbstractNodeLinkGraphicsItem *link, const FCNodeLinkPoint& pl)
{
    _LinkData d(link, pl);

    return (d_ptr->_linkDatas.removeAll(d) > 0);
}
