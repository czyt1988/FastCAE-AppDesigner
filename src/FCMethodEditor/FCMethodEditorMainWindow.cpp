#include "FCMethodEditorMainWindow.h"
#include "ui_FCMethodEditorMainWindow.h"

FCMethodEditorMainWindow::FCMethodEditorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FCMethodEditorMainWindow)
{
    ui->setupUi(this);
    addNodeWidget(tr("const"));
}


FCMethodEditorMainWindow::~FCMethodEditorMainWindow()
{
    delete ui;
}


void FCMethodEditorMainWindow::addNodeWidget(const QString& name)
{
    FCNodeListWidget *w = new FCNodeListWidget(this);

    ui->toolBox->addItem(w, name);
}
