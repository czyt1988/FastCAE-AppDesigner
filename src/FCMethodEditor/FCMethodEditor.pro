QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
include($$PWD/../common.pri)
include($$PWD/../function.pri)
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = MethodEditor
#生成到bin下
$$commonProAppSet($${TARGET})

SOURCES += \
    FCMethodEditorGraphicsScene.cpp \
    FCMethodEditorGraphicsView.cpp \
    FCMethodEditorMainWindow.cpp \
    FCMethodEditorNodeFactory.cpp \
    FCMethodEditorPluginManager.cpp \
    FCNodeListWidget.cpp \
    FCPluginManagerDialog.cpp \
    FCProject.cpp \
    FCToolBox.cpp \
    main.cpp

HEADERS += \
    FCMethodEditorGraphicsScene.h \
    FCMethodEditorGraphicsView.h \
    FCMethodEditorMainWindow.h \
    FCMethodEditorNodeFactory.h \
    FCMethodEditorPluginManager.h \
    FCNodeListWidget.h \
    FCPluginManagerDialog.h \
    FCProject.h \
    FCToolBox.h

FORMS += \
    FCMethodEditorMainWindow.ui \
    FCPluginManagerDialog.ui

include($$PWD/Mime/Mime.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include($${FC_SRC_DIR}/FCPlugin/FCPlugin.pri)
include($${FC_SRC_DIR}/FCNode/FCNode.pri)
