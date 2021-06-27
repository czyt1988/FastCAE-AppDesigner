#include "FCCommonWidgetsCollectionInterface.h"
#include "FCCommonWidgetsDesignerPlugin.h"
FCCommonWidgetsCollectionInterface::FCCommonWidgetsCollectionInterface(QObject *p)
    : QObject(p)
{
    m_widgets.append(new FCColorPickerButtonDesignerPlugin(this));
    m_widgets.append(new FCPathLineEditDesignerPlugin(this));
    m_widgets.append(new FCCoordinatesWidgetDesignerPlugin(this));
}


QList<QDesignerCustomWidgetInterface *> FCCommonWidgetsCollectionInterface::customWidgets() const
{
    return (m_widgets);
}
