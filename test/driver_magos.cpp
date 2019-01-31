#include <iostream>

#include "magos.h"

int main( int argc, char* argv[] ){

	// instatiating magos game object
	Magos mg;

	// validate inputs
	mg.initializer( argc, argv );

	if( mg.get_state() == Magos::States::ERROR ){

		// std::cout << "And error occurred!" << std::endl;

		return EXIT_FAILURE;

	} else {	

		mg.welcome();

	}

	while( not mg.game_over() ){

		mg.process_events();
		mg.update();
		mg.renderize();

	}

	return EXIT_SUCCESS;
	
}