#pragma once

#if defined(PLATFORM_WINDOWS)
#if defined(YK_USE_DYNAMIC_LIB)
#if defined(YK_BUILD_DYNAMIC_LIB)
#define YK_API __declspec(dllexport)
#else
#define YK_API __declspec(dllimport)
#endif
#else
#define YK_API
#endif
#else
#if defined(YK_USE_DYNAMIC_LIB)
#define YK_API __attribute__((visibility("default")))
#else
#define YK_API
#endif
#endif