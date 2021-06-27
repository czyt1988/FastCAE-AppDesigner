#ifndef FCCOMMONWIDGETSCOLLECTIONINTERFACE_H
#define FCCOMMONWIDGETSCOLLECTIONINTERFACE_H
#include <QDesignerCustomWidgetInterface>

class FCCommonWidgetsCollectionInterface : public QObject,
                       public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FastCAE.AppDesigner.FCCommonWidgetsCollection")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
    FCCommonWidgetsCollectionInterface(QObject *p = nullptr);
    QList<QDesignerCustomWidgetInterface *> customWidgets() const Q_DECL_OVERRIDE;

private:
    QList<QDesignerCustomWidgetInterface *> m_widgets;
};

#endif // FCCOMMONWIDGETSCOLLECTIONINTERFACE_H
