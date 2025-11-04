/**
 * @file	common.h
 * @brief	Common includes and definitions
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include <iostream>

#pragma once

#define NDEBUG

#define LIB_NAME            "LRVGEngine"
#define LIB_VERSION_MAJOR   "0"
#define LIB_VERSION_MINOR   "1"
#define LIB_VERSION_PATCH   "0"
#define LIB_VERSION_STRING  LIB_NAME " v" LIB_VERSION_MAJOR "." LIB_VERSION_MINOR "." LIB_VERSION_PATCH
#ifndef BUILD_DATE
#define BUILD_DATE          0
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
 

#ifdef NDEBUG
#define DEBUG(fmt, ...)     std::fprintf(stdout, "[DEBUG] %s %d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define DEBUG(fmt, ...)     ((void)0)
#endif
#define INFO(fmt, ...)      std::fprintf(stdout, "[INFO] %s %d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define WARNING(fmt, ...)   std::fprintf(stderr, "[WARNING] %s %d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define ERROR(fmt, ...)     std::fprintf(stderr, "[ERROR] %s %d: ", fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define ASSERT(x) \
    do { \
        if (!(x)) { \
            ERROR("Assertion failed: %s (%s:%d)", #x, __FILE__, __LINE__); \
            assert(x); \
        } \
    } while (0)

#define UNUSED(x)           (void)(x)
