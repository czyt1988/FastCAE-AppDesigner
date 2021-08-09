#include "FCNodeGraphicsView.h"
#include <QMatrix>
#include <QWheelEvent>
#include <QPainter>
#include <QDebug>
FCNodeGraphicsView::FCNodeGraphicsView(QWidget *parent) : QGraphicsView(parent)
    , m_enableShowScenePos(false)
    , m_enaleWheelZoom(true)
    , m_scaleMax(3)
    , m_scaleMin(0.333)
    , m_zoomStep(0.1)
{
    //把鼠标移动事件捕获
    //setMouseTracking(true);
}


FCNodeGraphicsView::FCNodeGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
    , m_enaleWheelZoom(true)
    , m_scaleMax(3)
    , m_scaleMin(0.333)
    , m_zoomStep(0.1)
{
    //setMouseTracking(true);
}


void FCNodeGraphicsView::setScaleRange(qreal min, qreal max)
{
    m_scaleMin = min;
    m_scaleMax = max;
}


qreal FCNodeGraphicsView::getScaleMaxFactor() const
{
    return (m_scaleMax);
}


qreal FCNodeGraphicsView::getScaleMinFactor() const
{
    return (m_scaleMin);
}


void FCNodeGraphicsView::wheelEvent(QWheelEvent *event)
{
    QMatrix old_matrix = matrix();

    if (event->delta() > 0) {
        if ((old_matrix.m11() > m_scaleMax) || (old_matrix.m22() > m_scaleMax)) {
            return;
        }
        old_matrix.scale(1+m_zoomStep, 1+m_zoomStep);
        setMatrix(old_matrix);
    }else {
        if ((old_matrix.m11() < m_scaleMin) || (old_matrix.m22() < m_scaleMin)) {
            return;
        }
        old_matrix.scale(1-m_zoomStep, 1-m_zoomStep);
        setMatrix(old_matrix);
    }
}


void FCNodeGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (event) {
        m_mouseScenePos = mapToScene(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}


bool FCNodeGraphicsView::isEnableShowScenePos() const
{
    return (m_enableShowScenePos);
}


void FCNodeGraphicsView::setEnableShowScenePos(bool enableShowScenePos)
{
    m_enableShowScenePos = enableShowScenePos;
}


bool FCNodeGraphicsView::isEnaleWheelZoom() const
{
    return (m_enaleWheelZoom);
}


void FCNodeGraphicsView::setEnaleWheelZoom(bool enaleWheelZoom)
{
    m_enaleWheelZoom = enaleWheelZoom;
}
