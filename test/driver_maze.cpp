#include <iostream>

#include "maze.h"

typedef std::size_t Nat;

int main( int argc, char* argv[] ){

	if( argc < 3 ){

		std::cout << "Invalid arguments!" << std::endl;
		std::cout << "Try " << argv[0] << " [MAZE WIDTH] [MAZE HEIGHT]" << std::endl;

	} else {

		// initialize maze dimensions from command line arguments
		Nat m_wid;
		Nat m_hei;

		try {

			m_wid = static_cast<Nat> ( std::stoi( argv[1] ) );
			m_hei = static_cast<Nat> ( std::stoi( argv[2] ) );

		} catch ( std::invalid_argument & e ) {

			std::cout << "An error occurred while trying to get dimensions!" << std::endl;
			std::cout << "Try " << argv[0] << " [MAZE WIDTH] [MAZE HEIGHT]" << std::endl;

			return EXIT_FAILURE;

		}

		Maze m { m_wid, m_hei };

		std::cout << m << std::endl << std::endl;

		m.knock_down(0, 1, Maze::Walls::Top);
		m.knock_down(0, 3, Maze::Walls::Bottom);
		m.knock_down(2, 0, Maze::Walls::Right);
		m.knock_down(2, 3, Maze::Walls::Left);

		m.set_state(m_wid-1, m_hei-1, Maze::States::Visited);
		m.set_state(m_wid-2, m_hei-2, Maze::States::Path);

		std::cout << m << std::endl << std::endl;

		// knock down border walls
		try {
			m.knock_down(1, 0, Maze::Walls::Top);
		} catch( std::invalid_argument & e) {
			std::cout << e.what() << std::endl;
		}

		try {
			m.knock_down(1, m_hei-1, Maze::Walls::Bottom);
		} catch( std::invalid_argument & e) {
			std::cout << e.what() << std::endl;
		}

		try {
			m.knock_down(m_wid-1, 3, Maze::Walls::Right);
		} catch( std::invalid_argument & e) {
			std::cout << e.what() << std::endl;
		}

		try {
			m.knock_down(0, 3, Maze::Walls::Left);
		} catch( std::invalid_argument & e) {
			std::cout << e.what() << std::endl;
		}

		// knock down outside matrix
		try {
			m.knock_down( 10, 2, Maze::Walls::Top);
		} catch( std::invalid_argument & e ){
			std::cout << e.what() << std::endl;
		}

		// knock down invalid wall
		try {
			m.knock_down( 0, 2, Maze::States::Untested);
		} catch( std::invalid_argument & e ){
			std::cout << e.what() << std::endl;
		}

		// set states
		try {
			m.set_state( 0, 2, Maze::Walls::Top);
		} catch( std::invalid_argument & e ){
			std::cout << e.what() << std::endl;
		}

	}

	return EXIT_SUCCESS;
	
}