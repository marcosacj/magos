#include <iostream>

#include "builder.h"
#include "wallf.h"

int main( int argc, char* argv[] ){

	if( argc < 4 ){

		std::cout << "Invalid arguments!" << std::endl;

		std::cout 	<< "Try " << argv[0]
					<< " [MAZE WIDTH] [MAZE HEIGHT] [RENDER WIDTH] [optional RENDER HEIGHT]"
					<< std::endl;

	} else {

		// Pointers to maze, render, builder and solver objects
		Maze * m;
		Render * r;
		HashBuilder * b;
		Wallf * s;

		// initialize maze and render dimensions from command line arguments
		Nat m_wid, m_hei;
		Nat r_wid, r_hei;

		try {

			m_wid = static_cast<Nat> ( std::stoi( argv[1] ) );
			m_hei = static_cast<Nat> ( std::stoi( argv[2] ) );

			// create maze object
			m = new Maze { m_wid, m_hei };

			r_wid = static_cast<Nat> ( std::stoi( argv[3] ) );

			if( argc > 4 ){

				r_hei = static_cast<Nat> ( std::stoi( argv[4] ) );

				// create render object with default constructor
				r = new Render { m, r_wid, r_hei };

			} else {

				// create render object with deductive constructor
				r = new Render { m, r_wid };

			}

		} catch ( std::invalid_argument & e ) {

			std::cout << "An error occurred while trying to get dimensions!" << std::endl;

			std::cout 	<< "Try " << argv[0]
					<< " [MAZE WIDTH] [MAZE HEIGHT] [RENDER WIDTH] [optional RENDER HEIGHT]"
					<< std::endl;

			return EXIT_FAILURE;

		}

		// create builder and solver objects
		b = new HashBuilder { m, r };
		s = new Wallf { m, r };

		// build and solve the maze
		while( not b->is_built() )
			b->build_step();

		s->solve_maze();

	}

	return EXIT_SUCCESS;
	
}