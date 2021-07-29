include(./../common.pri)
include(./../function.pri)
LIB_NAME=$$saLibNameMake(FCPlugin)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
LIBS += -L$${BIN_LIB_BUILD_DIR} -l$${LIB_NAME}

