#include "FCPluginManagerDialog.h"
#include "ui_FCPluginManagerDialog.h"

FCPluginManagerDialog::FCPluginManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCPluginManagerDialog)
{
    ui->setupUi(this);
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
