#include "FCGraphicsScene.h"
//Qt
#include <QMatrix>
#include <QKeyEvent>
#include <QDebug>
//Local
#include "FCNode.h"
#include "FCNodeLink.h"
#include "FCGraphicsNodeItem.h"
#include "FCGraphicsNodeLinkLineItem.h"


FCGraphicsScene::FCGraphicsScene(QObject *parent) : QGraphicsScene(parent)
    , m_scaleFactor(1.0)
{
}


void FCGraphicsScene::addNodeItem(FCNode *node)
{
    FCGraphicsNodeItem *nodeItem = new FCGraphicsNodeItem(node);

    m_node2item[node] = nodeItem;
    addItem(nodeItem);
}


void FCGraphicsScene::addNodeLinkItem(FCNodeLink *link)
{
    FCGraphicsNodeLinkLineItem *linkItem = new FCGraphicsNodeLinkLineItem(link);

    m_link2item[link] = linkItem;
    addItem(linkItem);
    linkItem->updateNodePos();
}


FCGraphicsNodeItem *FCGraphicsScene::nodeToItem(FCNode *node)
{
    return (m_node2item.value(node, nullptr));
}


FCGraphicsNodeLinkLineItem *FCGraphicsScene::linkToItem(FCNodeLink *link)
{
    return (m_link2item.value(link, nullptr));
}


void FCGraphicsScene::callNodeDoubleClicked(FCGraphicsNodeItem *item)
{
    emit nodeDoubleClicked(item);
}


/**
 * @brief 节点移动结束
 * @param node
 */
void FCGraphicsScene::callNodePositionChanged(FCGraphicsNodeItem *item)
{
    emit nodePositionChanged(item);
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


void FCGraphicsScene::callNodeRotationChanged(FCGraphicsNodeItem *item)
{
    emit nodeRotationChanged(item);
}
