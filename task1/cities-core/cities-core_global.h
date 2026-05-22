#ifndef CITIES_CORE_GLOBAL_H
#define CITIES_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CITIES_CORE_LIBRARY)
#define CITIES_CORE_EXPORT Q_DECL_EXPORT
#else
#define CITIES_CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // CITIES_CORE_GLOBAL_H
