#ifndef FCPLUGINGLOBAL_H
#define FCPLUGINGLOBAL_H
#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCPLUGIN_BUILDLIB)
#define FCPLUGIN_API    Q_DECL_EXPORT
#else
#define  FCPLUGIN_API
#endif


#endif // FCPLUGINGLOBAL_H
