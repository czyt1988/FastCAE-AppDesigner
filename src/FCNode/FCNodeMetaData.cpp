#include "FCNodeMetaData.h"

FCNodeMetaData::FCNodeMetaData()
{
}


FCNodeMetaData::FCNodeMetaData(const QString& prototype)
    : m_prototype(prototype)
{
}


FCNodeMetaData::FCNodeMetaData(const QString& prototype,
    const QString& name,
    const QIcon& icon,
    const QString& group)
    : m_prototype(prototype),
    m_nodeName(name),
    m_nodeIcon(icon),
    m_group(group)
{
}


QString FCNodeMetaData::getNodePrototype() const
{
    return (m_prototype);
}


void FCNodeMetaData::setNodePrototype(const QString& prototype)
{
    m_prototype = prototype;
}


QString FCNodeMetaData::getNodeName() const
{
    return (m_nodeName);
}


void FCNodeMetaData::setNodeName(const QString& name)
{
    m_nodeName = name;
}


QIcon FCNodeMetaData::getIcon() const
{
    return (m_nodeIcon);
}


void FCNodeMetaData::setIcon(const QIcon& icon)
{
    m_nodeIcon = icon;
}


QString FCNodeMetaData::getGroup() const
{
    return (m_group);
}


void FCNodeMetaData::setGroup(const QString& group)
{
    m_group = group;
}


uint qHash(const FCNodeMetaData& key, uint seed)
{
    return (qHash(key.getNodePrototype(), seed));
}


bool operator <(const FCNodeMetaData& a, const FCNodeMetaData& b)
{
    return (a.getNodePrototype() < b.getNodePrototype());
}
