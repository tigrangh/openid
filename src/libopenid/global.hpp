#pragma once

#include <openid.hpp/global>

#if defined(OPENID_LIBRARY)
#define OPENIDSHARED_EXPORT BELT_EXPORT
#else
#define OPENIDSHARED_EXPORT BELT_IMPORT
#endif
