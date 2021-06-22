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
VTK_LIB_BASE_DIR = $$PWD/VTK
OCC_LIB_BASE_DIR = $$PWD/OCC
VTK_LIB_PRI_PATH = $${VTK_LIB_BASE_DIR}/vtk.pri
OCC_LIB_PRI_PATH = $${OCC_LIB_BASE_DIR}/occ.pri

# 把当前目录作为include路径
INCLUDEPATH += $$PWD
