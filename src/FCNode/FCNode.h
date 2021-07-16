#ifndef FCNODE_H
#define FCNODE_H
#include "FCNodeGlobal.h"
#include <QVariant>
#include <QRectF>
#include <QPixmap>
#include <QDebug>
FC_IMPL_FORWARD_DECL(FCNode)

/**
 * @brief 用于描述节点的类,这个节点适合用在有向图结构里面，提供了pos，pixmap等用于绘图的函数，
 * 可以通用与Qt Graphview系统下的节点式绘制
 */
class FCNODE_API FCNode
{
    FC_IMPL(FCNode)
    friend class FCNodeLink;
    friend class FCNodesManager;
public:
    typedef  QHash<QString, QString> StringMap;
    FCNode();
    FCNode(const FCNode& other);
    FCNode(FCNode&& other);
    virtual ~FCNode();

    //获取node的名字
    QString getNodeName() const;
    void setNodeName(const QString& name);

    //获取描述
    QString getDescribe() const;
    void setDescribe(const QString& describe);

    //节点的范围
    QRectF getBoundingRect() const;
    void setBoundingRect(const QRectF& boundingRect);

    //获取节点的图片
    QPixmap getPixmap() const;
    void setPixmap(const QPixmap& pixmap);

    //图标的位置
    QRect getPixmapRect() const;
    void setPixmapRect(const QRect& pixmapRect);

    //获取链接点的数目
    int getConnectPointCount() const;

    //获取连接点的位置
    QPointF getConnectPoint(const QString& name) const;
    QPointF getConnectPointByIndex(int index) const;

    //添加链接点
    void addConnectPoint(const QString& name, const QPointF& p);

    //判断是否存在连接点
    bool isHaveConnectPoint(const QString& name) const;

    //获取所有连接点
    QList<QString> connectPointNames() const;

    //把connectPointName转换为描述的名字，connectPointName是一个类似id，connectPointDescribeName才是真实的名字
    QString connectPointNameToDescribeName(const QString& connectPointName) const;

    //节点在画布位置
    QPointF getPos() const;
    void setPos(const QPointF& pos);
    void setPos(double x, double y);

    //设置旋转
    void setRotation(qreal rotation);
    qreal getRotation() const;

    //用于存放内部数据
    void setData(QVariant d, int role = 0);
    QVariant getData(int role = 0) const;

    //复制一个实例，这个是一个工厂函数，需要自己手动销毁
    virtual FCNode *copy() const;

    //设置字典
    void setupStringMap(const QHash<QString, QString>& dict);

    //获取node的类型，这个类型可以表征同一类型的node 这个不会进行翻译
    QString getNodePrototype() const;
    void setNodePrototype(const QString& type);

protected:
};

FCNODE_API QDebug operator <<(QDebug debug, const FCNode& node);

#endif // FCNODE_H
