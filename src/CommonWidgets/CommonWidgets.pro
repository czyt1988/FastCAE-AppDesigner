#TEMPLATE	=   app
QT          +=  core gui widgets
TEMPLATE = lib
DEFINES += COMMONWIDGETS_BUILD
CONFIG		+=  c++11
CONFIG		+=  qt
include($$PWD/../common.pri)
include($$PWD/../function.pri)
TARGET = $$saLibNameMake(CommonWidgets)
# 通用的设置
$$commonProLibSet($${TARGET})

# 在lib文件夹下编译完后，把dll文件拷贝到bin目录下
$$saCopyLibToBin($${TARGET})

HEADERS += \ \
    CommonWidgetsAPI.h

SOURCES += \

RESOURCES += \
    icon.qrc


