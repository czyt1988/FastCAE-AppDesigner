#ifndef FCCOMMONWIDGETSAPI_H
#define FCCOMMONWIDGETSAPI_H
#include <QtCore/QtGlobal>


#if defined(FCCOMMONWIDGETS_BUILD)
#define FCCOMMONWIDGETS_API    Q_DECL_EXPORT
#else
#define  FCCOMMONWIDGETS_API
#endif

//Q_DECL_IMPORT.
#endif // FCCOMMONWIDGETSAPI_H
