################################################################
# 用于拷贝编译完成的库到对应目录
# czy.t@163.com
# 尘中远于2021年，添加快速部署脚本
################################################################
include( $${PWD}/common.pri )


#生成一个区别debug和release模式的lib名,输入一个lib名字
defineReplace(saLibNameMake) {
    LibName = $$1
    CONFIG(debug, debug|release){
        LibName = $${LibName}d
    }else{
        LibName = $${LibName}
    }
    return ($${LibName})
}

# 用于修正路径，对于window会把路径的/转变为\,unix下不作为
defineReplace(saFixPath) {
    PathName = $$1
    win32 {
        FixPathName = $$replace(PathName, /, \\)
    }
    unix {
        FixPathName = $${PathName}
    }
    return ($${FixPathName})
}

# 生成拷贝cmd命令
defineReplace(saCopyLibCMD) {
    LibName = $$1
    win32 {
        DIR1 = $${BIN_LIB_DIR}/$${LibName}.dll
    }
    unix {
        DIR1 = $${BIN_LIB_DIR}/$${LibName}.so
    }
    DIR2 = $${BIN_DIR}/
    DIR_FROM = $$saFixPath($${DIR1})
    DIR_TO = $$saFixPath($${DIR2})
    CMD_CPY = $${QMAKE_COPY} $${DIR_FROM} $${DIR_TO}
    return ($${CMD_CPY})
}

# 生成拷贝第三方库的cmd命令
defineReplace(saCopyFullPathCMD) {
    LibFullPath = $$1
    LibName = $$2
    win32 {
        DIR1 = $${LibFullPath}/$${LibName}.dll
    }
    unix {
        DIR1 = $${LibFullPath}/$${LibName}.so
    }
    DIR2 = $${BIN_DIR}/
    DIR_FROM = $$saFixPath($${DIR1})
    DIR_TO = $$saFixPath($${DIR2})
    CMD_CPY = $${QMAKE_COPY} $${DIR_FROM} $${DIR_TO}
    return ($${CMD_CPY})
}

# 生成拷贝第三方库的cmd命令 arg1: lib名称 此函数将从$$BIN_LIB_DIR的lib文件拷贝到$$BIN_DIR下
defineReplace(saCopyLibToBin) {
    CMD = $$saCopyLibCMD($$1)
    QMAKE_POST_LINK += $${CMD}
    export(QMAKE_POST_LINK)
    return (true)
}

# 生成拷贝第三方库的cmd命令 arg1: lib路径，arg2:lib名称 此函数需要自己定义lib路径，将拷贝到$$BIN_DIR下
defineReplace(saCopyFullPathLibToBin) {
    CMD = $$saCopyFullPathCMD($$1,$$2)
    QMAKE_POST_LINK += $${CMD}
    export(QMAKE_POST_LINK)
    return (true)
}

#通用的设置 传入生成的lib名
defineReplace(commonProLibSet) {
    #lib构建在lib目录下
    TARGET = $$1
    DESTDIR = $${BIN_LIB_DIR}
    MOC_DIR = $${DESTDIR}/$${TARGET}/moc
    RCC_DIR = $${DESTDIR}/$${TARGET}/rcc
    UI_DIR = $${DESTDIR}/$${TARGET}/qui
    OBJECTS_DIR = $${DESTDIR}/$${TARGET}/obj
    export(TARGET)
    export(DESTDIR)
    export(MOC_DIR)
    export(RCC_DIR)
    export(UI_DIR)
    export(OBJECTS_DIR)
    return (true)
}

# 此函数针对插件，把
defineReplace(copyDesignerPluginToQtDesignerPath) {
    LIBNAME = $$1
    win32 {
        LIBFILENAME = $${LIBNAME}.dll
        DIR_FROM = $${BIN_LIB_DIR}/$${LIBFILENAME}
    }
    unix {
        LIBFILENAME = $${LIBNAME}.so
        DIR_FROM = $${BIN_LIB_DIR}/$${LIBFILENAME}
    }
    DIR_FROM = $$saFixPath($${DIR_FROM})
    PLUGINDLL_DESIGNER_PATH = $$[QT_INSTALL_PLUGINS]/designer/$${LIBFILENAME}
    PLUGINDLL_DESIGNER_PATH = $$saFixPath($${PLUGINDLL_DESIGNER_PATH})
    CMD_CPY = $${QMAKE_COPY} $${DIR_FROM} $${PLUGINDLL_DESIGNER_PATH}
    message(cmd:$${CMD_CPY})
    QMAKE_POST_LINK += $${CMD_CPY}
    export(QMAKE_POST_LINK)
    return (true)
}
