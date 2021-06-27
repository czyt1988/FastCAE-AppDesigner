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
FC_SRC_DIR = $$PWD # 源代码路径
FC_3RD_PARTY_DIR = $${FC_SRC_DIR}/3rdparty # 第三方库路径
BIN_LIB_DIR = $$BIN_DIR/libs # 生成的lib路径
VTK_LIB_BASE_DIR = $${FC_3RD_PARTY_DIR}/VTK # 第三方库的VTK路径
OCC_LIB_BASE_DIR = $${FC_3RD_PARTY_DIR}/OCC # 第三方库的OCC路径
CTK_LIB_BASE_DIR = $${FC_3RD_PARTY_DIR}/CTK # 第三方库的CTK路径
CTK_INCLUDE_PATHS += $${CTK_LIB_BASE_DIR}/Core
CTK_INCLUDE_PATHS += $${CTK_LIB_BASE_DIR}/Widgets
VTK_LIB_PRI_PATH = $${VTK_LIB_BASE_DIR}/vtk.pri
OCC_LIB_PRI_PATH = $${OCC_LIB_BASE_DIR}/occ.pri
CTK_LIB_PRI_PATH = $${CTK_LIB_BASE_DIR}/ctk.pri
# 把当前目录作为include路径
INCLUDEPATH += $$PWD
