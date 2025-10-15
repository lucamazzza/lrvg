/**
 * @file		engine.h
 * @brief	Graphics engine main include file
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@supsi.ch]
 */

#pragma once
       
#include <memory> 

#ifdef _DEBUG
   #define LIB_NAME      "My Graphics Engine v0.1a (debug)"   
#else
   #define LIB_NAME      "My Graphics Engine v0.1a"   
#endif
   #define LIB_VERSION   10                 

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

namespace Eng {
   class ENG_API Base final
   {
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

