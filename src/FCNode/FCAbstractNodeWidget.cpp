#include "FCAbstractNodeWidget.h"
#include "FCAbstractNodeGraphicsItem.h"
class FCAbstractNodeWidgetPrivate {
    FC_IMPL_PUBLIC(FCAbstractNodeWidget)
public:
    FCAbstractNodeWidgetPrivate(FCAbstractNodeWidget *p);

    FCAbstractNodeGraphicsItem *_nodeItem;
};

FCAbstractNodeWidgetPrivate::FCAbstractNodeWidgetPrivate(FCAbstractNodeWidget *p) : q_ptr(p)
    , _nodeItem(nullptr)
{
}


FCAbstractNodeWidget::FCAbstractNodeWidget(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
    , d_ptr(new FCAbstractNodeWidgetPrivate(this))
{
}


FCAbstractNodeWidget::~FCAbstractNodeWidget()
{
}


void FCAbstractNodeWidget::setNodeItem(FCAbstractNodeGraphicsItem *item)
{
    d_ptr->_nodeItem = item;
}


FCAbstractNodeGraphicsItem *FCAbstractNodeWidget::getNodeItem() const
{
    return (d_ptr->_nodeItem);
}
