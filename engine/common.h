/**
 * @file	common.h
 * @brief	Common includes and definitions
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#define LIB_NAME            "LRVGEngine"
#define LIB_VERSION_MAJOR   "0"
#define LIB_VERSION_MINOR   "1"
#define LIB_VERSION_PATCH   "0"
#define LIB_VERSION_STRING  LIB_NAME " v" LIB_VERSION_MAJOR "." LIB_VERSION_MINOR "." LIB_VERSION_PATCH
#ifndef BUILD_DATE
#define BUILD_DATE          0
#endif

#ifdef __cplusplus
extern "C" {
#else
typedef unsigned char bool;
#define true                ((bool)1)
#define false               ((bool)0)
#define TO_BOOL(x)          ((bool))!!(x))
#endif

#define ARRAY_SIZE(arr)     (sizeof(arr)/sizeof((arr)[0]))
#define MIN(a,b)            (((a)<(b))?(a):(b)
#define MAX(a,b)            (((a)>(b))?(a):(b))
#define SWAP(a,b)           do { a ^= b; b ^= a; a ^= b; } while (0)
#define UNUSED(x)           (void)(x)

#ifdef _WINDOWS
#ifdef ENGINE_EXPORTS
#define ENG_API __declspec(dllexport)
#else
#define ENG_API __declspec(dllimport)
#endif      
#pragma warning(disable : 4251) 
#else
#define ENG_API
#endif
 
#ifndef NDEBUG
#define ASSERT(cond, msg)                                       \
    do {                                                        \
        if (!(condition)) {                                     \
            fprintf(stderr, "ASSERTION FAILED in %s:%d: %s\n",  \
                __FILE__, __LINE__, message);                   \
            abort();                                            \
        }                                                       \
    } while (0)
#define DEBUG(fmt, ...)      fprintf(stderr, "DEBUG %s:%d:      " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define ASSERT(cond, msg)   ((void)0)
#define DEBUG(fmt, ...)     ((void)0)
#endif
#define INFO(fmt, ...)      fprintf(stdout, "INFO:              " fmt "\n",                     ##__VA_ARGS__);
#define WARN(fmt, ...)      fprintf(stderr, "WARNING %s:%d:     " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);
#define ERROR(fmt, ...)     fprintf(stderr, "ERROR %s:%d:       " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);

#if defined(__GNUC__) || defined(__clang__)
#define LIKELY(x)           __builtin_expect(!!(x), 1)
#define UNLIKELY(x)         __builtin_expect(!!(x), 0)
#define INLINE              __attribute__((always_inline)) inline
#define UNREF               __attribute__((unused))
#else
#define LIKELY(x)           (void)(x)
#define UNLIKELY(x)         (void)(x)
#define INLINE              inline
#define UNREF
#endif

#ifdef __cplusplus
}
#endif

#ifdef _WINDOWS
#ifdef ENGINE_EXPORTS
#define ENG_API __declspec(dllexport)
#else
#define ENG_API __declspec(dllimport)
#endif      
#pragma warning(disable : 4251) 
#else
#define ENG_API
#endif
