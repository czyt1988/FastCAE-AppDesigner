#include "FCNodeGraphicsFactory.h"
#include "FCConstValueNodeGraphicsItem.h"
#include "FCTestNodeGraphicsItem.h"
FCNodeGraphicsFactory::FCNodeGraphicsFactory(QObject *p) : FCAbstractNodeGraphicsFactory(p)
{
    createMetaData();
}


QString FCNodeGraphicsFactory::factoryName() const
{
    return ("FC.Util");
}


FCAbstractNodeGraphicsItem *FCNodeGraphicsFactory::create(const QString& prototype)
{
    FpCreate fp = m_prototypeTpfp.value(prototype, nullptr);

    if (fp) {
        return (fp());
    }
    return (nullptr);
}


QStringList FCNodeGraphicsFactory::getPrototypes() const
{
    QStringList res;

    res.reserve(m_prototypeTpfp.size());
    for (auto i = m_prototypeTpfp.begin(); i != m_prototypeTpfp.end(); ++i)
    {
        res.append(i.key().getNodePrototype());
    }
    return (res);
}


QList<FCNodeMetaData> FCNodeGraphicsFactory::getNodesMetaData() const
{
    return (m_prototypeTpfp.keys());
}


void FCNodeGraphicsFactory::createMetaData()
{
    FpCreate fp;

    //FCConstValueNodeGraphicsItem
    fp = []()->FCAbstractNodeGraphicsItem *{
            return (new FCConstValueNodeGraphicsItem());
        };
    m_prototypeTpfp[saveGetMetaType(fp())] = fp;
    //FCTestNodeGraphicsItem
    fp = []()->FCAbstractNodeGraphicsItem *{
            return (new FCTestNodeGraphicsItem());
        };
    m_prototypeTpfp[saveGetMetaType(fp())] = fp;
}


/**
 * @brief 这个主要是为了获取到FCAbstractNodeGraphicsItem对应的metadata，获取完metadata后把内存销毁
 * @param t
 * @return
 */
FCNodeMetaData FCNodeGraphicsFactory::saveGetMetaType(FCAbstractNodeGraphicsItem *t)
{
    FCNodeMetaData meta = t->metaData();

    delete t;
    return (meta);
}
