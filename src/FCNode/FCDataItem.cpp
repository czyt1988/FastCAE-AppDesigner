#include "FCDataItem.h"

FCDataItem::FCDataItem()
{
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
