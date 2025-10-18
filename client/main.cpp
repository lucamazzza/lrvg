/**
 * @file	main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "engine.h"
#include <iostream>

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char *argv[])
{
   // Init engine:
   LRVGEngine::init("Hanoi", 800, 600);

   // Main loop:
   while (LRVGEngine::is_running()) {
	  LRVGEngine::update();
	  LRVGEngine::clear_screen();
	  LRVGEngine::render();
	  LRVGEngine::swap_buffers();
   }

   // Release engine:
   LRVGEngine::free();

   // Done:
   std::cout << "\n[application terminated]" << std::endl;
   return 0;
}
