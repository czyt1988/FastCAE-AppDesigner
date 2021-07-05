#TEMPLATE	=   app
QT          +=  core gui widgets
TEMPLATE = lib
DEFINES += FCNODE_BUILDLIB
CONFIG		+=  c++11
CONFIG		+=  qt
include($$PWD/../common.pri)
include($$PWD/../function.pri)
TARGET = $$saLibNameMake(FCNode)
# 通用的设置
$$commonProLibSet($${TARGET})

# 在lib文件夹下编译完后，把dll文件拷贝到bin目录下
$$saCopyLibToBin($${TARGET})

HEADERS += \
    FCNode.h \
    FCNodeGlobal.h \
    FCNodeLink.h \
    FCNode_p.h \
    FCNodesManager.h


SOURCES += \
    FCNode.cpp \
    FCNodeLink.cpp \
    FCNode_p.cpp \
    FCNodesManager.cpp



