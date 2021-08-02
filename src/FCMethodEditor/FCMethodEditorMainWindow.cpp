#include "FCMethodEditorMainWindow.h"
#include "ui_FCMethodEditorMainWindow.h"
#include "FCPluginManager.h"
//对话框
#include "FCPluginManagerDialog.h"
FCMethodEditorMainWindow::FCMethodEditorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FCMethodEditorMainWindow)
{
    ui->setupUi(this);
    initConnect();
    //加载插件
    FCPluginManager& plugin = FCPluginManager::instance();
    plugin.load();
}


FCMethodEditorMainWindow::~FCMethodEditorMainWindow()
{
    delete ui;
}


void FCMethodEditorMainWindow::setupNodeListWidget()
{
}

void FCMethodEditorMainWindow::initConnect()
{
    connect(ui->actionPluginManager,&QAction::triggered,this,&FCMethodEditorMainWindow::onActionPluginManagerTriggered);
}

void FCMethodEditorMainWindow::onActionPluginManagerTriggered(bool on)
{
    FCPluginManagerDialog dlg(this);
    dlg.exec();
}
