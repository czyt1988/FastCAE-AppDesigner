#include "FCD3ViewerCollectionInterface.h"
#include "FCD3ViewerDesignerPlugin.h"
FCD3ViewerCollectionInterface::FCD3ViewerCollectionInterface(QObject *p)
    : QObject(p)
{
    m_widgets.append(new FCD3ViewerDesignerPlugin(this));
}


QList<QDesignerCustomWidgetInterface *> FCD3ViewerCollectionInterface::customWidgets() const
{
    return (m_widgets);
}
