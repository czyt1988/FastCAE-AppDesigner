#TEMPLATE	=   app
QT          +=  core
TEMPLATE = lib
DEFINES += FCPLUGIN_BUILDLIB
CONFIG		+=  c++11
CONFIG		+=  qt
include($$PWD/../common.pri)
include($$PWD/../function.pri)
TARGET = $$saLibNameMake(FCPlugin)
# 通用的设置
$$commonProLibSet($${TARGET})

# 在lib文件夹下编译完后，把dll文件拷贝到bin目录下
$$saCopyLibToBin($${TARGET})

HEADERS += \
    FCPluginGlobal.h \
    FCAbstractPlugin.h \
    FCPluginOption.h \
    FCPluginManager.h

SOURCES += \
    FCPluginManager.cpp \
    FCPluginOption.cpp \



