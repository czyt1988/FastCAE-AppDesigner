#include "FCMethodEditorMainWindow.h"
#include "ui_FCMethodEditorMainWindow.h"
#include "FCPluginManager.h"
FCMethodEditorMainWindow::FCMethodEditorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FCMethodEditorMainWindow)
{
    ui->setupUi(this);
    //加载插件
    FCPluginManager::instance().load();
}


FCMethodEditorMainWindow::~FCMethodEditorMainWindow()
{
    delete ui;
}


void FCMethodEditorMainWindow::setupNodeListWidget()
{
}
