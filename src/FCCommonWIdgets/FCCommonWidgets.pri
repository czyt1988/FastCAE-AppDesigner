include(./../common.pri)
include(./../function.pri)
LIB_NAME=$$saLibNameMake(FCCommonWidgets)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
INCLUDEPATH += $${CTK_INCLUDE_PATHS}
DEPENDPATH += $${CTK_INCLUDE_PATHS}
LIBS += -L$${BIN_LIB_BUILD_DIR} -l$${LIB_NAME}

