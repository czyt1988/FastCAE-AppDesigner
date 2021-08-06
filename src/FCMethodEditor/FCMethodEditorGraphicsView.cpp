#include "FCMethodEditorGraphicsView.h"
#include <QDragEnterEvent>
#include <QDebug>
#include "FCNodeMimeData.h"
#include "FCNodeMetaData.h"
#include "FCMimeTypeFormatDefine.h"
#include "FCMethodEditorGraphicsScene.h"
FCMethodEditorGraphicsView::FCMethodEditorGraphicsView(QWidget *parent)
    : FCGraphicsView(parent)
{
    setAcceptDrops(true);
    setScene(new FCMethodEditorGraphicsScene(this));
    setRenderHint(QPainter::Antialiasing, false);
    //setDragMode(QGraphicsView::RubberBandDrag);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}


FCMethodEditorGraphicsView::FCMethodEditorGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : FCGraphicsView(scene, parent)
{
    setAcceptDrops(true);
}


/**
 * @brief 设置工程
 * @param project
 */
void FCMethodEditorGraphicsView::setProject(FCProject *project)
{
    m_project = project;
}


void FCMethodEditorGraphicsView::setNodeFactory(FCMethodEditorNodeFactory factory)
{
    m_factory = factory;
}


void FCMethodEditorGraphicsView::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasFormat(MIME_NODE_META_DATA)) {
        //说明有节点的meta数据拖入
        e->acceptProposedAction();
    }else{
        e->ignore();
    }
}


void FCMethodEditorGraphicsView::dragMoveEvent(QDragMoveEvent *e)
{
    e->acceptProposedAction();
}


void FCMethodEditorGraphicsView::dropEvent(QDropEvent *e)
{
    if (e->mimeData()->hasFormat(MIME_NODE_META_DATA)) {
        //说明有节点的meta数据拖入
        const FCNodeMimeData *nodemime = qobject_cast<const FCNodeMimeData *>(e->mimeData());
        if (nullptr == nodemime) {
            qDebug()<<tr("drop have invalid mime data");
            return;
        }
        QGraphicsScene *sc = scene();
        FCNodeMetaData nodemeta = nodemime->getNodeMetaData();
        FCAbstractNodeGraphicsItem *item = m_factory.create(nodemeta.getNodePrototype());
        if (nullptr == item) {
            qDebug()<<tr("can not create node,node prototype is:")<<nodemeta.getNodePrototype();
            return;
        }
        QPointF pos = mapToScene(e->pos());
        item->setPos(pos);
        sc->addItem(item);
    }
}
