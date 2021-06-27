#include "FCCommonWidgetsDesignerPlugin.h"
#include <QExtensionManager>
#include <QDesignerFormEditorInterface>
#include "FCCoordinatesWidget.h"
#include "FCColorPickerButton.h"
#include "FCPathLineEdit.h"

FCCommonWidgetsDesignerPluginBase::FCCommonWidgetsDesignerPluginBase(QObject *p)
    : QObject(p)
    , d_isInitialized(false)
{
}


bool FCCommonWidgetsDesignerPluginBase::isContainer() const
{
    return (false);
}


bool FCCommonWidgetsDesignerPluginBase::isInitialized() const
{
    return (d_isInitialized);
}


QIcon FCCommonWidgetsDesignerPluginBase::icon() const
{
    return (d_icon);
}


QString FCCommonWidgetsDesignerPluginBase::codeTemplate() const
{
    return (d_codeTemplate);
}


QString FCCommonWidgetsDesignerPluginBase::domXml() const
{
    return (d_domXml);
}


QString FCCommonWidgetsDesignerPluginBase::group() const
{
    return (QStringLiteral("FastCAE"));
}


QString FCCommonWidgetsDesignerPluginBase::includeFile() const
{
    return (d_include);
}


QString FCCommonWidgetsDesignerPluginBase::name() const
{
    return (d_name);
}


QString FCCommonWidgetsDesignerPluginBase::toolTip() const
{
    return (d_toolTip);
}


QString FCCommonWidgetsDesignerPluginBase::whatsThis() const
{
    return (d_whatsThis);
}


void FCCommonWidgetsDesignerPluginBase::initialize(QDesignerFormEditorInterface *core)
{
    if (d_isInitialized) {
        return;
    }

    QExtensionManager *manager = core->extensionManager();

    if (manager) {
        //TODO
    }

    d_isInitialized = true;
}


////////////////////////////////////////////////////////////////////////


FCColorPickerButtonDesignerPlugin::FCColorPickerButtonDesignerPlugin(QObject *p)
    : FCCommonWidgetsDesignerPluginBase(p)
{
    d_name = "FCColorPickerButton";
    d_include = "FCColorPickerButton.h";
    d_domXml =
        "<widget class=\"FCColorPickerButton\" name=\"colorPickerButton\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>80</width>\n"
        "   <height>32</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}


QWidget *FCColorPickerButtonDesignerPlugin::createWidget(QWidget *parent)
{
    return (new FCColorPickerButton(parent));
}


////////////////////////////////////////////////////////////////////////

FCPathLineEditDesignerPlugin::FCPathLineEditDesignerPlugin(QObject *p)
    : FCCommonWidgetsDesignerPluginBase(p)
{
    d_name = "FCPathLineEdit";
    d_include = "FCPathLineEdit.h";
    d_domXml =
        "<widget class=\"FCPathLineEdit\" name=\"pathLineEdit\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>120</width>\n"
        "   <height>32</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}


QWidget *FCPathLineEditDesignerPlugin::createWidget(QWidget *parent)
{
    return (new FCPathLineEdit(parent));
}


////////////////////////////////////////////////////////////////////////

FCCoordinatesWidgetDesignerPlugin::FCCoordinatesWidgetDesignerPlugin(QObject *p)
    : FCCommonWidgetsDesignerPluginBase(p)
{
    d_name = "FCCoordinatesWidget";
    d_include = "FCCoordinatesWidget.h";
    d_domXml =
        "<widget class=\"FCCoordinatesWidget\" name=\"coordinatesWidget\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>250</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}


QWidget *FCCoordinatesWidgetDesignerPlugin::createWidget(QWidget *parent)
{
    return (new FCCoordinatesWidget(parent));
}
