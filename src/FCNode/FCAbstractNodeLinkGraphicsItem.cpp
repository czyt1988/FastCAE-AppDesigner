#include "FCAbstractNodeLinkGraphicsItem.h"
#include <QPainter>
#include <QDebug>
#include "FCAbstractNodeGraphicsItem.h"
#include "FCNodeGraphicsScene.h"
#include "FCNodePalette.h"
class FCAbstractNodeLinkGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeLinkGraphicsItem)
public:
    FCAbstractNodeLinkGraphicsItemPrivate(FCAbstractNodeLinkGraphicsItem *p);
    FCNodeGraphicsScene *nodeScene() const;

    FCAbstractNodeGraphicsItem *_fromItem;
    FCAbstractNodeGraphicsItem *_toItem;
    FCNodeLinkPoint _fromPoint;
    FCNodeLinkPoint _toPoint;
    QPointF _fromPos;
    QPointF _toPos;
    QRectF _boundingRect; ///< 记录boundingRect
};

FCAbstractNodeLinkGraphicsItemPrivate::FCAbstractNodeLinkGraphicsItemPrivate(FCAbstractNodeLinkGraphicsItem *p)
    : q_ptr(p)
    , _fromItem(nullptr)
    , _toItem(nullptr)
    , _fromPos(0, 0)
    , _toPos(100, 100)
    , _boundingRect(0, 0, 100, 100)
{
}


FCNodeGraphicsScene *FCAbstractNodeLinkGraphicsItemPrivate::nodeScene() const
{
    return (qobject_cast<FCNodeGraphicsScene *>(q_ptr->scene()));
}


////////////////////////////////////////////////////////////////////////



FCAbstractNodeLinkGraphicsItem::FCAbstractNodeLinkGraphicsItem(QGraphicsItem *p)
    : QGraphicsItem(p)
    , d_ptr(new FCAbstractNodeLinkGraphicsItemPrivate(this))
{
}


FCAbstractNodeLinkGraphicsItem::FCAbstractNodeLinkGraphicsItem(FCAbstractNodeGraphicsItem *from, FCNodeLinkPoint pl, QGraphicsItem *p)
    : QGraphicsItem(p)
    , d_ptr(new FCAbstractNodeLinkGraphicsItemPrivate(this))
{
    attachFrom(from, pl);
}


FCAbstractNodeLinkGraphicsItem::~FCAbstractNodeLinkGraphicsItem()
{
    //析构时d调用FCAbstractNodeGraphicsItem::callItemLinkIsDestroying移除item对应记录的link
    if (d_ptr->_fromItem) {
        d_ptr->_fromItem->callItemLinkIsDestroying(this, d_ptr->_fromPoint);
    }
    if (d_ptr->_toItem) {
        d_ptr->_toItem->callItemLinkIsDestroying(this, d_ptr->_toPoint);
    }
}


/**
 * @brief 更新范围参数
 */
void FCAbstractNodeLinkGraphicsItem::updateBoundingRect()
{
    FCNodeGraphicsScene *sc = d_ptr->nodeScene();

    if (nullptr == sc) {
        return;
    }
    d_ptr->_fromPos = QPointF(0, 0);
    d_ptr->_toPos = QPointF(100, 100);
    if ((d_ptr->_fromItem == nullptr) && (d_ptr->_toItem == nullptr)) {
        //都是空退出
        d_ptr->_boundingRect = rectFromTwoPoint(d_ptr->_fromPos, d_ptr->_toPos);
        return;
    } else if ((d_ptr->_fromItem != nullptr) && (d_ptr->_toItem == nullptr)) {
        //只设定了一个from
        // to要根据scene的鼠标位置实时刷新
        d_ptr->_toPos = mapFromScene(sc->getCurrentMouseScenePos());
        //重新设置rect的topleft和buttomright
        d_ptr->_boundingRect = rectFromTwoPoint(d_ptr->_fromPos, d_ptr->_toPos);
    }else if ((d_ptr->_fromItem != nullptr) && (d_ptr->_toItem != nullptr)) {
        //两个都不为空
        d_ptr->_toPos = mapFromItem(d_ptr->_toItem, d_ptr->_toPoint.position);
        d_ptr->_boundingRect = rectFromTwoPoint(d_ptr->_fromPos, d_ptr->_toPos);
    }
}


/**
 * @brief 通过两个点形成一个矩形，两个点总能形成一个矩形，如果重合，返回一个空矩形
 * @param p0
 * @param p1
 * @return
 */
QRectF FCAbstractNodeLinkGraphicsItem::rectFromTwoPoint(const QPointF& p0, const QPointF& p1)
{
    return (QRectF(QPointF(qMin(p0.x(), p1.x()), qMin(p0.y(), p1.y())), QPointF(qMax(p0.x(), p1.x()), qMax(p0.y(), p1.y()))));
}


QRectF FCAbstractNodeLinkGraphicsItem::boundingRect() const
{
    return (d_ptr->_boundingRect);
}


void FCAbstractNodeLinkGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen pen(FCNodePalette::getGlobalLinkLineColor());

    painter->setPen(pen);
    painter->drawLine(d_ptr->_fromPos, d_ptr->_toPos);
    painter->restore();
}


bool FCAbstractNodeLinkGraphicsItem::attachFrom(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl)
{
    if (!item->isHaveLinkPoint(pl)) {
        qDebug() << QObject::tr("item have not in put link point:") << pl;
        return (false);
    }
    if (!pl.isOutput()) {
        //from必须从out出发
        qDebug() << QObject::tr("link from must attach an output point");
        return (false);
    }
    d_ptr->_fromItem = item;
    d_ptr->_fromPoint = pl;
    return (true);
}


/**
 * @brief 清空from节点
 *
 * 在nodeitem删除时会触发
 */
void FCAbstractNodeLinkGraphicsItem::resetAttachFrom()
{
    d_ptr->_fromItem = nullptr;
    d_ptr->_fromPoint = FCNodeLinkPoint();
}


bool FCAbstractNodeLinkGraphicsItem::attachTo(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl)
{
    if (!item->isHaveLinkPoint(pl)) {
        qDebug() << QObject::tr("item have not in put link point:") << pl;
        return (false);
    }
    if (!pl.isInput()) {
        //to必须到in
        qDebug() << QObject::tr("link to must attach an input point");
        return (false);
    }
    d_ptr->_toItem = item;
    d_ptr->_toPoint = pl;
    return (true);
}


void FCAbstractNodeLinkGraphicsItem::resetAttachTo()
{
    d_ptr->_toItem = nullptr;
    d_ptr->_toPoint = FCNodeLinkPoint();
}


QVariant FCAbstractNodeLinkGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    switch (change)
    {
    case QGraphicsItem::ItemSceneChange:
        updateBoundingRect();
        break;

    default:
        break;
    }
    return (QGraphicsItem::itemChange(change, value));
}


void FCAbstractNodeLinkGraphicsItem::callItemIsDestroying(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& pl)
{
    if ((d_ptr->_fromItem == item) && (d_ptr->_fromPoint == pl)) {
        //说明from要取消
        d_ptr->_fromItem = nullptr;
        d_ptr->_fromPoint = FCNodeLinkPoint();
    }else if ((d_ptr->_toItem == item) && (d_ptr->_toPoint == pl)) {
        //说明to要取消
        d_ptr->_toItem = nullptr;
        d_ptr->_toPoint = FCNodeLinkPoint();
    }
    //如果from和to都为空，这时就需要自动销毁
    FCNodeGraphicsScene *sc = d_ptr->nodeScene();

    if (sc) {
        sc->callNodeItemLinkIsEmpty(this);
    }
}
