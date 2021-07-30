﻿#ifndef FCNODEGRAPHICSVIEW_H
#define FCNODEGRAPHICSVIEW_H
#include <QtCore/qglobal.h>
#include "FCGraphicsView.h"
#include "FCProject.h"
#include <QPointer>
class GProject;

/**
 * @brief 用于节点显示的GraphicsView
 */
class FCNodeGraphicsView : public FCGraphicsView
{
public:
    FCNodeGraphicsView(QWidget *parent = 0);
    FCNodeGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
    void setProject(FCProject *project);

protected:
    void dragEnterEvent(QDragEnterEvent *e) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *e) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *e) Q_DECL_OVERRIDE;

private:
    QPointer<FCProject> m_project;
};

#endif // GNODEGRAPHICSVIEW_H
