#include "FCDataItem.h"

FCDataItem::FCDataItem()
{
}


FCDataItem::FCDataItem(const QVariant& v)
{
    setValue(v);
}


QVariant FCDataItem::getValue() const
{
    return (m_variant);
}


void FCDataItem::setValue(const QVariant& v)
{
    m_variant = v;
}


QVariant& FCDataItem::value()
{
    return (m_variant);
}


const QVariant& FCDataItem::value() const
{
    return (m_variant);
}


QString FCDataItem::getName() const
{
    return (m_name);
}


void FCDataItem::setName(const QString& s)
{
    m_name = s;
}


QString& FCDataItem::name()
{
    return (m_name);
}


const QString& FCDataItem::name() const
{
    return (m_name);
}


bool operator ==(const FCDataItem& a, const FCDataItem& b)
{
    return ((a.value() == b.value()) && (a.name() == b.name()));
}


bool operator <(const FCDataItem& a, const FCDataItem& b)
{
    return (a.value() < b.value());
}


QDebug operator <<(QDebug dbg, const FCDataItem& a)
{
    dbg.nospace() << "(" << a.name << ")" << a.value();
    return (dbg.space());
}
