include(./../common.pri)
include(./../function.pri)
LIB_NAME=$$saLibNameMake(FCNode)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
LIBS += -L$${BIN_LIB_DIR} -l$${LIB_NAME}

