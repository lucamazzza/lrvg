/**
 * @file		engine.cpp
 * @brief	Graphics engine main file
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@supsi.ch]
 */

#include "engine.h"
   
#include <iostream>   
#include <source_location>

struct Eng::Base::Reserved
{
   bool initFlag;
   Reserved() : initFlag{ false } 
   {}
};

ENG_API Eng::Base::Base() : reserved(std::make_unique<Eng::Base::Reserved>())
{  
#ifdef _DEBUG   
   std::cout << "[+] " << std::source_location::current().function_name() << " invoked" << std::endl;
#endif
}

ENG_API Eng::Base::~Base()
{
#ifdef _DEBUG
   std::cout << "[-] " << std::source_location::current().function_name() << " invoked" << std::endl;
#endif
}

Eng::Base ENG_API &Eng::Base::getInstance()
{
   static Base instance;
   return instance;
}

bool ENG_API Eng::Base::init()
{
   if (reserved->initFlag)
   {
      std::cout << "ERROR: engine already initialized" << std::endl;
      return false;
   }

   std::cout << "[>] " << LIB_NAME << " initialized" << std::endl;
   reserved->initFlag = true;
   return true;
}

bool ENG_API Eng::Base::free()
{
   if (!reserved->initFlag)
   {
      std::cout << "ERROR: engine not initialized" << std::endl;
      return false;
   }

   std::cout << "[<] " << LIB_NAME << " deinitialized" << std::endl;
   reserved->initFlag = false;
   return true;
}
