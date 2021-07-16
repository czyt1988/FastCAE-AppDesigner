#include "FCNodeListWidget.h"

#define ROLE_PHOTOTYPE    (Qt::UserRole+1)

FCNodeListWidgetItem::FCNodeListWidgetItem(const FCNode *node, QListWidget *listview)
    : QListWidgetItem(QIcon(node->getPixmap()), node->getDescribe(), listview)
{
    setData(ROLE_PHOTOTYPE, node->getNodePrototype());
}


QString FCNodeListWidgetItem::getNodePhototype() const
{
    return (data(ROLE_PHOTOTYPE).toString());
}


FCNodeListWidget::FCNodeListWidget(QWidget *p) : QListWidget(p)
{
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setGridSize(QSize(45, 45));
}
