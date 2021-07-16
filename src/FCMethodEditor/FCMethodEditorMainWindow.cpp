#include "FCMethodEditorMainWindow.h"
#include "ui_FCMethodEditorMainWindow.h"

FCMethodEditorMainWindow::FCMethodEditorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FCMethodEditorMainWindow)
{
    ui->setupUi(this);
    //加载所有模板
    m_templateLoader.load();
    //根据模板初始化
    setupNodeListWidget();
}


FCMethodEditorMainWindow::~FCMethodEditorMainWindow()
{
    delete ui;
}


/**
 * @brief 添加节点窗口
 * @param name 分组名
 * @param baseNodes 节点列表
 */
void FCMethodEditorMainWindow::addNodeWidget(const QString& name, QList<FCNode *> baseNodes)
{
    FCNodeListWidget *w = new FCNodeListWidget(this);

    //添加节点
    for (FCNode *node : baseNodes)
    {
        QListWidgetItem *item = new FCNodeListWidgetItem(node, w);
    }
    ui->toolBox->addItem(w, name);
}


void FCMethodEditorMainWindow::setupNodeListWidget()
{
    QList<QString> gns = m_templateLoader.groupsName();

    for (const QString& name : gns)
    {
        addNodeWidget(name, m_templateLoader.nodeList(name));
    }
}
