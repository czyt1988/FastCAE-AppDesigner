#include "FCTestNodeGraphicsItem.h"
#include <QPainter>
#include "FCNodePalette.h"
#define RES_ICON    ":/icon/icon/test.svg"
FCTestNodeGraphicsItem::FCTestNodeGraphicsItem(QGraphicsItem *p)
    : FCAbstractNodeGraphicsItem(p)
{
    metaData().setIcon(QIcon(RES_ICON));
    metaData().setNodePrototype("FC.Test.Const");
    metaData().setNodeName(QObject::tr("Test1"));
    metaData().setGroup(QObject::tr("test"));
    QList<FCNodeLinkPoint>& lps = linkPoints();

    lps.append(FCNodeLinkPoint(QPoint(50-4, 25), "out", FCNodeLinkPoint::OutPut, FCNodeLinkPoint::East));
    lps.append(FCNodeLinkPoint(QPoint(25, 50-4), "out1", FCNodeLinkPoint::OutPut, FCNodeLinkPoint::South));
    lps.append(FCNodeLinkPoint(QPoint(0+4, 25), "in1", FCNodeLinkPoint::Input, FCNodeLinkPoint::West));
    lps.append(FCNodeLinkPoint(QPoint(25, 0+4), "in2", FCNodeLinkPoint::Input, FCNodeLinkPoint::North));
}


void FCTestNodeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen pen(FCNodePalette::getGlobalEdgeColor());
    QRectF rec = boundingRect();

    pen.setWidth(1);
    if (isSelected()) {
        pen.setWidth(2);
        pen.setColor(pen.color().darker());
        rec.adjust(1, 1, -1, -1);
    }
    painter->setPen(pen);
    painter->fillRect(rec, FCNodePalette::getGlobalBackgroundColor());
    painter->drawRect(rec);
    //绘制点
    paintLinkPoints(painter, option, widget);
    painter->restore();
}


QRectF FCTestNodeGraphicsItem::boundingRect() const
{
    return (QRectF(0, 0, 50, 50));
}
