#include "FCNodeLinkPoint.h"


FCNodeLinkPoint::FCNodeLinkPoint()
    : direction(East)
    , way(OutPut)
{
}


FCNodeLinkPoint::FCNodeLinkPoint(const QPoint& p, const QString& n, FCNodeLinkPoint::Way w, FCNodeLinkPoint::Direction d)
    : position(p)
    , name(n)
    , way(w)
    , direction(d)
{
}


bool FCNodeLinkPoint::isValid() const
{
    return (!name.isNull());
}


bool FCNodeLinkPoint::isInput() const
{
    return (this->way == Input);
}


bool FCNodeLinkPoint::isOutput() const
{
    return (this->way == OutPut);
}


/**
 * @brief FCNodeLinkPoint 的等于号操作符
 * @param a
 * @param b
 * @return
 */
bool operator ==(const FCNodeLinkPoint& a, const FCNodeLinkPoint& b)
{
    return ((a.name == b.name) &&
           (a.direction == b.direction) &&
           (a.position == b.position) &&
           (a.way == b.way));
}


bool operator ==(const FCNodeLinkPoint& a, const QString& b)
{
    return (a.name == b);
}


bool operator <(const FCNodeLinkPoint& a, const FCNodeLinkPoint& b)
{
    return (a.name < b.name);
}


uint qHash(const FCNodeLinkPoint& key, uint seed)
{
    return (qHash(key.name, seed));
}


QDebug operator <<(QDebug dbg, const FCNodeLinkPoint& a)
{
    dbg.nospace() << "(" << a.name << ") [" << a.position << "],way is " << a.way << ",direct is " << a.direction;
    return (dbg.space());
}
