#include <iostream>

#include "magos.h"

int main( int argc, char* argv[] ){

	Magos * mg;

	// validate inputs
	if( true ){
		
		mg->initializer( argc, argv );

	} else {

		std::cout << "something wrong..." << std::endl;

		return 0;

	}

	// std::cout << mg << std::endl;

	return 0;
	
}