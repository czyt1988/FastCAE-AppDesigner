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

    //返回string对应的字典结果，如果没有QString _name;查找到，就返回id自身
    QString string(const QString& id);

public:
    QString _name;
    QString _describe;
    QRectF _boundingRect;
    QRect _pixmapRect;
    QPixmap _pixmap;
    QHash<QString, QPointF> _connectPoints;
    QPointF _pos;
    qreal _rotation;
    QMap<int, QVariant> _dataMap;
    QMultiHash<QString, FCNodeLink *> _linkMap;     ///< 记录所有点的连接线
    QHash<QString, QString> _stringMap;             ///< 翻译字典，针对多语言，再调用返回String的情况下，都会调用这个查找对应的
    QString _prototype;                             ///< prototype,用于表征同一类型的node
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
    QString _fromConnectName;
    QString _toConnectName;
};

#endif // FCNODE_P_H
