#include "FCMethodEditorGraphicsScene.h"
//Qt
#include <QMatrix>
#include <QKeyEvent>
#include <QDebug>


FCMethodEditorGraphicsScene::FCMethodEditorGraphicsScene(QObject *parent) : FCNodeGraphicsScene(parent)
    , m_scaleFactor(1.0)
{
}


void FCMethodEditorGraphicsScene::keyPressEvent(QKeyEvent *keyEvent)
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
void FCMethodEditorGraphicsScene::keyDeletePressed()
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
QUndoStack *FCMethodEditorGraphicsScene::getUndoStack() const
{
    return (m_undoStack);
}


/**
 * @brief 设置回退栈，节点支持redo/undo的必要条件
 * @param undoStack
 */
void FCMethodEditorGraphicsScene::setUndoStack(QUndoStack *undoStack)
{
    m_undoStack = undoStack;
}
