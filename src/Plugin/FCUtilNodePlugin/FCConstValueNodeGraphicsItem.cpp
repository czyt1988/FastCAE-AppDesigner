#include "FCConstValueNodeGraphicsItem.h"
#include <QPainter>
#include "FCNodePalette.h"
#define RES_VARIANT    ":/icon/icon/variant.svg"
FCConstValueNodeGraphicsItem::FCConstValueNodeGraphicsItem(QGraphicsItem *p)
    : FCAbstractNodeGraphicsItem(p)
{
    metaData().setIcon(QIcon(RES_VARIANT));
    metaData().setNodePrototype("FC.Util.Const");
    metaData().setNodeName(QObject::tr("variant"));
    metaData().setGroup(QObject::tr("common"));
    QList<FCNodeLinkPoint>& lps = linkPoints();

    lps.append(FCNodeLinkPoint(QPoint(50-4, 25), "out", FCNodeLinkPoint::OutPut, FCNodeLinkPoint::East));
    lps.append(FCNodeLinkPoint(QPoint(25, 50-4), "out1", FCNodeLinkPoint::OutPut, FCNodeLinkPoint::South));
    lps.append(FCNodeLinkPoint(QPoint(0+4, 25), "in1", FCNodeLinkPoint::Input, FCNodeLinkPoint::West));
    lps.append(FCNodeLinkPoint(QPoint(25, 0+4), "in2", FCNodeLinkPoint::Input, FCNodeLinkPoint::North));
}


FCConstValueNodeGraphicsItem::~FCConstValueNodeGraphicsItem()
{
}


/**
 * @brief 设置参数，如果无法设置成功返回false
 *
 * 支持 int double string datetime color pointf
 * @param v
 * @return
 */
bool FCConstValueNodeGraphicsItem::setValue(const QVariant& v)
{
    switch (v.type())
    {
    case QVariant::Double:
    case QVariant::String:
    case QVariant::DateTime:
    case QVariant::PointF:
    case QVariant::Color:
        m_value = v;
        return (true);

    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::ULongLong:
    case QVariant::LongLong:
        m_value = v.toInt();
        return (true);

    case QVariant::Point://Point也转换为PointF
        m_value = QPointF(v.toPoint());
        return (true);

    default:
        break;
    }
    return (false);
}


QVariant FCConstValueNodeGraphicsItem::getValue() const
{
    return (m_value);
}


bool FCConstValueNodeGraphicsItem::isNull() const
{
    bool b = m_value.isValid();

    b &= m_value.isNull();
    b &= checkType();
    return (b);
}


void FCConstValueNodeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen pen(FCNodePalette::getGlobalEdgeColor());
    QRectF rec = boundingRect();

    pen.setWidth(1);
    if (isSelected()) {
        pen.setWidth(2);
        pen.setColor(pen.color().darker());
        rec.adjust(1, 1, -1, -1);
    }
    painter->setPen(pen);
    painter->fillRect(rec, FCNodePalette::getGlobalBackgroundColor());
    painter->drawRect(rec);
    //绘制点
    paintLinkPoints(painter, option, widget);
    painter->restore();
}


QRectF FCConstValueNodeGraphicsItem::boundingRect() const
{
    return (QRectF(0, 0, 50, 50));
}


bool FCConstValueNodeGraphicsItem::checkType() const
{
    switch (m_value.type())
    {
    case QVariant::Double:
    case QVariant::String:
    case QVariant::DateTime:
    case QVariant::PointF:
    case QVariant::Color:
    case QVariant::Int:
        return (true);

    default:
        break;
    }
    return (false);
}
