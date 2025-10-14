/**
 * @file	common.h
 * @brief	TODO:
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <iostream>

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
 
#define _DEBUG

#ifdef _DEBUG
#define DEBUG( message ) \
   std::cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << " " << message << std::endl;
#else
#define DEBUG( message )
#endif
#define WARNING( message ) \
   std::cout << "[WARNING] " << __FILE__ << ":" << __LINE__ << " " << message << std::endl;
#define ERROR( message ) \
   std::cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << message << std::endl;

