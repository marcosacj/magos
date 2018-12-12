#include "magos.h"

// Magos::Magos( Maze * param_m, Render * param_r, HashBuilder * param_b, Solver * param_s ){
Magos::Magos( void ){

	std::cout << "Constructing Magos Game..." << std::endl;

	// m = param_m;
	// r = param_r;
	// b = param_b;
	// s = param_s;

}

Magos::~Magos( void ){

	std::cout << "Destroying Magos Game..." << std::endl;

	// delete m;
	// delete r;

}

void Magos::welcome( void ) const {

	// https://www.messletters.com/pt/big-text/

	std::cout << "##     ##    ###     ######    #######   ######      ######      ###    ##     ## ########" << std::endl;
	std::cout << "###   ###   ## ##   ##    ##  ##     ## ##    ##    ##    ##    ## ##   ###   ### ##      " << std::endl;
	std::cout << "#### ####  ##   ##  ##        ##     ## ##          ##         ##   ##  #### #### ##      " << std::endl;
	std::cout << "## ### ## ##     ## ##   #### ##     ##  ######     ##   #### ##     ## ## ### ## ######  " << std::endl;
	std::cout << "##     ## ######### ##    ##  ##     ##       ##    ##    ##  ######### ##     ## ##      " << std::endl;
	std::cout << "##     ## ##     ## ##    ##  ##     ## ##    ##    ##    ##  ##     ## ##     ## ##      " << std::endl;
	std::cout << "##     ## ##     ##  ######    #######   ######      ######   ##     ## ##     ## ########" << std::endl;

}


void Magos::initializer( int argc, char* argv[] ){

	game_state = STARTING;

	// check number of input arguments (mininum is 4)
	// [NAME OF PROGRAM] [MAZE WIDTH] [MAZE HEIGHT] [IMAGE WIDTH] [optional IMAGE HEIGHT]
	if( argc < 4 ){

		game_state = ERROR;

		std::cout << "Invalid game arguments!" << std::endl;

		std::cout 	<< "Try " << argv[0]
					<< " [MAZE WIDTH] [MAZE HEIGHT] [RENDER WIDTH] [optional RENDER HEIGHT]"
					<< std::endl;

	} else {

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

			// creare builder and solver objects
			b = new HashBuilder { m, r };
			s = new Solver { m, r };

		} catch ( std::invalid_argument & e ) {

			std::cout << "An error occurred while trying to get dimensions!" << std::endl;

			std::cout 	<< "Try " << argv[0]
					<< " [MAZE WIDTH] [MAZE HEIGHT] [RENDER WIDTH] [optional RENDER HEIGHT]"
					<< std::endl;

		}

		game_state = BUILDING;

	}

}

void Magos::process_events( void ){

	// std::cout << "Processing events..." << std::endl;

}

void Magos::update( void ){

	switch( game_state ){

		case STARTING:
			break;
			
		case BUILDING:
			std::cout << "building..." << std::endl;
			b->build_step();
			if( b->is_built() )
				game_state = SOLVING;
			break;
			
		case SOLVING:
			std::cout << "solving..." << std::endl;
			s->solve_step();
			if( s->is_solved() )
				game_state = OVER;
			break;
			
		case OVER:
			break;
			
		case ERROR:
			break;

		default:
			throw std::runtime_error( "An error occurred during game execution!" ) ;
	}

}

void Magos::renderize( void ){

	// std::cout << "Renderizing..." << std::endl;

}

bool Magos::game_over( void ){

	// this code is just for test purpose...
	// srand(time(0));
	// if( rand() % 2 == 0 )
	// 	return true;
	// else
	// 	return false;

	return game_state == OVER;

}