#ifndef FCNODE_P_H
#define FCNODE_P_H

#include "FCGlobals.h"
#include <QVariant>
#include <QRectF>
#include <QPixmap>
class FCNode;
class FCNodeLink;

/**
 * @brief FCNode的私有类
 */
class FCNodePrivate {
    friend class FCNodeLink;
public:
    FC_IMPL_PUBLIC(FCNode)
    FCNodePrivate(FCNode *p);
    ~FCNodePrivate();
    //除了q_ptr,其余都复制
    void copy(const FCNodePrivate *other);

    //移除连接
    void removeLink(FCNodeLink *link);

    //把所有连接都断开此节点，此函数仅仅在析构时调用
    void detachAll();

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

/**
 * @brief FCNodeLink的私有类
 */
class FCNodeLinkPrivate {
    friend class FCNode;
public:
    FC_IMPL_PUBLIC(FCNodeLink)
    FCNodeLinkPrivate(FCNodeLink *p);
    FCNode *_fromNode;
    FCNode *_toNode;
};

#endif // FCNODE_P_H
