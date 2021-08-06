#ifndef FCMETHODNODEGLOBAL_H
#define FCMETHODNODEGLOBAL_H
#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCNODE_BUILDLIB)
#define FCNODE_API    Q_DECL_EXPORT
#else
#define  FCNODE_API
#endif

#include <QGraphicsItem>

namespace FastCAE {
/**
 * @brief  定义本程序的Graphics item类型
 */
enum FCNodeGraphicsItemType {
    GraphicsNodeItem	= QGraphicsItem::UserType + 10          ///<针对FCNode的item
    , GraphicsLinkItem	= QGraphicsItem::UserType + 11
    , GraphicsNodeUserType	= QGraphicsItem::UserType + 1000        ///< 用户自定义的类型需要在此基础上加
};
}


#endif // FCMETHODNODEGLOBAL_H
