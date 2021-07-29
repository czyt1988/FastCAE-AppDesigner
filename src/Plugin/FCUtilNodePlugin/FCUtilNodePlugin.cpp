#include "FCUtilNodePlugin.h"
#include "FCNodeGraphicsFactory.h"
#include <QObject>

QString plugin_get_iid()
{
    return ("FC.FCUtilNodePlugin");
}


QString plugin_get_name()
{
    return ("FC Util Nodes");
}


QString plugin_get_version()
{
    return ("version 0.1.1");
}


QString plugin_get_description()
{
    return (QObject::tr("FastCAE Util Nodes"));
}


FCAbstractPlugin *plugin_create()
{
    return (new FCUtilNodePlugin());
}


void plugin_destory(FCAbstractPlugin *p)
{
}


FCUtilNodePlugin::FCUtilNodePlugin()
{
}


FCUtilNodePlugin::~FCUtilNodePlugin()
{
}


QString FCUtilNodePlugin::getIID() const
{
    return (plugin_get_iid());
}


QString FCUtilNodePlugin::getName() const
{
    return (plugin_get_name());
}


QString FCUtilNodePlugin::getVersion() const
{
    return (plugin_get_version());
}


QString FCUtilNodePlugin::getDescription() const
{
    return (plugin_get_description());
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
