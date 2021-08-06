#ifndef FCNODELINKPOINT_H
#define FCNODELINKPOINT_H
#include "FCNodeGlobal.h"
#include <QtCore/qglobal.h>


/**
 * @brief 用于表征连接点信息的数据
 */
class FCNODE_API FCNodeLinkPoint {
public:

    /**
     * @brief 连接点的方向
     */
    enum Direction {
        East,
        South,
        West,
        North
    };

    /**
     * @brief 节点的方法
     */
    enum Way {
        Input,  ///< 输入节点
        OutPut  ///< 输出节点
    };

    FCNodeLinkPoint();
    FCNodeLinkPoint(const QPoint& p, const QString& n, Way w = OutPut, Direction d = East);

    QPoint position;        ///< 连接点相对FCAbstractNodeGraphicsItem的位置
    QString name;           ///< 连接点名字
    Way way;                ///< 连接点的属性，是输入还是输出
    Direction direction;    ///< 连接点引线的伸出方向（用于绘制连线的时候指定方向）
};
Q_DECLARE_METATYPE(FCNodeLinkPoint)

//FCNodeLinkPoint 的等于号操作符
FCNODE_API bool operator ==(const FCNodeLinkPoint& a, const FCNodeLinkPoint& b);

#endif // FCNODELINKPOINT_H
