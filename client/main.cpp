/**
 * @file	main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@supsi.ch]
 */

#include <engine.h>
#include <iostream>

int main(int argc, char *argv[])
{
   // Credits:
   std::cout << "Client application example, A. Peternier (C) SUPSI" << std::endl;
   std::cout << std::endl;

   // Init engine:
   lrvg::Engine::init("Hanoi", 800, 600);

   // Done:
   std::cout << "\n[application terminated]" << std::endl;
   return 0;
}
