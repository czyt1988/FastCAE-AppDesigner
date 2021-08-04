#include "FCConstValueNodeGraphicsItem.h"
#include <QPainter>
#define RES_VARIANT ":/icon/icon/variant.svg"
FCConstValueNodeGraphicsItem::FCConstValueNodeGraphicsItem(QGraphicsItem *p)
    : FCAbstractNodeGraphicsItem(p)
{
    metaData().setIcon(QIcon(RES_VARIANT));
    metaData().setNodePrototype("FC.Util.Const");
    metaData().setNodeName(QObject::tr("variant"));
    metaData().setGroup(QObject::tr("common"));
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
    QPen pen(Qt::black);

    pen.setWidth(1);
    painter->setPen(pen);
    painter->fillRect(boundingRect(), Qt::white);
    painter->drawRect(boundingRect());

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
