#include "FCNodeGraphicsScene.h"

FCNodeGraphicsScene::FCNodeGraphicsScene(QObject *p)
    : QGraphicsScene(p)
{
    qRegisterMetaType<FCNodeLinkPoint>("FCNodeLinkPoint");
}


FCNodeGraphicsScene::FCNodeGraphicsScene(const QRectF& sceneRect, QObject *p)
    : QGraphicsScene(sceneRect, p)
{
    qRegisterMetaType<FCNodeLinkPoint>("FCNodeLinkPoint");
}


FCNodeGraphicsScene::FCNodeGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *p)
    : QGraphicsScene(x, y, width, height, p)
{
    qRegisterMetaType<FCNodeLinkPoint>("FCNodeLinkPoint");
}


void FCNodeGraphicsScene::callNodeItemLinkPointSelected(FCAbstractNodeGraphicsItem *item, const FCNodeLinkPoint& lp)
{
    emit nodeItemLinkPointSelected(item, lp);
}
