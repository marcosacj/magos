#include <iostream>

#include "magos.h"

int main( int argc, char* argv[] ){

	Magos mg;

	// validate inputs
	mg.initializer( argc, argv );

	if( mg.get_state() == Magos::States::ERROR ){

		std::cout << "Something wrong..." << std::endl;

		return EXIT_FAILURE;

	} else {

		std::cout << "Success..." << std::endl;	

		mg.welcome();

	}

	while( not mg.game_over() ){

		mg.process_events();
		mg.update();
		mg.renderize();

	}

	return EXIT_SUCCESS;
	
}