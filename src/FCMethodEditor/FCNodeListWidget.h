#ifndef FCNODELISTWIDGET_H
#define FCNODELISTWIDGET_H
#include <QListWidget>
#include <QListWidgetItem>
#include "FCNodeMetaData.h"
class FCNodeListWidgetItem : public QListWidgetItem {
public:
    FCNodeListWidgetItem(const FCNodeMetaData& node, QListWidget *listview = nullptr);
    FCNodeMetaData getNodeMetaData() const;
    void setNodeMetaData(const FCNodeMetaData& md);
};

/**
 * @brief 用于显示节点，并支持拖曳到view视图中
 */
class FCNodeListWidget : public QListWidget
{
    Q_OBJECT
public:
    FCNodeListWidget(QWidget *p = nullptr);
    void addItems(const QList<FCNodeMetaData>& nodeMetaDatas);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // FCNODELISTWIDGET_H
