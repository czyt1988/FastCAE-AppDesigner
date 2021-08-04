#ifndef FCMETHODEDITORNODEFACTORY_H
#define FCMETHODEDITORNODEFACTORY_H

#include <QtCore/qglobal.h>
#include <QHash>
#include <QPointer>
#include "FCAbstractNodeGraphicsFactory.h"
#include "FCAbstractNodeGraphicsItem.h"

/**
 * @brief 这个是总工厂，汇总了所有插件的工厂
 */
class FCMethodEditorNodeFactory
{
public:
    FCMethodEditorNodeFactory();
    void registFactory(FCAbstractNodeGraphicsFactory *factory);
    void registFactorys(const QList<FCAbstractNodeGraphicsFactory *> factorys);
    FCAbstractNodeGraphicsItem *create(const QString& prototype) const;

private:
    QHash<QString, QPointer<FCAbstractNodeGraphicsFactory> > m_prototypeToFactory;///< 记录prototype对应的工厂
};

#endif // FCMETHODEDITORNODEFACTORY_H
