#ifndef FCMETHODNODEGLOBAL_H
#define FCMETHODNODEGLOBAL_H
#include <QtCore/QtGlobal>


#if defined(FCNODE_BUILDLIB)
#define FCNODE_API    Q_DECL_EXPORT
#else
#define  FCNODE_API
#endif
#endif // FCMETHODNODEGLOBAL_H
