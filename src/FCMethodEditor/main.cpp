#include "FCMethodEditorMainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FCMethodEditorMainWindow w;

    w.show();

    return (a.exec());
}
