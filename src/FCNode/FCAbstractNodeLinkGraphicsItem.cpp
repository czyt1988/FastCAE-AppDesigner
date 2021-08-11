#include "FCAbstractNodeLinkGraphicsItem.h"
#include <QPainter>
#include <QDebug>
#include "FCAbstractNodeGraphicsItem.h"
#include "FCNodeGraphicsScene.h"
#include "FCNodePalette.h"
#include <math.h>
#include <QGraphicsSimpleTextItem>

class FCAbstractNodeLinkGraphicsItemPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeLinkGraphicsItem)
public:
    FCAbstractNodeLinkGraphicsItemPrivate(FCAbstractNodeLinkGraphicsItem *p);
    FCNodeGraphicsScene *nodeScene() const;
    void setTextVisible(bool on, FCAbstractNodeLinkGraphicsItem::Orientations o);
    bool isTextVisible(FCAbstractNodeLinkGraphicsItem::Orientations o) const;
    void updateText(QGraphicsSimpleTextItem *item, const QPointF& p, const FCNodeLinkPoint& pl, int offset);
    void updateText();
    void setPointTextColor(const QColor& c, FCAbstractNodeLinkGraphicsItem::Orientations o);
    QColor getPointTextColor(FCAbstractNodeLinkGraphicsItem::Orientations o) const;
    void setPointTextPositionOffset(int offset, FCAbstractNodeLinkGraphicsItem::Orientations o);
    int getPointTextPositionOffset(FCAbstractNodeLinkGraphicsItem::Orientations o) const;

    FCAbstractNodeGraphicsItem *_fromItem;
    FCAbstractNodeGraphicsItem *_toItem;
    FCNodeLinkPoint _fromPoint;
    FCNodeLinkPoint _toPoint;
    QPointF _fromPos;
    QPointF _toPos;
    QRectF _boundingRect;           ///< 记录boundingRect
    qreal _bezierControlScale;      ///<贝塞尔曲线的控制点的缩放比例
    QPainterPath _linePath;         ///< 通过点得到的绘图线段
    QPen _linePen;                  ///< 线的画笔
    QGraphicsSimpleTextItem *_fromTextItem;
    QGraphicsSimpleTextItem *_toTextItem;
    QPair<int, int> _pointTextPositionOffset;///< 记录文本和连接点的偏移量，默认为10
};

FCAbstractNodeLinkGraphicsItemPrivate::FCAbstractNodeLinkGraphicsItemPrivate(FCAbstractNodeLinkGraphicsItem *p)
    : q_ptr(p)
    , _fromItem(nullptr)
    , _toItem(nullptr)
    , _fromPos(0, 0)
    , _toPos(100, 100)
    , _boundingRect(0, 0, 100, 100)
    , _bezierControlScale(0.25)
    , _pointTextPositionOffset(10, 10)
{
    _linePen = QPen(FCNodePalette::getGlobalLinkLineColor());
    _fromTextItem = new QGraphicsSimpleTextItem(p);
    _toTextItem = new QGraphicsSimpleTextItem(p);
    setTextVisible(false, FCAbstractNodeLinkGraphicsItem::OrientationBoth);
}


FCNodeGraphicsScene *FCAbstractNodeLinkGraphicsItemPrivate::nodeScene() const
{
    return (qobject_cast<FCNodeGraphicsScene *>(q_ptr->scene()));
}


void FCAbstractNodeLinkGraphicsItemPrivate::setTextVisible(bool on, FCAbstractNodeLinkGraphicsItem::Orientations o)
{
    switch (o)
    {
    case FCAbstractNodeLinkGraphicsItem::OrientationFrom:
        _fromTextItem->setVisible(on);
        break;

    case FCAbstractNodeLinkGraphicsItem::OrientationTo:
        _toTextItem->setVisible(on);
        break;

    default:
        _fromTextItem->setVisible(on);
        _toTextItem->setVisible(on);
        break;
    }
}


bool FCAbstractNodeLinkGraphicsItemPrivate::isTextVisible(FCAbstractNodeLinkGraphicsItem::Orientations o) const
{
    switch (o)
    {
    case FCAbstractNodeLinkGraphicsItem::OrientationFrom:
        return (_fromTextItem->isVisible());

    case FCAbstractNodeLinkGraphicsItem::OrientationTo:
        return (_toTextItem->isVisible());

    default:
        break;
    }
    return (_fromTextItem->isVisible() && _toTextItem->isVisible());
}


void FCAbstractNodeLinkGraphicsItemPrivate::updateText(QGraphicsSimpleTextItem *item, const QPointF& p, const FCNodeLinkPoint& pl, int offset)
{
    item->setText(pl.name);
    int hoff = item->boundingRect().height();

    hoff /= 2;
    int w = item->boundingRect().width();

    switch (pl.direction)
    {
    case FCNodeLinkPoint::East:
        item->setRotation(0);
        item->setPos(p.x()+offset, p.y()-hoff);
        break;

    case FCNodeLinkPoint::South:
        item->setRotation(90);
        item->setPos(p.x()+hoff, p.y()+offset);
        break;

    case FCNodeLinkPoint::West:
        item->setRotation(0);
        item->setPos(p.x()-w-offset, p.y()-hoff);
        break;

    case FCNodeLinkPoint::North:
        item->setRotation(90);
        item->setPos(p.x()+hoff, p.y()-w-offset);
        break;

    default:
        break;
    }
}


void FCAbstractNodeLinkGraphicsItemPrivate::updateText()
{
    updateText(_fromTextItem, _fromPos, _fromPoint, _pointTextPositionOffset.first);
    updateText(_toTextItem, _toPos, _toPoint, _pointTextPositionOffset.second);
}


void FCAbstractNodeLinkGraphicsItemPrivate::setPointTextColor(const QColor& c, FCAbstractNodeLinkGraphicsItem::Orientations o)
{
    switch (o)
    {
    case FCAbstractNodeLinkGraphicsItem::OrientationFrom:
        _fromTextItem->setBrush(c);
        break;

    case FCAbstractNodeLinkGraphicsItem::OrientationTo:
        _toTextItem->setBrush(c);
        break;

    default:
        _fromTextItem->setBrush(c);
        _toTextItem->setBrush(c);
        break;
    }
}


QColor FCAbstractNodeLinkGraphicsItemPrivate::getPointTextColor(FCAbstractNodeLinkGraphicsItem::Orientations o) const
{
    switch (o)
    {
    case FCAbstractNodeLinkGraphicsItem::OrientationFrom:
        return (_fromTextItem->brush().color());

    case FCAbstractNodeLinkGraphicsItem::OrientationTo:
        return (_toTextItem->brush().color());

    default:
        break;
    }
    return (QColor());
}


void FCAbstractNodeLinkGraphicsItemPrivate::setPointTextPositionOffset(int offset, FCAbstractNodeLinkGraphicsItem::Orientations o)
{
    switch (o)
    {
    case FCAbstractNodeLinkGraphicsItem::OrientationFrom:
        _pointTextPositionOffset.first = offset;
        break;

    case FCAbstractNodeLinkGraphicsItem::OrientationTo:
        _pointTextPositionOffset.second = offset;
        break;

    default:
        _pointTextPositionOffset.first = offset;
        _pointTextPositionOffset.second = offset;
        break;
    }
}


int FCAbstractNodeLinkGraphicsItemPrivate::getPointTextPositionOffset(FCAbstractNodeLinkGraphicsItem::Orientations o) const
{
    switch (o)
    {
    case FCAbstractNodeLinkGraphicsItem::OrientationFrom:
        return (_pointTextPositionOffset.first);

    case FCAbstractNodeLinkGraphicsItem::OrientationTo:
        return (_pointTextPositionOffset.second);

    default:
        break;
    }
    return (0);
}


////////////////////////////////////////////////////////////////////////



FCAbstractNodeLinkGraphicsItem::FCAbstractNodeLinkGraphicsItem(QGraphicsItem *p)
    : QGraphicsItem(p)
    , d_ptr(new FCAbstractNodeLinkGraphicsItemPrivate(this))
{
    setFlags(flags() | ItemIsSelectable);
}


FCAbstractNodeLinkGraphicsItem::FCAbstractNodeLinkGraphicsItem(FCAbstractNodeGraphicsItem *from, FCNodeLinkPoint pl, QGraphicsItem *p)
    : QGraphicsItem(p)
    , d_ptr(new FCAbstractNodeLinkGraphicsItemPrivate(this))
{
    setFlags(flags() | ItemIsSelectable);
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
        d_ptr->_boundingRect = d_ptr->_linePath.boundingRect().adjusted(-2, -2, 2, 2);//留足选中后画笔变宽的绘制余量
        return;
    } else if ((d_ptr->_fromItem != nullptr) && (d_ptr->_toItem == nullptr)) {
        //只设定了一个from
        // to要根据scene的鼠标位置实时刷新
        d_ptr->_toPos = mapFromScene(sc->getCurrentMouseScenePos());
        d_ptr->_toPoint.direction = generateOppositeDirection(d_ptr->_fromPoint.direction);
        generatePainterPath();
        d_ptr->_boundingRect = d_ptr->_linePath.boundingRect().adjusted(-2, -2, 2, 2);//留足选中后画笔变宽的绘制余量
    } else if ((d_ptr->_fromItem != nullptr) && (d_ptr->_toItem != nullptr)) {
        //两个都不为空
        d_ptr->_toPos = mapFromItem(d_ptr->_toItem, d_ptr->_toPoint.position);
        generatePainterPath();
        d_ptr->_boundingRect = d_ptr->_linePath.boundingRect().adjusted(-2, -2, 2, 2);//留足选中后画笔变宽的绘制余量
    }else{
        generatePainterPath();
        d_ptr->_boundingRect = d_ptr->_linePath.boundingRect().adjusted(-2, -2, 2, 2);//留足选中后画笔变宽的绘制余量
        qDebug()	<< "occ unknow link type,please check!, from item:" << d_ptr->_fromItem
                << " to item:" << d_ptr->_toItem
        ;
    }
    d_ptr->updateText();
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
    d_ptr->_bezierControlScale = rate;
}


/**
 * @brief 获取贝塞尔曲线的控制点的缩放比例
 * @return
 */
qreal FCAbstractNodeLinkGraphicsItem::getBezierControlScale() const
{
    return (d_ptr->_bezierControlScale);
}


/**
 * @brief 设置线的画笔
 * @param p
 */
void FCAbstractNodeLinkGraphicsItem::setLinePen(const QPen& p)
{
    d_ptr->_linePen = p;
}


/**
 * @brief 返回当前画笔
 * @return
 */
QPen FCAbstractNodeLinkGraphicsItem::getLinePen() const
{
    return (d_ptr->_linePen);
}


/**
 * @brief 设置是否显示连接点的文本
 * @param on
 */
void FCAbstractNodeLinkGraphicsItem::setPointTextVisible(bool on, Orientations o)
{
    d_ptr->setTextVisible(on, o);
}


/**
 * @brief 是否显示连接点的文本
 * @return
 */
bool FCAbstractNodeLinkGraphicsItem::isPointTextVisible(Orientations o) const
{
    return (d_ptr->isTextVisible(o));
}


/**
 * @brief 设置连接点显示的颜色
 * @param c
 * @param o
 */
void FCAbstractNodeLinkGraphicsItem::setPointTextColor(const QColor& c, FCAbstractNodeLinkGraphicsItem::Orientations o)
{
    d_ptr->setPointTextColor(c, o);
}


/**
 * @brief 获取连接点显示的颜色
 * @param o 不能指定OrientationBoth，指定OrientationBoth返回QColor()
 * @return
 */
QColor FCAbstractNodeLinkGraphicsItem::getPointTextColor(FCAbstractNodeLinkGraphicsItem::Orientations o) const
{
    return (d_ptr->getPointTextColor(o));
}


/**
 * @brief 设置文本和连接点的偏移量，默认为10
 * @param offset
 * @param o
 */
void FCAbstractNodeLinkGraphicsItem::setPointTextPositionOffset(int offset, FCAbstractNodeLinkGraphicsItem::Orientations o)
{
    d_ptr->setPointTextPositionOffset(offset, o);
}


/**
 * @brief 文本和连接点的偏移量
 * @param o 不能指定OrientationBoth，指定OrientationBoth返回0
 * @return 指定OrientationBoth返回0
 */
int FCAbstractNodeLinkGraphicsItem::getPointTextPositionOffset(FCAbstractNodeLinkGraphicsItem::Orientations o) const
{
    return (d_ptr->getPointTextPositionOffset(o));
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
    QPen pen = d_ptr->_linePen;

    if (isSelected()) {
        pen.setWidth(pen.width()+2);
        pen.setColor(pen.color().darker(150));
    }
    painter->setPen(pen);
    painter->drawPath(d_ptr->_linePath);
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
    d_ptr->updateText();
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
    d_ptr->updateText();
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
    case QGraphicsItem::ItemSelectedHasChanged:
        setPointTextVisible(value.toBool());
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
