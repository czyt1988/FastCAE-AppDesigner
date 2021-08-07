#ifndef FCNODEGRAPHICSSCENE_H
#define FCNODEGRAPHICSSCENE_H
#include <QtCore/qglobal.h>
#include "FCNodeGlobal.h"
#include <QGraphicsScene>
#include "FCAbstractNodeGraphicsItem.h"
class QGraphicsSceneMouseEvent;
FC_IMPL_FORWARD_DECL(FCNodeGraphicsScene)
class FCNODE_API FCNodeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    FC_IMPL(FCNodeGraphicsScene)
    friend class FCAbstractNodeGraphicsItem;
public:
    FCNodeGraphicsScene(QObject *p = nullptr);
    FCNodeGraphicsScene(const QRectF& sceneRect, QObject *p = nullptr);
    FCNodeGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *p = nullptr);
    //判断是否处于开始连接状态
    bool isStartLink() const;

signals:

    /**
     * @brief 节点的连接点被选中触发的信号
     * @param item 节点item
     * @param lp 连接点
     */
    void nodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp, QGraphicsSceneMouseEvent *event);

protected slots:
    //此函数为FCNodeGraphicsScene处理连接点点击事件
    void onNodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp, QGraphicsSceneMouseEvent *event);

protected:
    //此函数将会触发 nodeItemLinkPointSelected 信号
    void callNodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp, QGraphicsSceneMouseEvent *event);

private:
    void initConnect();
};

#endif // FCNODEGRAPHICSSCENE_H
