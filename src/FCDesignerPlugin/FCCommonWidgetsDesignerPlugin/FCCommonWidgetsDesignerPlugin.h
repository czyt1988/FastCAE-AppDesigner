#ifndef FCCOMMONWIDGETSDESIGNERPLUGIN_H
#define FCCOMMONWIDGETSDESIGNERPLUGIN_H
#include <QDesignerCustomWidgetInterface>
class QDesignerFormEditorInterface;
class QDesignerFormWindowInterface;

class FCCommonWidgetsDesignerPluginBase : public QObject,
                      public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    FCCommonWidgetsDesignerPluginBase(QObject *p = nullptr);
    virtual bool isContainer() const Q_DECL_OVERRIDE;
    virtual bool isInitialized() const Q_DECL_OVERRIDE;
    virtual QIcon icon() const Q_DECL_OVERRIDE;
    virtual QString codeTemplate() const Q_DECL_OVERRIDE;
    virtual QString domXml() const Q_DECL_OVERRIDE;
    virtual QString group() const Q_DECL_OVERRIDE;
    virtual QString includeFile() const Q_DECL_OVERRIDE;
    virtual QString name() const Q_DECL_OVERRIDE;
    virtual QString toolTip() const Q_DECL_OVERRIDE;
    virtual QString whatsThis() const Q_DECL_OVERRIDE;
    virtual void initialize(QDesignerFormEditorInterface *core) Q_DECL_OVERRIDE;

protected:
    QString d_name;
    QString d_include;
    QString d_toolTip;
    QString d_whatsThis;
    QString d_domXml;
    QString d_codeTemplate;
    QIcon d_icon;
private:
    bool d_isInitialized;
};

class FCColorPickerButtonDesignerPlugin : public FCCommonWidgetsDesignerPluginBase
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    FCColorPickerButtonDesignerPlugin(QObject *p);
    virtual QWidget *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
};

class FCPathLineEditDesignerPlugin : public FCCommonWidgetsDesignerPluginBase
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    FCPathLineEditDesignerPlugin(QObject *p);
    virtual QWidget *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
};

class FCCoordinatesWidgetDesignerPlugin : public FCCommonWidgetsDesignerPluginBase
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    FCCoordinatesWidgetDesignerPlugin(QObject *p);
    virtual QWidget *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
};
#endif // FCCOMMONWIDGETSDESIGNERPLUGIN_H
