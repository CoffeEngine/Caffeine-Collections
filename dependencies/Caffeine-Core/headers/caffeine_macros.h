#ifndef CAFFEINE_UTILS_MACROS_H
#define CAFFEINE_UTILS_MACROS_H

#include "caffeine_flags.h"

#if CFF_OS == WINDOWS
#define CFF_FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define CFF_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define cff_cast(type,value)(*(type*)&value)

#endif