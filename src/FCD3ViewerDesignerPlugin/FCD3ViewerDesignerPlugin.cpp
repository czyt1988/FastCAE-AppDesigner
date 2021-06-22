#include "FCD3ViewerDesignerPlugin.h"
#include <QWidget>
#include "FCD3Viewer.h"
#include <QExtensionManager>
#include <QDesignerFormEditorInterface>
FCD3ViewerDesignerPlugin::FCD3ViewerDesignerPlugin(QObject *p)
    : QObject(p)
    , m_isInitialized(false)
{
}


bool FCD3ViewerDesignerPlugin::isContainer() const
{
    return (false);
}


bool FCD3ViewerDesignerPlugin::isInitialized() const
{
    return (m_isInitialized);
}


QIcon FCD3ViewerDesignerPlugin::icon() const
{
    return (QIcon());
}


QString FCD3ViewerDesignerPlugin::domXml() const
{
    return QString("<ui language=\"c++\">\n"
           " <widget class=\"%1\" name=\"d3Viewer\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>400</width>\n"
           "    <height>400</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n").arg(name());
}


QString FCD3ViewerDesignerPlugin::group() const
{
    return (QStringLiteral("FastCAE"));
}


QString FCD3ViewerDesignerPlugin::includeFile() const
{
    return ("FCD3Viewer.h");
}


QString FCD3ViewerDesignerPlugin::name() const
{
    return ("FCD3Viewer");
}


QString FCD3ViewerDesignerPlugin::toolTip() const
{
    return (tr("FastCAE 3D Viewer"));
}


QString FCD3ViewerDesignerPlugin::whatsThis() const
{
    return (tr("FastCAE 3D Viewer"));
}


QWidget *FCD3ViewerDesignerPlugin::createWidget(QWidget *parent)
{
    FCD3Viewer *v = new FCD3Viewer(parent);

    return (v);
}


void FCD3ViewerDesignerPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_isInitialized) {
        return;
    }

    QExtensionManager *manager = core->extensionManager();

    if (manager) {
    }

    m_isInitialized = true;
}
