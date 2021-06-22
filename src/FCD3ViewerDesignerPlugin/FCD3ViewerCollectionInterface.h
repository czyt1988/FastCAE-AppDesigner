#ifndef FCD3VIEWERCOLLECTIONINTERFACE_H
#define FCD3VIEWERCOLLECTIONINTERFACE_H
#include <QDesignerCustomWidgetInterface>

class FCD3ViewerCollectionInterface : public QObject,
                      public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FastCAE.AppDesigner.FCD3ViewerPluginCollection")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
    FCD3ViewerCollectionInterface(QObject *p = nullptr);
    QList<QDesignerCustomWidgetInterface *> customWidgets() const Q_DECL_OVERRIDE;

private:
    QList<QDesignerCustomWidgetInterface *> m_widgets;
};

#endif // D3VIEWERCOLLECTIONINTERFACE_H
