#ifndef FCGRAPHICSITEMTYPE_H
#define FCGRAPHICSITEMTYPE_H
#include <QGraphicsItem>
namespace FastCAE {
/**
 * @brief  定义本程序的Graphics item类型
 */
enum FCGraphicsItemType {
    GraphicsNodeItem = QGraphicsItem::UserType + 100        ///<针对FCNode的item
    , GraphicsNodeLinkLineItem                              ///< 对应GGraphicsNodeLinkLineItem
};
}


#endif // FCGRAPHICSITEMTYPE_H
