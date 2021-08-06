#ifndef FCMETHODEDITORGRAPHICSVIEW_H
#define FCMETHODEDITORGRAPHICSVIEW_H
#include <QtCore/qglobal.h>
#include "FCGraphicsView.h"
#include "FCProject.h"
#include "FCMethodEditorNodeFactory.h"
#include "FCMethodEditorGraphicsScene.h"
#include <QPointer>

class GProject;

/**
 * @brief 用于节点显示的GraphicsView
 */
class FCMethodEditorGraphicsView : public FCGraphicsView
{
public:
    FCMethodEditorGraphicsView(QWidget *parent = 0);
    FCMethodEditorGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
    void setProject(FCProject *project);
    void setNodeFactory(FCMethodEditorNodeFactory factory);

protected:
    void dragEnterEvent(QDragEnterEvent *e) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *e) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *e) Q_DECL_OVERRIDE;

private:
    QPointer<FCProject> m_project;
    FCMethodEditorNodeFactory m_factory;
};

#endif // GNODEGRAPHICSVIEW_H
