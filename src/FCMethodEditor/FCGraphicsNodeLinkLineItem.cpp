#include "FCGraphicsNodeLinkLineItem.h"
//C
#include <math.h>
//Qt
#include <QDebug>
#include <QStyleOptionGraphicsItem>

//Local
#include "FCGraphicsNodeItem.h"
#include "FCGraphicsScene.h"


FCGraphicsNodeLinkLineItem::FCGraphicsNodeLinkLineItem(FCNodeLink *link, QGraphicsItem *parent) : QGraphicsItem(parent)
    , m_linkPen(Qt::black)
    , m_link(link)
    , m_hoverColor(52, 185, 250)
    , m_lineWidth(2)
    , m_p0(0, 0)
    , m_p1(100, 100)
    , m_boundingRect(-3, -3, 106, 106)
    , m_externLength(15)
    , m_updateAndCallScene(false)
{
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    updateNodePos();
}


FCGraphicsNodeLinkLineItem::~FCGraphicsNodeLinkLineItem()
{
    FCGraphicsScene *sc = qobject_cast<FCGraphicsScene *>(scene());

    if (sc) {
        FCNode *node0 = m_link->from();
        FCNode *node1 = m_link->to();
        if (node0) {
            FCGraphicsNodeItem *item = sc->nodeToItem(node0);
            if (item) {
                item->callLinkDelete(this);
            }
        }
        if (node1) {
            FCGraphicsNodeItem *item = sc->nodeToItem(node1);
            if (item) {
                item->callLinkDelete(this);
            }
        }
    }
}


void FCGraphicsNodeLinkLineItem::setLinkPen(const QPen& pen)
{
    m_linkPen = pen;
}


QPen FCGraphicsNodeLinkLineItem::getLinkPen() const
{
    return (m_linkPen);
}


QRectF FCGraphicsNodeLinkLineItem::boundingRect() const
{
    return (m_boundingRect);
}


QPainterPath FCGraphicsNodeLinkLineItem::shape() const
{
    return (m_linePainterPath);
}


void FCGraphicsNodeLinkLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (nullptr == m_link) {
        return;
    }
    painter->setRenderHint(QPainter::Antialiasing);

    int width = m_lineWidth;
    QPen pen = m_linkPen;

    if (option->state & QStyle::State_MouseOver && option->state & QStyle::State_Selected) {
        pen.setColor(m_hoverColor);
        pen.setWidth(width+1);
    }else if (option->state & QStyle::State_MouseOver && !(option->state & QStyle::State_Selected)) {
        pen.setColor(m_hoverColor);
        pen.setWidth(width+1);
    }else if (!(option->state & QStyle::State_MouseOver) && option->state & QStyle::State_Selected) {
        pen.setColor(pen.color().darker());
        pen.setWidth(width+1);
    }
    painter->setPen(pen);



    painter->setBrush(Qt::NoBrush);
    //painter->drawRect(QRectF(0,0,abs(m_p1.x()-m_p0.x()),abs(m_p1.y()-m_p0.y())));

    painter->drawLines(m_drawLines);
    //绘制箭头
    painter->setPen(Qt::NoPen);
    painter->setBrush(pen.color());
    painter->drawPath(m_arrowPainterPath);
}


///
/// \brief 更新节点信息并生成节点连线方式
///
/// 目前只用简单的平行交叉式连接线生成方案，后续如果节点复杂，应该考虑曼哈顿路由等比较适应度高的图算法
///
void FCGraphicsNodeLinkLineItem::updateNodePos()
{
    FCGraphicsScene *sc = qobject_cast<FCGraphicsScene *>(scene());
    FCNode *node0 = m_link->from();
    FCNode *node1 = m_link->to();

    if (nullptr == sc) {
        qDebug() << "none attach";
        return;
    }
    if ((nullptr == node0) && (nullptr == node1)) {
        qDebug() << "none attach";
        return;
    }
    FCGraphicsNodeItem *item0 = sc->nodeToItem(node0);

    if (item0) {
        item0->addLink(this);
        //node1BorundRectToScene = item0->mapToScene(item0->boundingRect());//获取node的范围
    }
    FCGraphicsNodeItem *item1 = sc->nodeToItem(node1);

    if (item1) {
        item1->addLink(this);
        //node2BorundRectToScene = item0->mapToScene(item0->boundingRect());//获取node的范围
    }

    if ((nullptr != node0) && (nullptr == node1)) {
        QPointF cp = m_link->getFromNodeConnectPoint();
        if (item0) {
            m_p0 = item0->mapToScene(cp);
        }else {
            QPointF pos = node0->getPos();
            m_p0 = pos + cp;
        }
        m_pExtern1 = m_p1;
    }else if ((nullptr == node0) && (nullptr != node1)) {
        QPointF cp = m_link->getToNodeConnectPoint();
        if (item1) {
            m_p1 = item1->mapToScene(cp);
        }else {
            QPointF pos = node1->getPos();
            m_p1 = pos + cp;
        }
        m_pExtern0 = m_p0;
    }else {
        QPointF cp0 = m_link->getFromNodeConnectPoint();
        QPointF cp1 = m_link->getToNodeConnectPoint();

        if (item0) {
            m_p0 = item0->mapToScene(cp0);
        }else {
            QPointF pos = node0->getPos();
            m_p0 = pos + cp0;
        }
        if (item1) {
            m_p1 = item1->mapToScene(cp1);
        }else {
            QPointF pos = node1->getPos();
            m_p1 = pos + cp1;
        }
    }

    //上面是计算连接点和延生连接点的坐标，下面函数用于生成连接线
    updateLine();
    updateBoundingRect();
}


///
/// \brief 生成箭头的painterPath虚函数，使用虚函数是为了以后可能改为策略模式
/// \param from 箭头的开始点，这里将会传入m_pExtern1
/// \param end 箭头的结束点，这里将会传入m_p1
/// \return 返回箭头
///
QPainterPath FCGraphicsNodeLinkLineItem::generateArrowPath(const QPointF& from, const QPointF& end)
{
    //首先定义箭头线投影到两点间的百分比
    qreal present = 1;
    //定义旋转角度
    qreal rotationDegree = 20;
    //箭头的收纳点比例，收纳点比例要比present小，否则就成菱形箭头
    qreal constringencyPresent = present*0.7;



    //把坐标点转换为to点为（0，0）点
    QPointF fp = from - end;
    //此时相当于fp 点-> (0,0)

    //建立转换矩阵
    QTransform tf;

    tf.scale(present, present);//先进行缩放
    //获取箭头的一个端点 --
    tf.rotate(rotationDegree);
    QPointF pArr0 = tf.map(fp);

    //获取箭头的另个端点 --
    tf.rotate(-2.0*rotationDegree);
    QPointF pArr1 = tf.map(fp);

    //对于某些箭头还会有收纳点收纳点在箭头的连线上

    tf.reset();
    tf.scale(constringencyPresent, constringencyPresent);
    QPointF pConstringencyArr = tf.map(fp);

    //生成绘制箭头，从收纳点开始，点需要和to进行映射还原坐标
    QPolygonF polygon;

    polygon.push_back(pConstringencyArr+end);
    polygon.push_back(pArr0+end);
    polygon.push_back(end);
    polygon.push_back(pArr1+end);
    polygon.push_back(pConstringencyArr+end);
    QPainterPath path;

    path.addPolygon(polygon);
    return (path);
}


/**
 * @brief 生成连接点
 *
 * 根据提供的p0,pExtern0和p1,pExtern1生成连接点，p0,pExtern0和p1,pExtern1都是已经偏移好的相对此图元的坐标点
 *
 * 目前只用简单的平行交叉式连接线生成方案，后续如果节点复杂，应该考虑曼哈顿路由等比较适应度高的图算法
 *
 * 平行交叉式就是根据p0，pExtern0生成的延长线和p1，pExtern1生成的延长线的交点作为拐点
 *
 * @param p0 连接的起始点
 * @param pExtern0 连接的延长点，延长点和起始点确定了连接线的伸出方向
 * @param p1 连接的终点
 * @param pExtern1 连接终点延长线，延长点和终止点确定了连接线终结时的方向
 * @return 生成的沿途各点
 */
QVector<QPointF> FCGraphicsNodeLinkLineItem::generateConnectPoints(const QPointF& p0, const QPointF& pExtern0
    , const QPointF& p1, const QPointF& pExtern1)
{
    //获取两个线的交点
    QVector<QPointF> resPoints;
    QVector<QPointF> connectPoints;

//    //先确定两个方向
//    FCNode::Dirction dir0 = FCNode::checkDirection(p0, pExtern0);
//    FCNode::Dirction dir1 = FCNode::checkDirection(p1, pExtern1);

//    //判断是否是平行，目前不是水平就是垂直
//    if (!FCNode::isDirectionParallelism(dir0, dir1)) {
//        connectPoints = _generateConnectPointsNotParallelism(pExtern0, pExtern1, dir0, dir1);
//    }else {
//        //平行
//        connectPoints = _generateConnectPointsParallelism(pExtern0, pExtern1, dir0, dir1);
//    }
//    resPoints << p0 << pExtern0 << connectPoints << pExtern1 << p1;
    return (resPoints);
}


///
/// \brief 根据m_p0，m_p1，m_pExtern0，m_pExtern1更新线条
///
/// 目前只用简单的平行交叉式连接线生成方案，后续如果节点复杂，应该考虑曼哈顿路由等比较适应度高的图算法
///
/// 平行交叉式就是根据m_p0，m_pExtern0生成的延长线和m_p1，m_pExtern1生成的延长线的交点作为拐点
///
/// 如果两个延长线无交点，就是两个延长线平行，那么会采取以下策略：选取m_pExtern0，m_pExtern1组成的矩形的中间点作为交叉点
///
void FCGraphicsNodeLinkLineItem::updateLine()
{
    m_drawLines.clear();
    m_mapOrigionPoint.rx() = qMin(qMin(qMin(m_p1.x(), m_p0.x()), m_pExtern0.x()), m_pExtern1.x());
    m_mapOrigionPoint.ry() = qMin(qMin(qMin(m_p1.y(), m_p0.y()), m_pExtern0.y()), m_pExtern1.y());

    QVector<QPointF> res = generateConnectPoints(m_p0-m_mapOrigionPoint, m_pExtern0-m_mapOrigionPoint
        , m_p1-m_mapOrigionPoint, m_pExtern1-m_mapOrigionPoint);

    m_arrowPainterPath = generateArrowPath(m_pExtern1-m_mapOrigionPoint, m_p1-m_mapOrigionPoint);
    QRectF arrorRect = m_arrowPainterPath.boundingRect();
    qreal minX = res[0].x()
    , minY = res[0].y()
    , maxX = res[0].x()
    , maxY = res[0].y();
    QPainterPath linePainterPath;

    linePainterPath.moveTo(res[0]);
    for (int i = 1; i < res.size(); ++i)
    {
        m_drawLines.append(QLineF(res[i-1], res[i]));
        minX = qMin(res[i].x(), minX);
        minY = qMin(res[i].y(), minY);
        maxX = qMax(res[i].x(), maxX);
        maxY = qMax(res[i].y(), maxY);
        //把线段的区域加入，让shape可以选择到连接线
        int dx = abs(res[i].x() - res[i-1].x());
        int dy = abs(res[i].y() - res[i-1].y());
        QRectF rect;//记录线段的矩形
        if (dx <= 0) {
            dx = 6;
            rect.setTopLeft(QPointF(res[i].x()-dx/2.0, qMin(res[i].y(), res[i-1].y())));
        }else {
            dy = 6;
            rect.setTopLeft(QPointF(qMin(res[i].x(), res[i-1].x()), res[i].y()-dy/2.0));
        }
        rect.setWidth(dx);
        rect.setHeight(dy);
        linePainterPath.addRect(rect);
    }
    minX = qMin(arrorRect.left(), minX);
    minY = qMin(arrorRect.top(), minY);
    maxX = qMax(arrorRect.right(), maxX);
    maxY = qMax(arrorRect.bottom(), maxY);
    prepareGeometryChange();
    m_boundingRect = QRectF(minX, minY, maxX-minX, maxY-minY);

    //linePainterPath.addRect(m_boundingRect);
    m_linePainterPath = linePainterPath | m_arrowPainterPath;

    //m_linePainterPath = m_arrowPainterPath|p;

    setPos(m_mapOrigionPoint);
}


void FCGraphicsNodeLinkLineItem::updateBoundingRect()
{
    //prepareGeometryChange();

    /*
     * int maxArrowRange = qMax(m_arrowRect.width(),m_arrowRect.height());
     * qreal xmin = qMin(qMin(qMin(m_p1.x(),m_p0.x()),m_pExtern0.x()),m_pExtern1.x());
     * qreal xmax = qMax(qMax(qMax(m_p1.x(),m_p0.x()),m_pExtern0.x()),m_pExtern1.x());
     * qreal ymin = qMin(qMin(qMin(m_p1.y(),m_p0.y()),m_pExtern0.y()),m_pExtern1.y());
     * qreal ymax = qMax(qMax(qMax(m_p1.y(),m_p0.y()),m_pExtern0.y()),m_pExtern1.y());
     * m_boundingRect = QRectF(0,0,xmax - xmin,ymax - ymin)
     *      .adjusted(-maxArrowRange,-maxArrowRange,maxArrowRange,maxArrowRange);
     */
    //m_boundingRect = m_linePainterPath.boundingRect();
}


/**
 * @brief 获取代理的连接指针
 * @return
 */
FCNodeLink *FCGraphicsNodeLinkLineItem::getLink() const
{
    return (m_link);
}


/**
 * @brief 更新显示-在FCNodeLink内容更新后调用此函数刷新
 */
void FCGraphicsNodeLinkLineItem::updateDataByValue()
{
    m_updateAndCallScene = false;
    if (m_link) {
        update();
    }
    m_updateAndCallScene = true;
}
