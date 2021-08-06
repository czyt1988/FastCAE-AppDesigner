#ifndef FCMETHODEDITORGRAPHICSSCENE_H
#define FCMETHODEDITORGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QHash>
#include "FCNodeGraphicsScene.h"
class QUndoStack;
class QGraphicsSceneWheelEvent;
class GProject;
class FCMethodEditorGraphicsScene : public FCNodeGraphicsScene
{
    Q_OBJECT
public:
    FCMethodEditorGraphicsScene(QObject *parent = 0);

    QUndoStack *getUndoStack() const;
    void setUndoStack(QUndoStack *undoStack);

signals:

    /**
     * @brief 节点删除
     * @param item 节点
     */
    void nodeDeleted(const QList<QGraphicsItem *>& items);

protected:
    virtual void keyPressEvent(QKeyEvent *keyEvent);

    //删除按键按下操作
    virtual void keyDeletePressed();

private:
    qreal m_scaleFactor;
    QUndoStack *m_undoStack;
};

#endif // GGRAPHICSSCENE_H
