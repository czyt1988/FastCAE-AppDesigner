#include "FCAbstractNodeLinkGraphicsItem.h"
#include <QPainter>
#include <QDebug>
#include "FCAbstractNodeGraphicsItem.h"
#include "FCNodeGraphicsScene.h"
#include "FCNodePalette.h"
#include <math.h>
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
    QRectF _boundingRect;           ///< 记录boundingRect
    qreal _bezierControlScale;      ///<贝塞尔曲线的控制点的缩放比例
    QPainterPath _linePath;         ///< 通过点得到的绘图线段
};

FCAbstractNodeLinkGraphicsItemPrivate::FCAbstractNodeLinkGraphicsItemPrivate(FCAbstractNodeLinkGraphicsItem *p)
    : q_ptr(p)
    , _fromItem(nullptr)
    , _toItem(nullptr)
    , _fromPos(0, 0)
    , _toPos(100, 100)
    , _boundingRect(0, 0, 100, 100)
    , _bezierControlScale(0.25)
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
    resetAttachFrom();
    resetAttachTo();
}


/**
 * @brief 自动根据fromitem来更新位置
 * @note 如果设置了toitem，会调用@sa updateBoundingRect 来更新boundingRect
 */
void FCAbstractNodeLinkGraphicsItem::updatePos()
{
    FCNodeGraphicsScene *sc = d_ptr->nodeScene();

    if ((nullptr == d_ptr->_fromItem) || (nullptr == sc)) {
        return;
    }
    setPos(d_ptr->_fromItem->mapToScene(d_ptr->_fromPoint.position));
    if (d_ptr->_toItem) {
        updateBoundingRect();
    }
}


void FCAbstractNodeLinkGraphicsItem::updateBoundingRect()
{
    FCNodeGraphicsScene *sc = d_ptr->nodeScene();

    if (nullptr == sc) {
        return;
    }
    //通过调用prepareGeometryChange()通知范围变更，避免出现残影
    prepareGeometryChange();
    d_ptr->_fromPos = QPointF(0, 0);
    d_ptr->_toPos = QPointF(100, 100);
    if ((d_ptr->_fromItem == nullptr) && (d_ptr->_toItem == nullptr)) {
        //都是空退出
        d_ptr->_fromPoint.direction = FCNodeLinkPoint::East;
        d_ptr->_toPoint.direction = FCNodeLinkPoint::West;
        generatePainterPath();
        d_ptr->_boundingRect = d_ptr->_linePath.boundingRect();
        return;
    } else if ((d_ptr->_fromItem != nullptr) && (d_ptr->_toItem == nullptr)) {
        //只设定了一个from
        // to要根据scene的鼠标位置实时刷新
        d_ptr->_toPos = mapFromScene(sc->getCurrentMouseScenePos());
        d_ptr->_toPoint.direction = generateOppositeDirection(d_ptr->_fromPoint.direction);
        generatePainterPath();
        d_ptr->_boundingRect = d_ptr->_linePath.boundingRect();
    } else if ((d_ptr->_fromItem != nullptr) && (d_ptr->_toItem != nullptr)) {
        //两个都不为空
        d_ptr->_toPos = mapFromItem(d_ptr->_toItem, d_ptr->_toPoint.position);
        generatePainterPath();
        d_ptr->_boundingRect = d_ptr->_linePath.boundingRect();
    }else{
        generatePainterPath();
        d_ptr->_boundingRect = d_ptr->_linePath.boundingRect();
        qDebug()	<< "occ unknow link type,please check!, from item:" << d_ptr->_fromItem
                << " to item:" << d_ptr->_toItem
        ;
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


/**
 * @brief 通过伸出点方向，得到贝塞尔曲线控制点的位置
 * @param orgPoint 原始点
 * @param d 伸出方向
 * @param externLen 伸出长度
 * @return 得到控制点
 */
QPointF FCAbstractNodeLinkGraphicsItem::calcCubicControlPoint(const QPointF& orgPoint, FCNodeLinkPoint::Direction d, qreal externLen)
{
    switch (d)
    {
    case FCNodeLinkPoint::East:
        return (QPointF(orgPoint.x()+externLen, orgPoint.y()));

    case FCNodeLinkPoint::South:
        return (QPointF(orgPoint.x(), orgPoint.y()+externLen));

    case FCNodeLinkPoint::West:
        return (QPointF(orgPoint.x()-externLen, orgPoint.y()));

    case FCNodeLinkPoint::North:
        return (QPointF(orgPoint.x(), orgPoint.y()-externLen));
    }
    return (orgPoint);
}


/**
 * @brief 计算两个点的距离
 * @param a
 * @param b
 * @return
 */
qreal FCAbstractNodeLinkGraphicsItem::pointLength(const QPointF& a, const QPointF& b)
{
    return (pow((a.x()-b.x())*(a.x()-b.x())+(a.y()-b.y())*(a.y()-b.y()), 0.5));
}


/**
 * @brief 通过a点的方向和a相对b的位置，生成一个相反的方向
 * @param a
 * @param ad
 * @param b
 * @return
 */
FCNodeLinkPoint::Direction FCAbstractNodeLinkGraphicsItem::generateOppositeDirection(FCNodeLinkPoint::Direction ad)
{
    switch (ad)
    {
    case FCNodeLinkPoint::East:
        return (FCNodeLinkPoint::West);

    case FCNodeLinkPoint::South:
        return (FCNodeLinkPoint::North);

    case FCNodeLinkPoint::West:
        return (FCNodeLinkPoint::East);

    case FCNodeLinkPoint::North:
        return (FCNodeLinkPoint::South);
    }
    return (ad);
}


/**
 * @brief 设置贝塞尔曲线的控制点的缩放比例
 *
 * FCAbstractNodeLinkGraphicsItem在连线时按照两个连接点的方向延伸出贝塞尔曲线的控制点，贝塞尔曲线的控制点的长度w = length * bezierControlScale，
 * 其中length是两个连接点的绝对距离，可以通过@sa pointLength 计算得到，bezierControlScale，就是这个延伸的比例，如果越大，曲率越明显
 * @param rate 默认为0.25
 */
void FCAbstractNodeLinkGraphicsItem::setBezierControlScale(qreal rate)
{
}


QRectF FCAbstractNodeLinkGraphicsItem::boundingRect() const
{
    return (d_ptr->_boundingRect);
}


QPainterPath FCAbstractNodeLinkGraphicsItem::shape() const
{
    return (d_ptr->_linePath);
}


void FCAbstractNodeLinkGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen pen(FCNodePalette::getGlobalLinkLineColor());

    painter->setPen(pen);
    painter->drawPath(d_ptr->_linePath);
    //painter->drawLine(d_ptr->_fromPos, d_ptr->_toPos);
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
    item->recordLink(this, pl);
    return (true);
}


/**
 * @brief 清空from节点
 *
 * 在nodeitem删除时会触发
 */
void FCAbstractNodeLinkGraphicsItem::resetAttachFrom()
{
    if (d_ptr->_fromItem) {
        d_ptr->_fromItem->callItemLinkIsDestroying(this, d_ptr->_fromPoint);
        d_ptr->_fromItem = nullptr;
    }
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
    item->recordLink(this, pl);
    return (true);
}


void FCAbstractNodeLinkGraphicsItem::resetAttachTo()
{
    if (d_ptr->_toItem) {
        d_ptr->_toItem->callItemLinkIsDestroying(this, d_ptr->_toPoint);
        d_ptr->_toItem = nullptr;
    }
    d_ptr->_toPoint = FCNodeLinkPoint();
}


/**
 * @brief 生成painterpath,默认会根据连接点生成一个贝塞尔曲线
 * 此函数在updateBoundingRect里调用
 */
void FCAbstractNodeLinkGraphicsItem::generatePainterPath()
{
    d_ptr->_linePath.clear();
    //贝塞尔的引导线根据伸出点的方向偏移两个点距离的1/5
    //! 1 先求出两个点距离
    qreal length = pointLength(d_ptr->_fromPos, d_ptr->_toPos);

    length *= d_ptr->_bezierControlScale;
    //! 2.通过伸出方向，得到两个控制点的位置
    QPointF fromcCrtlPoint = calcCubicControlPoint(d_ptr->_fromPos, d_ptr->_fromPoint.direction, length);
    QPointF toCrtlPoint = calcCubicControlPoint(d_ptr->_toPos, d_ptr->_toPoint.direction, length);

    //! 3.生成贝塞尔曲线
    d_ptr->_linePath.moveTo(d_ptr->_fromPos);
    d_ptr->_linePath.cubicTo(fromcCrtlPoint, toCrtlPoint, d_ptr->_toPos);
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
