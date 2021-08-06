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
