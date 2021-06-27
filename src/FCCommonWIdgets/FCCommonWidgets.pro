QT          +=  core gui widgets
#QT += opengl
TEMPLATE = lib
DEFINES += FCCOMMONWIDGETS_BUILD
CONFIG		+=  c++11
CONFIG		+=  qt
include($$PWD/../common.pri)
include($$PWD/../function.pri)
TARGET = $$saLibNameMake(FCCommonWidgets)
include($${CTK_LIB_PRI_PATH})
# 通用的设置
$$commonProLibSet($${TARGET})

# 在lib文件夹下编译完后，把dll文件拷贝到bin目录下
$$saCopyLibToBin($${TARGET})

HEADERS += \
    FCColorPickerButton.h \
    FCCommonWidgetsAPI.h \
    FCCoordinatesWidget.h \
    FCPathLineEdit.h

SOURCES += \
    FCColorPickerButton.cpp \
    FCCoordinatesWidget.cpp \
    FCPathLineEdit.cpp



