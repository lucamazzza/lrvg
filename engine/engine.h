/**
 * @file    engine.h
 * @brief	Graphics engine main include file
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#ifdef _DEBUG
#define LIB_NAME      "My Graphics Engine v0.1a (debug)"     ///< Library credits
#else
#define LIB_NAME      "My Graphics Engine v0.1a"             ///< Library credits
#endif
#define LIB_VERSION   10                                     ///< Library version (divide by 10)

#include <memory> 

#include "common.h"

namespace Eng {

/**
 * @brief Base engine main class. This class is a singleton.
 */
class ENG_API Base final {
public: 

   Base(Base const &) = delete;
   ~Base();
   void operator=(Base const &) = delete;
   static Base &getInstance();
   bool init();
   bool free();   

private: 
   struct Reserved;
   std::unique_ptr<Reserved> reserved;
   Base();
};
}; 
