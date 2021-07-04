#ifndef FCNODE_P_H
#define FCNODE_P_H

#include "FCGlobals.h"
#include <QVariant>
#include <QRectF>
#include <QPixmap>
class FCNode;
class FCNodeLink;
class FCNodePrivate {
public:
    FC_IMPL_PUBLIC(FCNode)
    FCNodePrivate(FCNode *p);
    ~FCNodePrivate();
    //除了q_ptr,其余都复制
    void copy(const FCNodePrivate *other);

    //移除连接
    void removeLink(FCNodeLink *link);

    QString _name;
    QString _describe;
    QRectF _boundingRect;
    QRect _pixmapRect;
    QPixmap _pixmap;
    QHash<QString, QPointF> _connectPoints;
    QPointF _pos;
    qreal _rotation;
    QMap<int, QVariant> _dataMap;
    QMultiHash<QString, FCNodeLink *> _linkMap;///< 记录所有点的连接线
};

#endif // FCNODE_P_H
