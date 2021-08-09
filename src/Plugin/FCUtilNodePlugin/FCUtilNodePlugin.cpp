#include "FCUtilNodePlugin.h"
#include "FCNodeGraphicsFactory.h"
#include <QObject>

FCAbstractPlugin *plugin_create()
{
    return (new FCUtilNodePlugin());
}


void plugin_destory(FCAbstractPlugin *p)
{
    delete p;
}


FCUtilNodePlugin::FCUtilNodePlugin()
{
}


FCUtilNodePlugin::~FCUtilNodePlugin()
{
}


QString FCUtilNodePlugin::getIID() const
{
    return ("FC.FCUtilNodePlugin");
}


QString FCUtilNodePlugin::getName() const
{
    return ("FC Util Nodes");
}


QString FCUtilNodePlugin::getVersion() const
{
    return ("version 0.1.1");
}


QString FCUtilNodePlugin::getDescription() const
{
    return ("FastCAE Util Nodes");
}


FCAbstractNodeGraphicsFactory *FCUtilNodePlugin::createNodeFactory()
{
    return (new FCNodeGraphicsFactory());
}


void FCUtilNodePlugin::destoryNodeFactory(FCAbstractNodeGraphicsFactory *p)
{
    if (p) {
        p->deleteLater();
    }
}
