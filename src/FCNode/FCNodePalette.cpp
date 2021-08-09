#include "FCNodePalette.h"
static FCNodePalette s_default_node_palette = FCNodePalette();

FCNodePalette::FCNodePalette()
{
    m_colors<<QColor(0, 0, 0)       //RoleText
        <<QColor(78, 103, 200)  //RoleEdge
        <<QColor(255, 255, 255) //RoleBackground
        <<QColor(70, 175, 147)  //RoleLink
        <<QColor(93, 206, 175)  //RoleLinkLine
        <<QColor(255, 128, 33)
        <<QColor(241, 65, 36)
    ;
}


const FCNodePalette& FCNodePalette::getGlobalPalette()
{
    return (s_default_node_palette);
}


void FCNodePalette::setGlobalPalette(FCNodePalette pl)
{
    s_default_node_palette = pl;
}


const QColor& FCNodePalette::getGlobalColor(FCNodePalette::Role r)
{
    return (s_default_node_palette.getColor(r));
}


const QColor& FCNodePalette::getGlobalTextColor()
{
    return (s_default_node_palette.getTextColor());
}


const QColor& FCNodePalette::getGlobalEdgeColor()
{
    return (s_default_node_palette.getEdgeColor());
}


const QColor& FCNodePalette::getGlobalBackgroundColor()
{
    return (s_default_node_palette.getBackgroundColor());
}


const QColor& FCNodePalette::getGlobalLinkPointColor()
{
    return (s_default_node_palette.getLinkPointColor());
}


const QColor& FCNodePalette::getGlobalLinkLineColor()
{
    return (s_default_node_palette.getLinkLineColor());
}


const QColor& FCNodePalette::getColor(FCNodePalette::Role r) const
{
    return (m_colors[int(r)]);
}


const QColor& FCNodePalette::getTextColor() const
{
    return (getColor(RoleText));
}


const QColor& FCNodePalette::getEdgeColor() const
{
    return (getColor(RoleEdge));
}


const QColor& FCNodePalette::getBackgroundColor() const
{
    return (getColor(RoleBackground));
}


const QColor& FCNodePalette::getLinkPointColor() const
{
    return (getColor(RoleLinkPoint));
}


const QColor& FCNodePalette::getLinkLineColor() const
{
    return (getColor(RoleLinkLine));
}
