/**
 * @file	main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

// #INCLUDE ///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "lrvg_engine.h"

#include <iostream>

// MAIN ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char *argv[])
{
   // Credits:
   std::cout << "Client application example, A. Peternier (C) SUPSI" << std::endl;
   std::cout << std::endl;

   // Init engine:
   LRVGEngine::init("Hanoi", 800, 600);

   // Main loop:
   LRVGEngine::run();

   // Release engine:
   LRVGEngine::free();

   // Done:
   std::cout << "\n[application terminated]" << std::endl;
   return 0;
}
