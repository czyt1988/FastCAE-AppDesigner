#include "FCPluginManagerDialog.h"
#include "ui_FCPluginManagerDialog.h"
#include "FCPluginManager.h"
#include <QTreeWidgetItem>
#include <QDebug>
#include "FCAbstractNodePlugin.h"
#include "FCMethodEditorPluginManager.h"
FCPluginManagerDialog::FCPluginManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCPluginManagerDialog)
{
    ui->setupUi(this);
    init();
}


FCPluginManagerDialog::~FCPluginManagerDialog()
{
    delete ui;
}


void FCPluginManagerDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;

    default:
        break;
    }
}


void FCPluginManagerDialog::init()
{
    ui->treeWidget->setColumnCount(4);//插件名称，插件b版本，是否加载
    ui->treeWidget->setHeaderLabels({ tr("name"), tr("version"), tr("is loaded"), tr("description") });
    FCMethodEditorPluginManager& plugin = FCMethodEditorPluginManager::instance();
    QList<FCAbstractNodePlugin *> nodeplugins = plugin.getNodePlugins();
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->treeWidget);

    //节点插件
    rootItem->setText(0, tr("node plugin"));
    ui->treeWidget->insertTopLevelItem(0, rootItem);
    for (FCAbstractNodePlugin *p : nodeplugins)
    {
        qDebug()<<"plugin name:"<<p->getName();
        QTreeWidgetItem *item = new QTreeWidgetItem(rootItem);
        item->setText(0, p->getName());
        item->setText(1, p->getVersion());
        item->setText(2, tr("is load"));
        item->setText(3, p->getDescription());
    }
    ui->treeWidget->expandAll();
}
