#include <iostream>

#include "magos.h"

int main( int argc, char* argv[] ){

	Magos mg;

	// validate inputs
	mg.initializer( argc, argv );

	if( true ){

		std::cout << "Success..." << std::endl;	

	} else {

		std::cout << "Something wrong..." << std::endl;

		return EXIT_FAILURE;

	}

	return EXIT_SUCCESS;
	
}