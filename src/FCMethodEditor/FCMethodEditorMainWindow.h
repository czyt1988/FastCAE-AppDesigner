﻿#ifndef METHODMAINWINDOW_H
#define METHODMAINWINDOW_H

#include <QMainWindow>
#include "FCNodeListWidget.h"

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

private:
    Ui::FCMethodEditorMainWindow *ui;
};
#endif // METHODMAINWINDOW_H
