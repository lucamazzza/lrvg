/**
 * @file	common.h
 * @brief	Common includes and definitions
 *
 * This file contains common includes and definitions used throughout the project.
 * It includes standard libraries, third-party libraries, and project-specific headers.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

/** @defgroup LibraryInfo Library Information Macros
 * @{
 */
#define LIB_NAME            "LRVGEngine"      /**< Library name */
#define LIB_VERSION_MAJOR   "0"               /**< Major version number */
#define LIB_VERSION_MINOR   "1"               /**< Minor version number */
#define LIB_VERSION_PATCH   "0"               /**< Patch version number */
#define LIB_VERSION_STRING  LIB_NAME " v" LIB_VERSION_MAJOR "." LIB_VERSION_MINOR "." LIB_VERSION_PATCH /**< Full version string */
#ifndef BUILD_DATE
#define BUILD_DATE          0                 /**< Build date timestamp */
#endif
/** @} */

/** @defgroup ColorCodes ANSI Color Codes
 * @{
 */
#define RED_FG              "\033[31m"        /**< Red foreground color */
#define GRN_FG              "\033[32m"        /**< Green foreground color */
#define YLW_FG              "\033[33m"        /**< Yellow foreground color */
#define BLU_FG              "\033[34m"        /**< Blue foreground color */
#define MGN_FG              "\033[35m"        /**< Magenta foreground color */
#define CYN_FG              "\033[36m"        /**< Cyan foreground color */
#define RST_FG              "\033[0m"         /**< Reset foreground color */
/** @} */

#ifdef __cplusplus
extern "C" {
#else
typedef unsigned char bool;
#define true                ((bool)1)
#define false               ((bool)0)
#define TO_BOOL(x)          ((bool))!!(x))
#endif

/** @defgroup UtilityMacros Utility Macros
 * @{
 */
#define ARRAY_SIZE(arr)     (sizeof(arr)/sizeof((arr)[0]))  /**< Calculate array size */
#define MIN(a,b)            (((a)<(b))?(a):(b)              /**< Return minimum of two values */
#define MAX(a,b)            (((a)>(b))?(a):(b))             /**< Return maximum of two values */
#define SWAP(a,b)           do { a ^= b; b ^= a; a ^= b; } while (0) /**< Swap two values using XOR */
#define UNUSED(x)           (void)(x)                       /**< Mark variable as unused */
/** @} */

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
 
/** @defgroup LoggingMacros Logging and Debugging Macros
 * @{
 */
#ifndef NDEBUG
/** @brief Assert a condition with a message, active only in debug builds */
#define ASSERT(cond, msg)                                                     \
    do {                                                                      \
        if (!(cond)) {                                                        \
            fprintf(stderr, RED_FG "ASSERTION FAILED %s:%d: %s\n" RST_FG,     \
                __FILE__, __LINE__, msg);                                     \
            abort();                                                          \
        }                                                                     \
    } while (0)
/** @brief Print debug message with file and line information */
#define DEBUG(fmt, ...)      fprintf(stdout, CYN_FG "DEBUG %s:%d: " fmt "\n" RST_FG, __FILE__, __LINE__, ##__VA_ARGS__);
#define SUCCESS(fmt, ...)    fprintf(stdout, GRN_FG "SUCCESS: " fmt "\n" RST_FG, ##__VA_ARGS__);
#else
#define ASSERT(cond, msg)   ((void)0)
#define DEBUG(fmt, ...)     ((void)0)
#define SUCCESS(fmt, ...)   ((void)0)
#endif
#define INFO(fmt, ...)      fprintf(stdout, MGN_FG "INFO: " fmt "\n" RST_FG, ##__VA_ARGS__);
#define WARN(fmt, ...)      fprintf(stderr, YLW_FG "WARNING %s:%d: " fmt "\n" RST_FG, __FILE__, __LINE__, ##__VA_ARGS__);
/** @brief Print error message with file and line information */
#define ERROR(fmt, ...)     fprintf(stderr, RED_FG "ERROR %s:%d: " fmt "\n" RST_FG, __FILE__, __LINE__, ##__VA_ARGS__);
/** @} */

/** @defgroup CompilerHints Compiler Optimization Hints
 * @{
 */
#if defined(__GNUC__) || defined(__clang__)
#define LIKELY(x)           __builtin_expect(!!(x), 1)          /**< Hint that expression is likely true */
#define UNLIKELY(x)         __builtin_expect(!!(x), 0)          /**< Hint that expression is unlikely true */
#define INLINE              __attribute__((always_inline)) inline /**< Force inline function */
#define UNREF               __attribute__((unused))             /**< Mark as potentially unused */
#else
#define LIKELY(x)           (x)
#define UNLIKELY(x)         (x)
#define INLINE              inline
#define UNREF
#endif
/** @} */

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
