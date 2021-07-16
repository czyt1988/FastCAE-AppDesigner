#ifndef FCNODELISTWIDGET_H
#define FCNODELISTWIDGET_H
#include <QListWidget>
#include <QListWidgetItem>
#include <FCNode.h>
class FCNodeListWidgetItem : public QListWidgetItem {
public:
    FCNodeListWidgetItem(const FCNode *node, QListWidget *listview = nullptr);
    QString getNodePhototype() const;
};

/**
 * @brief 用于显示节点，并支持拖曳到view视图中
 */
class FCNodeListWidget : public QListWidget
{
    Q_OBJECT
public:
    FCNodeListWidget(QWidget *p = nullptr);
};

#endif // FCNODELISTWIDGET_H
