#TEMPLATE	=   app
QT          +=  core gui widgets
TEMPLATE = lib
DEFINES += FCD3VIEWER_BUILDLIB
CONFIG		+=  c++11
CONFIG		+=  qt
include($$PWD/../common.pri)
include($$PWD/../function.pri)
include($${VTK_LIB_PRI_PATH})
include($${OCC_LIB_PRI_PATH})
TARGET = $$saLibNameMake(FCD3Viewer)
# 通用的设置
$$commonProLibSet($${TARGET})

# 在lib文件夹下编译完后，把dll文件拷贝到bin目录下
$$saCopyLibToBin($${TARGET})

HEADERS += \
        $$PWD/FCD3ViewerAPI.h \
        $$PWD/FCD3Viewer.h \
        FCAbstractGeometryDataIO.h \
        FCGeometryDataIOResult.h \
        FCGeometryDataIOWorker.h \
        FCIgesDataIO.h

SOURCES += \
        $$PWD/FCD3Viewer.cpp \
        FCAbstractGeometryDataIO.cpp \
        FCGeometryDataIOResult.cpp \
        FCGeometryDataIOWorker.cpp \
        FCIgesDataIO.cpp

RESOURCES += \
    icon.qrc


