#ifndef FCTESTNODEGRAPHICSITEM_H
#define FCTESTNODEGRAPHICSITEM_H
#include "FCUtilNodePluginGlobal.h"
#include "FCAbstractNodeGraphicsItem.h"
#include <QtCore/qglobal.h>

/**
 * @brief 测试节点，此节点用于测试，
 */
class FCUTILNODEPLUGIN_API FCTestNodeGraphicsItem : public FCAbstractNodeGraphicsItem
{
public:
    FCTestNodeGraphicsItem(QGraphicsItem *p = nullptr);
public:
    //绘图
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    //绘图相关
    QRectF boundingRect() const override;
};

#endif // FCTESTNODEGRAPHICSITEM_H
