#ifndef FCD3VIEWERDESIGNERPLUGIN_H
#define FCD3VIEWERDESIGNERPLUGIN_H
#include <QDesignerCustomWidgetInterface>
class QDesignerFormEditorInterface;
class QDesignerFormWindowInterface;

class FCD3ViewerDesignerPlugin : public QObject,
                 public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    FCD3ViewerDesignerPlugin(QObject *p = nullptr);
    bool isContainer() const Q_DECL_OVERRIDE;
    bool isInitialized() const Q_DECL_OVERRIDE;
    QIcon icon() const Q_DECL_OVERRIDE;
    QString domXml() const Q_DECL_OVERRIDE;
    QString group() const Q_DECL_OVERRIDE;
    QString includeFile() const Q_DECL_OVERRIDE;
    QString name() const Q_DECL_OVERRIDE;
    QString toolTip() const Q_DECL_OVERRIDE;
    QString whatsThis() const Q_DECL_OVERRIDE;
    QWidget *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
    void initialize(QDesignerFormEditorInterface *core) Q_DECL_OVERRIDE;

private:
    bool m_isInitialized;
    QDesignerFormEditorInterface *m_formEditor;
};

#endif // D3VIEWERDESIGNERPLUGIN_H
