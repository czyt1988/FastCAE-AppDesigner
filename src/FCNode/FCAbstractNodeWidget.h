#ifndef FCABSTRACTNODEWIDGET_H
#define FCABSTRACTNODEWIDGET_H
#include <QWidget>
#include "FCNodeGlobal.h"
#include "FCAbstractNodeGraphicsItem.h"

/**
 * @brief FCNodeItem都可返回一个FCAbstractNodeWidget，用于设置node
 */
class FCAbstractNodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FCAbstractNodeWidget(QWidget *parent = nullptr, Qt::WindowFlags f);
    ~FCAbstractNodeWidget();
signals:
};

#endif // FCABSTRACTNODEWIDGET_H
