QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
DEFINES += FCUTILNODEPLUGIN_BUILDLIB
CONFIG		+=  c++11
CONFIG		+=  qt
include($$PWD/../../common.pri)
include($$PWD/../../function.pri)
TARGET = $$saLibNameMake(FCUtilNodePlugin)
# 通用的设置
$$commonProPluginSet($${TARGET})

# 在lib文件夹下编译完后，把dll文件拷贝到bin/plugins目录下
$$saCopyPluginLibToPlugin($${TARGET})

#引入插件
include($${FC_SRC_DIR}/FCPlugin/FCPlugin.pri)
#引入节点
include($${FC_SRC_DIR}/FCNode/FCNode.pri)
HEADERS += \
    FCConstValueNodeGraphicsItem.h \
    FCNodeGraphicsFactory.h \
    FCTestNodeGraphicsItem.h \
    FCUtilNodePlugin.h \
    FCUtilNodePluginGlobal.h


SOURCES += \
    FCConstValueNodeGraphicsItem.cpp \
    FCNodeGraphicsFactory.cpp \
    FCTestNodeGraphicsItem.cpp \
    FCUtilNodePlugin.cpp

RESOURCES += \
    resource.qrc




