include(./../common.pri)
include(./../function.pri)
LIB_NAME=$$saLibNameMake(FCD3Viewer)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
HEADERS += \
        $$PWD/FCD3ViewerAPI.h \
        $$PWD/FCD3Viewer.h

include($${VTK_LIB_PRI_PATH})
include($${OCC_LIB_PRI_PATH})
LIBS += -L$${BIN_LIB_DIR} -l$${LIB_NAME}

