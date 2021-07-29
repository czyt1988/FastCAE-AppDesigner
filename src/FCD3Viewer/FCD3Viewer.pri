include(./../common.pri)
include(./../function.pri)
LIB_NAME=$$saLibNameMake(FCD3Viewer)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
include($${VTK_LIB_PRI_PATH})
include($${OCC_LIB_PRI_PATH})
LIBS += -L$${BIN_LIB_BUILD_DIR} -l$${LIB_NAME}

