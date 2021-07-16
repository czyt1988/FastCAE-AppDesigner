#include "FCGraphicsView.h"
#include <QMatrix>
#include <QWheelEvent>
#include <QPainter>
#include <QDebug>
FCGraphicsView::FCGraphicsView(QWidget *parent) : QGraphicsView(parent)
    , m_enableShowScenePos(false)
    , m_enaleWheelZoom(true)
    , m_scaleMax(3)
    , m_scaleMin(0.333)
    , m_zoomStep(0.1)
{
}


FCGraphicsView::FCGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
    , m_enaleWheelZoom(true)
    , m_scaleMax(3)
    , m_scaleMin(0.333)
    , m_zoomStep(0.1)
{
}


void FCGraphicsView::setScaleRange(qreal min, qreal max)
{
    m_scaleMin = min;
    m_scaleMax = max;
}


qreal FCGraphicsView::getScaleMaxFactor() const
{
    return (m_scaleMax);
}


qreal FCGraphicsView::getScaleMinFactor() const
{
    return (m_scaleMin);
}


void FCGraphicsView::wheelEvent(QWheelEvent *event)
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


void FCGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (event) {
        m_mouseScenePos = mapToScene(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}


bool FCGraphicsView::isEnableShowScenePos() const
{
    return (m_enableShowScenePos);
}


void FCGraphicsView::setEnableShowScenePos(bool enableShowScenePos)
{
    m_enableShowScenePos = enableShowScenePos;
}


bool FCGraphicsView::isEnaleWheelZoom() const
{
    return (m_enaleWheelZoom);
}


void FCGraphicsView::setEnaleWheelZoom(bool enaleWheelZoom)
{
    m_enaleWheelZoom = enaleWheelZoom;
}
