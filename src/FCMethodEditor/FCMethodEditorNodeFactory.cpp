#include "FCMethodEditorNodeFactory.h"

FCMethodEditorNodeFactory::FCMethodEditorNodeFactory()
{
}


void FCMethodEditorNodeFactory::registFactory(FCAbstractNodeGraphicsFactory *factory)
{
    QList<FCNodeMetaData> mds = factory->getNodesMetaData();

    for (const FCNodeMetaData& m : mds)
    {
        m_prototypeToFactory[m.getNodePrototype()] = factory;
    }
}


void FCMethodEditorNodeFactory::registFactorys(const QList<FCAbstractNodeGraphicsFactory *> factorys)
{
    for (FCAbstractNodeGraphicsFactory *f : factorys)
    {
        registFactory(f);
    }
}


FCAbstractNodeGraphicsItem *FCMethodEditorNodeFactory::create(const QString& prototype) const
{
    QPointer<FCAbstractNodeGraphicsFactory> factory = m_prototypeToFactory.value(prototype, nullptr);

    if (factory.isNull()) {
        return (nullptr);
    }
    return (factory->create(prototype));
}
