#ifndef FCABSTRACTNODEGRAPHICSITEM_H
#define FCABSTRACTNODEGRAPHICSITEM_H
#include "FCNodeGlobal.h"
#include <QGraphicsItem>
#include <QIcon>
#include "FCNodeMetaData.h"
FC_IMPL_FORWARD_DECL(FCAbstractNodeGraphicsItem)

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

/**
 * @brief 这是节点的基类，fastcae所有节点都继承此类
 * 作为一个节点的QGraphicsItem，
 */
class FCNODE_API FCAbstractNodeGraphicsItem : public QGraphicsItem
{
    FC_IMPL(FCAbstractNodeGraphicsItem)
    friend class FCAbstractNodeGraphicsFactory;
public:
    enum { Type = FastCAE::GraphicsNodeItem };
    int type() const
    {
        return (Type);
    }


public:
    FCAbstractNodeGraphicsItem(QGraphicsItem *p = nullptr);
    virtual ~FCAbstractNodeGraphicsItem();
    //获取node的名字
    QString getNodeName() const;
    void setNodeName(const QString& name);

    //获取node的类型，这个类型可以表征同一类型的node 这个不会进行翻译
    virtual QString getNodePrototype() const;

    //获取图标，图标是节点对应的图标
    QIcon getIcon() const;
    void setIcon(const QIcon& icon);

    //获取节点的元数据
    const FCNodeMetaData& metaData() const;
    FCNodeMetaData& metaData();

    //设置元数据
    void setMetaData(const FCNodeMetaData& metadata);

    //获取连接点
    virtual QList<FCNodeLinkPoint> getLinkPoints() const = 0;

    //绘制连接点
    virtual void paintLinkPoints(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //绘制某个连接点
    virtual void paintLinkPoint(const FCNodeLinkPoint& pl, QPainter *painter);

    //获取连接点对应的矩形区域
    virtual QRect getlinkPointRect(const FCNodeLinkPoint& pl) const;
};

#endif // FCNODEGRAPHICSITEM_H
