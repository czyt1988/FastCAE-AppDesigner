#ifndef FCNODEGRAPHICSSCENE_H
#define FCNODEGRAPHICSSCENE_H
#include <QtCore/qglobal.h>
#include "FCNodeGlobal.h"
#include <QGraphicsScene>
#include "FCAbstractNodeGraphicsItem.h"
#include "FCAbstractNodeLinkGraphicsItem.h"
class QGraphicsSceneMouseEvent;
FC_IMPL_FORWARD_DECL(FCNodeGraphicsScene)

class FCNODE_API FCNodeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    FC_IMPL(FCNodeGraphicsScene)
    friend class FCAbstractNodeGraphicsItem;
    friend class FCAbstractNodeLinkGraphicsItem;
public:
    FCNodeGraphicsScene(QObject *p = nullptr);
    FCNodeGraphicsScene(const QRectF& sceneRect, QObject *p = nullptr);
    FCNodeGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *p = nullptr);
    ~FCNodeGraphicsScene();
    //判断是否处于开始连接状态
    bool isStartLink() const;

    //获取当前鼠标在scene的位置
    QPointF getCurrentMouseScenePos() const;

signals:

    /**
     * @brief 节点的连接点被选中触发的信号
     * @param item 节点item
     * @param lp 连接点
     */
    void nodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp, QGraphicsSceneMouseEvent *event);

    /**
     * @brief 说明link已经为空，这时会自动remove
     */
    void nodeLinkItemIsEmpty(FCAbstractNodeLinkGraphicsItem *link);

protected slots:
    //此函数为FCNodeGraphicsScene处理连接点点击事件
    void onNodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp, QGraphicsSceneMouseEvent *event);

protected:
    //鼠标点击事件
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

    //鼠标移动事件
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);


    //此函数将会触发 nodeItemLinkPointSelected 信号
    void callNodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp, QGraphicsSceneMouseEvent *event);

    //itemlink都没用节点连接时会调用这个函数，发出
    void callNodeItemLinkIsEmpty(FCAbstractNodeLinkGraphicsItem *link);

private:
    void initConnect();
};

#endif // FCNODEGRAPHICSSCENE_H
