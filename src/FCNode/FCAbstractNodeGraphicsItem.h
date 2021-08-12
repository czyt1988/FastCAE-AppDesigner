#ifndef FCABSTRACTNODEGRAPHICSITEM_H
#define FCABSTRACTNODEGRAPHICSITEM_H
#include "FCNodeGlobal.h"
#include <QAbstractGraphicsShapeItem>
#include <QIcon>
#include "FCNodeMetaData.h"
#include "FCNodeLinkPoint.h"
class FCAbstractNodeLinkGraphicsItem;
FC_IMPL_FORWARD_DECL(FCAbstractNodeGraphicsItem)

/**
 * @brief 这是节点的基类，fastcae所有节点都继承此类
 * 作为一个节点的QGraphicsItem，
 */
class FCNODE_API FCAbstractNodeGraphicsItem : public QAbstractGraphicsShapeItem
{
    FC_IMPL(FCAbstractNodeGraphicsItem)
    friend class FCAbstractNodeGraphicsFactory;
    friend class FCAbstractNodeLinkGraphicsItem;
    friend class FCNodeGraphicsScene;
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
    const QList<FCNodeLinkPoint>& getLinkPoints() const;

    //通过名字获取连接点
    FCNodeLinkPoint getLinkPoint(const QString& name) const;

    //判断是否存在连接点
    bool isHaveLinkPoint(const FCNodeLinkPoint& pl) const;

    //绘制连接点
    virtual void paintLinkPoints(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //绘制某个连接点
    virtual void paintLinkPoint(const FCNodeLinkPoint& pl, QPainter *painter);

    //获取连接点对应的矩形区域
    virtual QRect getlinkPointRect(const FCNodeLinkPoint& pl) const;

    //获取节点对应的窗口，一般保存节点的设置
    virtual QWidget *nodeWidget();

protected:
    //处理一些联动事件，如和FCAbstractNodeLinkGraphicsItem的联动
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value);

    //鼠标事件
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //获取连接点的内存引用
    QList<FCNodeLinkPoint>& linkPoints();

    //此函数用于FCAbstractNodeLinkGraphicsItem在调用attachedTo/From过程中调用
    bool recordLink(FCAbstractNodeLinkGraphicsItem *link, const FCNodeLinkPoint& pl);

    //连接的link在销毁时调用，把item记录的link信息消除
    bool callItemLinkIsDestroying(FCAbstractNodeLinkGraphicsItem *link, const FCNodeLinkPoint& pl);
};

#endif // FCNODEGRAPHICSITEM_H
