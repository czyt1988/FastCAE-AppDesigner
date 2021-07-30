#include "FCNodeListWidget.h"

#define ROLE_META_DATA    (Qt::UserRole+1)

FCNodeListWidgetItem::FCNodeListWidgetItem(FCNodeMetaData node, QListWidget *listview)
    : QListWidgetItem(QIcon(node.getIcon()), node.getNodeName(), listview)
{
    setData(ROLE_META_DATA, QVariant::fromValue(node));
}


QString FCNodeListWidgetItem::getNodePhototype() const
{
    return (data(ROLE_META_DATA).value<FCNodeMetaData>().getNodePrototype());
}


FCNodeListWidget::FCNodeListWidget(QWidget *p) : QListWidget(p)
{
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setGridSize(QSize(45, 45));
}
