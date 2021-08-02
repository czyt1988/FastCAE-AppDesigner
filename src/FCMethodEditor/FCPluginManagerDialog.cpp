#include "FCPluginManagerDialog.h"
#include "ui_FCPluginManagerDialog.h"
#include "FCPluginManager.h"
#include <QDebug>
#include "FCAbstractNodePlugin.h"
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
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FCPluginManagerDialog::init()
{
    ui->treeWidget->setColumnCount(3);//插件名称，插件b版本，是否加载
    FCPluginManager& plugin = FCPluginManager::instance();
    plugin.

}
