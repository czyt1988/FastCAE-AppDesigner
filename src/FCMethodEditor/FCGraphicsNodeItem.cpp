#include "FCGraphicsNodeItem.h"
#include <QColor>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
#include "FCGraphicsNodeLinkLineItem.h"
#include "FCGraphicsScene.h"
QColor FCGraphicsNodeItem::s_hoverColor = QColor(0, 0, 200, 0);
QColor FCGraphicsNodeItem::s_selectEdgetColor = QColor(5, 124, 242);



FCGraphicsNodeItem::FCGraphicsNodeItem(FCNode *node, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_node(node)
    , m_showConnectPointName(false)
    , m_updateAndCallScene(false)
{
    setPos(node->getPos());
    setRotation(node->getRotation());
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    setTransformOriginPoint(boundingRect().center());
    m_lastMovePos = pos();
}


QRectF FCGraphicsNodeItem::boundingRect() const
{
    return (m_node->getBoundingRect().adjusted(-3, -3, 3, 3));
}


QPainterPath FCGraphicsNodeItem::shape() const
{
    QPainterPath path;

    path.addRect(m_node->getBoundingRect());
    return (path);
}


void FCGraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    QColor penColor = Qt::black;
    int edgeWidget = 0;

    if (option->state & QStyle::State_MouseOver && option->state & QStyle::State_Selected) {
        s_hoverColor.setAlpha(100);
        edgeWidget = 2;
        penColor = s_selectEdgetColor.darker();
    }else if (option->state & QStyle::State_MouseOver && !(option->state & QStyle::State_Selected)) {
        s_hoverColor.setAlpha(50);
        edgeWidget = 1;
    }else if (!(option->state & QStyle::State_MouseOver) && option->state & QStyle::State_Selected) {
        s_hoverColor.setAlpha(0);
        edgeWidget = 2;
        penColor = s_selectEdgetColor;
    }else {
        s_hoverColor.setAlpha(0);
    }
    //绘制图片
    painter->drawPixmap(m_node->getPixmapRect(), m_node->getPixmap());
    //set Pen
    QPen pen(Qt::SolidLine);

    pen.setColor(penColor);
    pen.setWidth(edgeWidget);
    painter->setPen(pen);
    painter->setBrush(QBrush(s_hoverColor));
    painter->drawRect(m_node->getBoundingRect());
    //
    QBrush brush;

    brush.setColor(Qt::black);
    painter->setBrush(brush);
    int connectPointSize = m_node->getConnectPointCount();

    for (int i = 0; i < connectPointSize; ++i)
    {
        QPointF p = m_node->getConnectPointByIndex(i);
        QRectF r(0, 0, 4, 4);
        r.moveCenter(p);
        painter->drawRect(r);
    }
}


/**
 * @brief 获取连接点数目
 * @return
 */
int FCGraphicsNodeItem::getConnectPointCount() const
{
    return (m_node->getConnectPointCount());
}


QPointF FCGraphicsNodeItem::getConnectPointByIndex(int index) const
{
    return (m_node->getConnectPointByIndex(index));
}


QPointF FCGraphicsNodeItem::getConnectPoint(const QString& name) const
{
    return (m_node->getConnectPoint(name));
}


void FCGraphicsNodeItem::addLink(FCGraphicsNodeLinkLineItem *item)
{
    m_links.insert(item);
}


FCNode *FCGraphicsNodeItem::getNode() const
{
    return (m_node);
}


/**
 * @brief 通过节点的内容更新信息，此函数不会触发scene的变换信号防止递归调用信号
 */
void FCGraphicsNodeItem::updateDataByValue()
{
    m_updateAndCallScene = false;
    if (m_node) {
        setPos(m_node->getPos());
        setRotation(m_node->getRotation());
        update();
    }
    m_updateAndCallScene = true;
}


void FCGraphicsNodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//    if (Qt::LeftButton == event->button()) {
//        GProjectGraphicsScene *sc = qobject_cast<GProjectGraphicsScene *>(scene());
//        if (sc) {
//            sc->callNodeDoubleClicked(this);
//        }
//    }
}


void FCGraphicsNodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_node->setPos(pos());
    if (Qt::RightButton == event->button()) {
        qreal ro = rotation();
        ro += 90;
        if (ro >= 360) {
            ro = 0;
        }
        setRotation(ro);
        m_node->setRotation(ro);
    }else if (Qt::LeftButton == event->button()) {
        //左键点击，更新一下位置信息
        m_lastMovePos = pos();
    }
    QGraphicsItem::mousePressEvent(event);
    update();
}


void FCGraphicsNodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_node->setPos(pos());
    QGraphicsItem::mouseMoveEvent(event);
    update();
}


void FCGraphicsNodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_node->setPos(pos());
    //qDebug() << "mouseReleaseEvent:" << m_node->getPos();
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}


QVariant FCGraphicsNodeItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if (FCGraphicsScene *sc = qobject_cast<FCGraphicsScene *>(scene())) {
        //qDebug() <<change;
        switch (change)
        {
        case QGraphicsItem::ItemPositionHasChanged:
        {
            QPointF newPos = value.toPointF();
            m_node->setPos(pos());
            updateLinkItem();
            if (m_updateAndCallScene) {
                sc->callNodePositionChanged(this);
            }
            break;
        }

        case QGraphicsItem::ItemRotationHasChanged:
        {
            qreal ro = value.toDouble();
            setRotation(ro);
            updateLinkItem();
            if (m_updateAndCallScene) {
                sc->callNodeRotationChanged(this);
            }
            break;
        }

        default:
            break;
        }
    }
    return (QGraphicsItem::itemChange(change, value));
}


void FCGraphicsNodeItem::callLinkDelete(FCGraphicsNodeLinkLineItem *link)
{
    m_links.remove(link);
}


void FCGraphicsNodeItem::updateLinkItem()
{
    QSet<FCGraphicsNodeLinkLineItem *>::iterator ite = m_links.begin();

    for ( ; ite != m_links.end(); ++ite)
    {
        (*ite)->updateNodePos();
        (*ite)->update();
    }
}


/**
 * @brief 获取移动前的位置，鼠标点击时会记录此坐标
 * @return
 */
QPointF FCGraphicsNodeItem::getLastMovePos() const
{
    return (m_lastMovePos);
}
