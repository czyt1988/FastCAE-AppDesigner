QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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

# 依赖
include($${FC_SRC_DIR}/FCPlugin/FCPlugin.pri)

HEADERS += \
    FCAbstractNodeGraphicsFactory.h \
    FCAbstractNodeGraphicsItem.h \
    FCAbstractNodeLinkGraphicsItem.h \
    FCAbstractNodePlugin.h \
    FCNodeGlobal.h \
    FCNodeGraphicsScene.h \
    FCNodeLinkPoint.h \
    FCNodeMetaData.h \
    FCNodePalette.h \
    FCNodeStandardLinkGraphicsItem.h \
    FCProperties.h


SOURCES += \
    FCAbstractNodeGraphicsFactory.cpp \
    FCAbstractNodeGraphicsItem.cpp \
    FCAbstractNodeLinkGraphicsItem.cpp \
    FCAbstractNodePlugin.cpp \
    FCNodeGraphicsScene.cpp \
    FCNodeLinkPoint.cpp \
    FCNodeMetaData.cpp \
    FCNodePalette.cpp \
    FCNodeStandardLinkGraphicsItem.cpp \
    FCProperties.cpp



