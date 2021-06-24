CONFIG(debug, debug|release){
    contains(QT_ARCH, i386) {
        BIN_DIR = $$PWD/../bin_qt$$[QT_VERSION]_debug
    }else {
        BIN_DIR = $$PWD/../bin_qt$$[QT_VERSION]_debug_64
    }
}else{
    contains(QT_ARCH, i386) {
        BIN_DIR = $$PWD/../bin_qt$$[QT_VERSION]_release
    }else {
        BIN_DIR = $$PWD/../bin_qt$$[QT_VERSION]_release_64
    }
}
BIN_LIB_DIR = $$BIN_DIR/libs
VTK_LIB_BASE_DIR = $$PWD/3rdparty/VTK
OCC_LIB_BASE_DIR = $$PWD/3rdparty/OCC
VTK_LIB_PRI_PATH = $${VTK_LIB_BASE_DIR}/vtk.pri
OCC_LIB_PRI_PATH = $${OCC_LIB_BASE_DIR}/occ.pri

# 把当前目录作为include路径
INCLUDEPATH += $$PWD
