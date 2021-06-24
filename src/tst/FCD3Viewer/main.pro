QT          +=  core gui widgets
TEMPLATE	=   app
CONFIG		+=  c++11
CONFIG		+=  qt
TARGET		=   D3Test

include($$PWD/../common.pri)

DESTDIR = $${BIN_DIR}
MOC_DIR = $${DESTDIR}/build/$${TARGET}/moc
RCC_DIR = $${DESTDIR}/build/$${TARGET}/rcc
UI_DIR = $${DESTDIR}/build/$${TARGET}/qui
OBJECTS_DIR = $${DESTDIR}/build/$${TARGET}/obj

HEADERS += \
        $$PWD/MainWindow.h

SOURCES += \
	$$PWD/MainWindow.cpp \
        $$PWD/main.cpp

FORMS += \
        $$PWD/MainWindow.ui

include($$PWD/../FCD3Viewer/FCD3Viewer.pri)








