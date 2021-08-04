#include "FCMethodEditorMainWindow.h"
#include "ui_FCMethodEditorMainWindow.h"
//插件相关
#include "FCMethodEditorPluginManager.h"
#include "FCPluginManager.h"
#include "FCAbstractPlugin.h"
#include "FCAbstractNodePlugin.h"
//对话框
#include "FCPluginManagerDialog.h"
//节点相关
#include "FCAbstractNodeGraphicsFactory.h"
#include "FCNodeMetaData.h"

FCMethodEditorMainWindow::FCMethodEditorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FCMethodEditorMainWindow)
{
    ui->setupUi(this);
    //首次调用此函数会加载插件，可放置在main函数中调用
    FCMethodEditorPluginManager::instance();
    initUI();
    initConnect();
}


FCMethodEditorMainWindow::~FCMethodEditorMainWindow()
{
    delete ui;
}


void FCMethodEditorMainWindow::setupNodeListWidget()
{
    FCMethodEditorPluginManager& plugin = FCMethodEditorPluginManager::instance();
    QList<FCAbstractNodeGraphicsFactory *> factorys = plugin.getNodeFactorys();
}


void FCMethodEditorMainWindow::initUI()
{
    FCMethodEditorPluginManager& pluginmgr = FCMethodEditorPluginManager::instance();
    QList<FCAbstractNodeGraphicsFactory *> factorys = pluginmgr.getNodeFactorys();
    //提取所有的元数据
    QList<FCNodeMetaData> nodeMetaDatas;

    for (FCAbstractNodeGraphicsFactory *factory : factorys)
    {
        nodeMetaDatas += factory->getNodesMetaData();
        //注册工厂
        m_nodeFactory.registFactory(factory);
    }
    //对所有元数据按group进行筛分
    QMap<QString, QList<FCNodeMetaData> > groupedNodeMetaDatas;

    for (const FCNodeMetaData& md : nodeMetaDatas)
    {
        groupedNodeMetaDatas[md.getGroup()].append(md);
    }
    //把数据写入toolbox
    ui->toolBox->addItems(groupedNodeMetaDatas);
    ui->graphicsView->setNodeFactory(m_nodeFactory);
}


void FCMethodEditorMainWindow::initConnect()
{
    connect(ui->actionPluginManager, &QAction::triggered, this, &FCMethodEditorMainWindow::onActionPluginManagerTriggered);
}


void FCMethodEditorMainWindow::onActionPluginManagerTriggered(bool on)
{
    Q_UNUSED(on);
    FCPluginManagerDialog dlg(this);

    dlg.exec();
}
