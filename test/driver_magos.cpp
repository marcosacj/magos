#include <iostream>

#include "magos.h"

int main( int argc, char* argv[] ){

	// pointers to objects to be used in the game
	// Maze * m;
	// Render * r;
	// HashBuilder * b;
	// Solver * s;

	// instatiating magos game object
	// Magos mg { m, r, b, s } ;
	Magos mg;

	// validate inputs
	mg.initializer( argc, argv );

	if( mg.get_state() == Magos::States::ERROR ){

		std::cout << "Something wrong..." << std::endl;

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