################################################################
# D3Viewer 插件
################################################################

# 获取qt的基本路劲信息
message(Qt path is:$$[QT_INSTALL_PREFIX])
message(Qt libs path is:$$[QT_INSTALL_LIBS])
message(Qt plugin path is:$$[QT_INSTALL_PLUGINS])
include($$PWD/../../common.pri)
include($$PWD/../../function.pri)

# 插件必须的配置
CONFIG += plugin
QT += uiplugin designer
QT += widgets core gui
# 插件默认的配置
TEMPLATE = lib
CONFIG += c++11
TARGET = $$saLibNameMake(FCD3ViewerDesignerPlugin)

#target.path = $$[QT_INSTALL_PLUGINS]/designer
#生成的dll路径
$$commonProLibSet($${TARGET})

include($${FC_SRC_DIR}/FCD3Viewer/FCD3Viewer.pri)

HEADERS += \
    FCD3ViewerCollectionInterface.h \
    FCD3ViewerDesignerPlugin.h


SOURCES += \
    FCD3ViewerCollectionInterface.cpp \
    FCD3ViewerDesignerPlugin.cpp


# 编译完成后自动把dll移动到$$[QT_INSTALL_PLUGINS]/designer下面
$$copyDesignerPluginToQtDesignerPath($${TARGET})



