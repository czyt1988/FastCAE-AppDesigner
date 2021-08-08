#ifndef FCGRAPHICSVIEW_H
#define FCGRAPHICSVIEW_H
#include <QGraphicsView>
#include "FCNodeGlobal.h"
class QWheelEvent;

/**
 * @brief 支持缩放的GraphicsView
 */
class FCNODE_API FCNodeGraphicsView : public QGraphicsView
{
public:
    FCNodeGraphicsView(QWidget *parent = 0);
    FCNodeGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
    //设置缩放的因子
    void setScaleRange(qreal min, qreal max);
    qreal getScaleMaxFactor() const;
    qreal getScaleMinFactor() const;

    //设置是否可以滚轮缩放
    bool isEnaleWheelZoom() const;
    void setEnaleWheelZoom(bool enaleWheelZoom);

    bool isEnableShowScenePos() const;
    void setEnableShowScenePos(bool enableShowScenePos);

protected:
    //void paintEvent(QPaintEvent * event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    bool m_enableShowScenePos;
    bool m_enaleWheelZoom;
    qreal m_scaleMax;
    qreal m_scaleMin;
    qreal m_zoomStep;
    QPointF m_mouseScenePos;
};

#endif // GGRAPHICSVIEW_H
