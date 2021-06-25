INCLUDEPATH += $$PWD/Core
DEPENDPATH += $$PWD/Core
INCLUDEPATH += $$PWD/Widgets
DEPENDPATH +=  $$PWD/Widgets
#win32: LIBS += -lOpenGL32
#win32: LIBS += -lGlU32
HEADERS += \
    $$PWD/Core/ctkCoreExport.h \
    $$PWD/Core/ctkLogger.h \
    $$PWD/Core/ctkPimpl.h \
    $$PWD/Core/ctkSingleton.h \
    $$PWD/Core/ctkUtils.h \
    $$PWD/Core/ctkValueProxy.h \
    $$PWD/Widgets/ctkBasePopupWidget.h \
    $$PWD/Widgets/ctkBasePopupWidget_p.h \
    $$PWD/Widgets/ctkCollapsibleGroupBox.h \
    $$PWD/Widgets/ctkColorDialog.h \
    $$PWD/Widgets/ctkColorPickerButton.h \
    $$PWD/Widgets/ctkCoordinatesWidget.h \
    $$PWD/Widgets/ctkCoordinatesWidget_p.h \
    $$PWD/Widgets/ctkDoubleRangeSlider.h \
    $$PWD/Widgets/ctkDoubleSlider.h \
    $$PWD/Widgets/ctkDoubleSpinBox.h \
    $$PWD/Widgets/ctkDoubleSpinBox_p.h \
    $$PWD/Widgets/ctkExpandButton.h \
    $$PWD/Widgets/ctkMaterialPropertyPreviewLabel.h \
    $$PWD/Widgets/ctkMaterialPropertyWidget.h \
    $$PWD/Widgets/ctkMatrixWidget.h \
    $$PWD/Widgets/ctkPathLineEdit.h \
    $$PWD/Widgets/ctkPopupWidget.h \
    $$PWD/Widgets/ctkPopupWidget_p.h \
    $$PWD/Widgets/ctkProxyStyle.h \
    $$PWD/Widgets/ctkRangeSlider.h \
    $$PWD/Widgets/ctkRangeWidget.h \
    $$PWD/Widgets/ctkSliderWidget.h \
    $$PWD/Widgets/ctkWidgetsExport.h

SOURCES += \
    $$PWD/Core/ctkLogger.cpp \
    $$PWD/Core/ctkUtils.cpp \
    $$PWD/Core/ctkValueProxy.cpp \
    $$PWD/Widgets/ctkBasePopupWidget.cpp \
    $$PWD/Widgets/ctkCollapsibleGroupBox.cpp \
    $$PWD/Widgets/ctkColorDialog.cpp \
    $$PWD/Widgets/ctkColorPickerButton.cpp \
    $$PWD/Widgets/ctkCoordinatesWidget.cpp \
    $$PWD/Widgets/ctkDoubleRangeSlider.cpp \
    $$PWD/Widgets/ctkDoubleSlider.cpp \
    $$PWD/Widgets/ctkDoubleSpinBox.cpp \
    $$PWD/Widgets/ctkExpandButton.cpp \
    $$PWD/Widgets/ctkMaterialPropertyPreviewLabel.cpp \
    $$PWD/Widgets/ctkMaterialPropertyWidget.cpp \
    $$PWD/Widgets/ctkMatrixWidget.cpp \
    $$PWD/Widgets/ctkPathLineEdit.cpp \
    $$PWD/Widgets/ctkPopupWidget.cpp \
    $$PWD/Widgets/ctkProxyStyle.cpp \
    $$PWD/Widgets/ctkRangeSlider.cpp \
    $$PWD/Widgets/ctkRangeWidget.cpp \
    $$PWD/Widgets/ctkSliderWidget.cpp


RESOURCES += \
    $$PWD/Widgets/Resources/ctkWidgets.qrc

FORMS += \
    $$PWD/Widgets/Resources/UI/ctkMaterialPropertyWidget.ui \
    $$PWD/Widgets/Resources/UI/ctkRangeWidget.ui \
    $$PWD/Widgets/Resources/UI/ctkSliderWidget.ui
