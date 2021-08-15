#include "FCDataItem.h"

FCDataItem::FCDataItem()
{
}


FCDataItem::FCDataItem(const QVariant& v, const QString& n)
{
    set(v, n);
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


void FCDataItem::setName(const QString& n)
{
    m_name = n;
}


QString& FCDataItem::name()
{
    return (m_name);
}


const QString& FCDataItem::name() const
{
    return (m_name);
}


void FCDataItem::set(const QVariant& v, const QString& n)
{
    setValue(v);
    setName(n);
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
    dbg.nospace() << "(" << a.name() << ")" << a.value();
    return (dbg.space());
}
