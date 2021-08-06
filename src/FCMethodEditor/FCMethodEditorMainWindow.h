#ifndef FCMETHODEDITORMAINWINDOW_H
#define FCMETHODEDITORMAINWINDOW_H

#include <QMainWindow>
#include "FCNodeListWidget.h"
#include "FCMethodEditorNodeFactory.h"
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

private:
    //根据模板生成nodewidget
    void setupNodeListWidget();

    //初始化ui
    void initUI();

    //初始化信号槽
    void initConnect();

private slots:
    //插件管理对话框触发
    void onActionPluginManagerTriggered(bool on);

private:
    Ui::FCMethodEditorMainWindow *ui;
    FCMethodEditorNodeFactory m_nodeFactory;
};
#endif // METHODMAINWINDOW_H
