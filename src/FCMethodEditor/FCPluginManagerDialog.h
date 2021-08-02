#ifndef FCPLUGINMANAGERDIALOG_H
#define FCPLUGINMANAGERDIALOG_H

#include <QtWidgets/QDialog>
#include <QStandardItemModel>

namespace Ui {
class FCPluginManagerDialog;
}

class FCPluginManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FCPluginManagerDialog(QWidget *parent = nullptr);
    ~FCPluginManagerDialog();

protected:
    void changeEvent(QEvent *e);
private:
    void init();
private:
    Ui::FCPluginManagerDialog *ui;
};

#endif // FCPLUGINMANAGERDIALOG_H
