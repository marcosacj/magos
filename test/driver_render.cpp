#include <iostream>

#include "render.h"

int main( int argc, char* argv[] ){

	if( argc < 4 ){

		std::cout << "Invalid arguments!" << std::endl;

		std::cout 	<< "Try " << argv[0] 
					<< " [MAZE WIDTH] [MAZE HEIGHT] [RENDER WIDTH] [optional RENDER HEIGHT]"
					<< std::endl;

	} else {

		// Pointers to maze and render objects
		Maze * m;
		Render * r;

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

		std::cout << *r << std::endl;

		r->draw_image( "./data/img-clean.png" );

		m->knock_down( m_wid * 0.5 , m_hei * 0.3 , Maze::Walls::Top );
		m->knock_down( m_wid * 0.2 , m_hei * 0.5 , Maze::Walls::Right );
		m->knock_down( m_wid * 0.3 , m_hei * 0.4 , Maze::Walls::Right );
		m->knock_down( m_wid * 0.9 , m_hei * 0.9 , Maze::Walls::Left );

		r->draw_image( "./data/img-knock.png" );

		m->set_state(  m_wid * 0.1 , m_hei * 0.5 , Maze::States::Visited );
		m->set_state(  m_wid * 0.5 , m_hei * 0.9 , Maze::States::Path );
		m->set_state(  m_wid * 0.9 , m_hei * 0.4 , Maze::States::Discarded );

		r->draw_image( "./data/img-state.png" );

		std::cout << "Done!" << std::endl;

	}

	return 0;
	
}