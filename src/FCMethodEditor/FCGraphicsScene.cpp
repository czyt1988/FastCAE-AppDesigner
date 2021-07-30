#include "FCGraphicsScene.h"
//Qt
#include <QMatrix>
#include <QKeyEvent>
#include <QDebug>


FCGraphicsScene::FCGraphicsScene(QObject *parent) : QGraphicsScene(parent)
    , m_scaleFactor(1.0)
{
}


void FCGraphicsScene::keyPressEvent(QKeyEvent *keyEvent)
{
    if (nullptr == keyEvent) {
        return;
    }

    switch (keyEvent->key())
    {
    case Qt::Key_Delete:
        keyDeletePressed();
        break;

    default:
        break;
    }
    QGraphicsScene::keyPressEvent(keyEvent);
}


/**
 * @brief 删除键按下操作
 */
void FCGraphicsScene::keyDeletePressed()
{
    if (nullptr == m_undoStack) {
        return;
    }
    QList<QGraphicsItem *> items = selectedItems();

    if (items.size() <= 0) {
        return;
    }
    emit nodeDeleted(items);
}


/**
 * @brief 获取回退栈，节点支持redo/undo的必要条件
 * @return
 */
QUndoStack *FCGraphicsScene::getUndoStack() const
{
    return (m_undoStack);
}


/**
 * @brief 设置回退栈，节点支持redo/undo的必要条件
 * @param undoStack
 */
void FCGraphicsScene::setUndoStack(QUndoStack *undoStack)
{
    m_undoStack = undoStack;
}


//void FCGraphicsScene::callNodeRotationChanged(FCGraphicsNodeItem *item)
//{
//    emit nodeRotationChanged(item);
//}
