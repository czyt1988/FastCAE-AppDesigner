#TEMPLATE	=   app
QT          +=  core gui xml widgets
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
    FCAbstractNodeGraphicsFactory.h \
    FCAbstractNodeGraphicsItem.h \
    FCConstValueNodeGraphicsItem.h \
    FCNode.h \
    FCNodeGlobal.h \
    FCNodeGraphicsFactory.h \
    FCNodeLink.h \
    FCNode_p.h \
    FCNodesLoader.h \
    FCNodesManager.h \
    FCProperties.h


SOURCES += \
    FCAbstractNodeGraphicsFactory.cpp \
    FCAbstractNodeGraphicsItem.cpp \
    FCConstValueNodeGraphicsItem.cpp \
    FCNode.cpp \
    FCNodeGraphicsFactory.cpp \
    FCNodeLink.cpp \
    FCNode_p.cpp \
    FCNodesLoader.cpp \
    FCNodesManager.cpp \
    FCProperties.cpp



