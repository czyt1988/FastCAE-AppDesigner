#ifndef FCNODEGRAPHICSSCENE_H
#define FCNODEGRAPHICSSCENE_H
#include <QtCore/qglobal.h>
#include "FCNodeGlobal.h"
#include <QGraphicsScene>
#include "FCAbstractNodeGraphicsItem.h"

class FCNODE_API FCNodeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    friend class FCAbstractNodeGraphicsItem;
public:
    FCNodeGraphicsScene(QObject *p = nullptr);
    FCNodeGraphicsScene(const QRectF& sceneRect, QObject *p = nullptr);
    FCNodeGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *p = nullptr);
signals:

    /**
     * @brief 节点的连接点被选中触发的信号
     * @param item 节点item
     * @param lp 连接点
     */
    void nodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp);

protected:
    //此函数将会触发 nodeItemLinkPointSelected 信号
    void callNodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp);
};

#endif // FCNODEGRAPHICSSCENE_H
