TEMPLATE = subdirs
SUBDIRS += \
          $$PWD/FCPlugin \
          $$PWD/FCNode \
          $$PWD/FCCommonWidgets \
          $$PWD/Plugin/FCUtilNodePlugin \
          $$PWD/FCMethodEditor

OTHER_FILES += \
    $$PWD/../readme.md

CONFIG   += ordered
