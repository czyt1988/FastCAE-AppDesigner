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
include($${FC_SRC_DIR}/FCPlugin/FCPlugin.pri)
HEADERS += \
    FCAbstractNodeGraphicsFactory.h \
    FCAbstractNodeGraphicsItem.h \
    FCAbstractNodePlugin.h \
    FCNodeGlobal.h \
    FCNodeMetaData.h \
    FCProperties.h


SOURCES += \
    FCAbstractNodeGraphicsFactory.cpp \
    FCAbstractNodeGraphicsItem.cpp \
    FCNodeMetaData.cpp \
    FCProperties.cpp


