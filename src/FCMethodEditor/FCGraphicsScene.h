#ifndef FCGRAPHICSSCENE_H
#define FCGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QHash>
#include "FCNode.h"
#include "FCGraphicsNodeItem.h"
#include "FCGraphicsNodeLinkLineItem.h"
class QUndoStack;
class FCNode;
class FCNodeLink;
class QGraphicsSceneWheelEvent;
class GProject;
class FCGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    friend class FCGraphicsNodeItem;
    friend class FCGraphicsNodeLinkLineItem;
public:
    FCGraphicsScene(QObject *parent = 0);
    //添加节点
    void addNodeItem(FCNode* node);
    //添加连线，连线需要在节点后添加
    void addNodeLinkItem(FCNodeLink* link);
    //根据节点查找item
    FCGraphicsNodeItem* nodeToItem(FCNode* node);
    //根据连接节点寻找item
    FCGraphicsNodeLinkLineItem* linkToItem(FCNodeLink* link);
    //回退栈
    QUndoStack *getUndoStack() const;
    void setUndoStack(QUndoStack *undoStack);
signals:
    /**
     * @brief 节点选中的信号
     * @param node
     */
    void nodeDoubleClicked(FCGraphicsNodeItem *item);
    /**
     * @brief 节点旋转
     * @param node 节点
     */
    void nodeRotationChanged(FCGraphicsNodeItem* item);
    /**
     * @brief 节点位置变更
     * @param node 节点
     */
    void nodePositionChanged(FCGraphicsNodeItem* item);
    /**
     * @brief 节点删除
     * @param item 节点
     */
    void nodeDeleted(const QList<QGraphicsItem*>& items);
protected:
    void callNodeDoubleClicked(FCGraphicsNodeItem* item);
    void callNodeRotationChanged(FCGraphicsNodeItem* item);
    void callNodePositionChanged(FCGraphicsNodeItem* item);
protected:
    virtual void keyPressEvent(QKeyEvent *keyEvent);
    //删除按键按下操作
    virtual void keyDeletePressed();
private:
    QHash<FCNode*,FCGraphicsNodeItem*> m_node2item;
    QHash<FCNodeLink*,FCGraphicsNodeLinkLineItem*> m_link2item;
    qreal m_scaleFactor;
    QUndoStack* m_undoStack;
};

#endif // GGRAPHICSSCENE_H
