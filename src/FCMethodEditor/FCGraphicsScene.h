#ifndef FCGRAPHICSSCENE_H
#define FCGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QHash>

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

    QUndoStack *getUndoStack() const;
    void setUndoStack(QUndoStack *undoStack);

signals:

//    /**
//     * @brief 节点选中的信号
//     * @param node
//     */
//    void nodeDoubleClicked(FCGraphicsNodeItem *item);

//    /**
//     * @brief 节点旋转
//     * @param node 节点
//     */
//    void nodeRotationChanged(FCGraphicsNodeItem *item);

//    /**
//     * @brief 节点位置变更
//     * @param node 节点
//     */
//    void nodePositionChanged(FCGraphicsNodeItem *item);

    /**
     * @brief 节点删除
     * @param item 节点
     */
    void nodeDeleted(const QList<QGraphicsItem *>& items);

protected:
//    void callNodeDoubleClicked(FCGraphicsNodeItem *item);
//    void callNodeRotationChanged(FCGraphicsNodeItem *item);
//    void callNodePositionChanged(FCGraphicsNodeItem *item);

protected:
    virtual void keyPressEvent(QKeyEvent *keyEvent);

    //删除按键按下操作
    virtual void keyDeletePressed();

private:
    qreal m_scaleFactor;
    QUndoStack *m_undoStack;
};

#endif // GGRAPHICSSCENE_H
