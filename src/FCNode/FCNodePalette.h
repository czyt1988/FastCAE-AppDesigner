#ifndef FCNODEPALETTE_H
#define FCNODEPALETTE_H

#include <QtCore/qglobal.h>
#include <QColor>
#include "FCNodeGlobal.h"

/**
 * @brief 节点相关的调色板，这里封装了节点相关的大部分颜色，
 *
 * 尽量不要在节点绘制使用其他颜色，统一通过此颜色可以实现主题颜色的更换
 *
 * 参考office调色板的样式，每个调色板一共有7种颜色
 */
class FCNODE_API FCNodePalette
{
public:

    /**
     * @brief 颜色角色
     */
    enum Role {
        RoleText	= 0,    ///< 文本颜色
        RoleEdge	= 1,    ///< 边框颜色
        RoleBackground	= 2,    ///< 背景颜色
        RoleLinkPoint	= 3,    ///< 连接点的背景
        RoleLinkLine	= 4     ///< 连接线的颜色
    };
    FCNodePalette();
    static const FCNodePalette& getGlobalPalette();
    static void setGlobalPalette(FCNodePalette pl);
    static const QColor& getGlobalColor(Role r);
    static const QColor& getGlobalTextColor();
    static const QColor& getGlobalEdgeColor();
    static const QColor& getGlobalBackgroundColor();
    static const QColor& getGlobalLinkPointColor();
    static const QColor& getGlobalLinkLineColor();

    const QColor& getColor(Role r) const;
    const QColor& getTextColor() const;
    const QColor& getEdgeColor() const;
    const QColor& getBackgroundColor() const;
    const QColor& getLinkPointColor() const;
    const QColor& getLinkLineColor() const;

private:
    QList<QColor> m_colors;///< 存放所有颜色
};

#endif // FCNODEPALETTE_H
