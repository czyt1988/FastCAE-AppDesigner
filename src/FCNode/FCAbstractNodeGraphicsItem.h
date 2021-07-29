#ifndef FCABSTRACTNODEGRAPHICSITEM_H
#define FCABSTRACTNODEGRAPHICSITEM_H
#include "FCNodeGlobal.h"
#include <QGraphicsItem>
#include <QIcon>
#include "FCNodeMetaData.h"
FC_IMPL_FORWARD_DECL(FCAbstractNodeGraphicsItem)

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
};

#endif // FCNODEGRAPHICSITEM_H
