#ifndef FCABSTRACTNODEWIDGET_H
#define FCABSTRACTNODEWIDGET_H
#include <QWidget>
#include "FCNodeGlobal.h"
class FCAbstractNodeGraphicsItem;

FC_IMPL_FORWARD_DECL(FCAbstractNodeWidget)

/**
 * @brief FCNodeItem都可返回一个FCAbstractNodeWidget，用于设置node
 */
class FCAbstractNodeWidget : public QWidget
{
    Q_OBJECT
    FC_IMPL(FCAbstractNodeWidget)
public:
    explicit FCAbstractNodeWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~FCAbstractNodeWidget();

    //设置节点item
    void setNodeItem(FCAbstractNodeGraphicsItem *item);

    //获取保存的节点item指针
    FCAbstractNodeGraphicsItem *getNodeItem() const;
};

#endif // FCABSTRACTNODEWIDGET_H
