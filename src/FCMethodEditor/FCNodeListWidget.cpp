#include "FCNodeListWidget.h"
#include "FCNodeMimeData.h"
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDrag>
#define ROLE_META_DATA    (Qt::UserRole+1)

FCNodeListWidgetItem::FCNodeListWidgetItem(const FCNodeMetaData& node, QListWidget *listview)
    : QListWidgetItem(listview)
{
    setNodeMetaData(node);
}


FCNodeMetaData FCNodeListWidgetItem::getNodeMetaData() const
{
    return (data(ROLE_META_DATA).value<FCNodeMetaData>());
}


void FCNodeListWidgetItem::setNodeMetaData(const FCNodeMetaData& md)
{
    setIcon(md.getIcon());
    setText(md.getNodeName());
    setData(ROLE_META_DATA, QVariant::fromValue(md));
}


FCNodeListWidget::FCNodeListWidget(QWidget *p) : QListWidget(p)
{
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setGridSize(QSize(45, 45));
    setDragDropMode(DragOnly);
}


void FCNodeListWidget::addItems(const QList<FCNodeMetaData>& nodeMetaDatas)
{
    for (const FCNodeMetaData& d : nodeMetaDatas)
    {
        addItem(new FCNodeListWidgetItem(d));
    }
}


void FCNodeListWidget::mousePressEvent(QMouseEvent *event)
{
    FCNodeListWidgetItem *item = static_cast<FCNodeListWidgetItem *>(itemAt(event->pos()));

    if (nullptr == item) {
        return (QListWidget::mousePressEvent(event));
    }
    FCNodeMetaData nodemd = item->getNodeMetaData();
    FCNodeMimeData *md = new FCNodeMimeData(nodemd);
    QDrag *drag = new QDrag(this);

    drag->setMimeData(md);
    drag->setPixmap(nodemd.getIcon().pixmap(30, 30));
    drag->setHotSpot(event->pos());
    drag->exec();
}
