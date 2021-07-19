#include "FCConstValueNodeGraphicsItem.h"

FCConstValueNodeGraphicsItem::FCConstValueNodeGraphicsItem()
{
}


FCConstValueNodeGraphicsItem::~FCConstValueNodeGraphicsItem()
{
}


QString FCConstValueNodeGraphicsItem::getNodePrototype() const
{
    return ("FC.Util.Const");
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


QRectF FCConstValueNodeGraphicsItem::boundingRect() const
{
}


bool FCConstValueNodeGraphicsItem::checkType()
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
