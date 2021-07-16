#include "FCNodeGraphicsView.h"
#include <QDragEnterEvent>
#include <QDebug>
#include "FCNodeMimeData.h"
#include "FCMimeTypeFormatDefine.h"
#include "FCNodesManager.h"
#include "FCNode.h"
#include "FCGraphicsScene.h"
FCNodeGraphicsView::FCNodeGraphicsView(QWidget *parent)
    : FCGraphicsView(parent)
{
    setAcceptDrops(true);
}


FCNodeGraphicsView::FCNodeGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : FCGraphicsView(scene, parent)
{
    setAcceptDrops(true);
}


/**
 * @brief 设置节点的模板，GraphicsView不会管理模板的内存，在外部删除不会影响
 * @param t
 */
void FCNodeGraphicsView::setNodeTemplate(FCNodeTemplate *t)
{
    m_template = t;
}


/**
 * @brief 设置工程
 * @param project
 */
void FCNodeGraphicsView::setProject(FCProject *project)
{
    m_project = project;
}


void FCNodeGraphicsView::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}


void FCNodeGraphicsView::dragMoveEvent(QDragMoveEvent *e)
{
    e->acceptProposedAction();
}


void FCNodeGraphicsView::dropEvent(QDropEvent *e)
{
    const FCNodeMimeData *mimeData = qobject_cast<const FCNodeMimeData *>(e->mimeData());
    FCGraphicsScene *s = qobject_cast<FCGraphicsScene *>(scene());

    if ((nullptr == mimeData) || (nullptr == s)) {
        return;
    }

    if (m_template.isNull()) {
        return;
    }
    if (mimeData->hasFormat(MIME_STANDARD_NODE)) {
        QPointF scenePos = mapToScene(e->pos());
        QString nodePrototype = mimeData->getNodePrototype();
        FCNode *n = m_project->manager()->createNodeFromPrototype(nodePrototype);
        if (nullptr == n) {
            return;
        }
        n->setPos(scenePos);
        s->addNodeItem(n);
    }
}
