#ifndef METHODMAINWINDOW_H
#define METHODMAINWINDOW_H

#include <QMainWindow>
#include "FCNodeListWidget.h"
#include "FCNodeTemplate.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class FCMethodEditorMainWindow;
}
QT_END_NAMESPACE

class FCMethodEditorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    FCMethodEditorMainWindow(QWidget *parent = nullptr);
    ~FCMethodEditorMainWindow();
    //添加节点窗口
    void addNodeWidget(const QString& name, QList<FCNode *> baseNodes);

private:
    //根据模板生成nodewidget
    void setupNodeListWidget();

private:
    Ui::FCMethodEditorMainWindow *ui;
    FCNodeTemplate m_templateLoader;
};
#endif // METHODMAINWINDOW_H
