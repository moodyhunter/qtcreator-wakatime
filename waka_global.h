#pragma once

#if defined(WAKATIME_LIBRARY)
#  define WAKATIME_EXPORT Q_DECL_EXPORT
#else
#  define WAKATIME_EXPORT Q_DECL_IMPORT
#endif
