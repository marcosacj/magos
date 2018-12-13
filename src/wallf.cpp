#include <iostream>
#include <vector>
#include <algorithm> // std::shuffle
#include <random> // std::random_device, std::mt19937

#include "wallf.h"

Wallf::Wallf( Maze * param_m , Render * param_r ){

	std::cout << "Constructing Wall Follower solver..." << std::endl;

	// set pointers
	m = param_m;
	r = param_r;

	// set start and end positions
	start_point = 0;
	end_point = m->get_wid()*m->get_hei() - 1;

	// set current position
	position = start_point;

	// set current direction
	std::vector<direction_t> directions { Top, Right, Bottom, Left };
	std::shuffle( std::begin(directions), std::end(directions), std::mt19937{ std::random_device{}() } );
	
	direction = directions.front();

}

Wallf::~Wallf( void ){

	std::cout << "Destrpying Wall Follower solver..." << std::endl;

	if( m != nullptr ) delete m;
	if( r != nullptr ) delete r;

}

bool Wallf::is_solved( void ){

	return position == end_point;

}

void Wallf::solve_step( void ){

	// std::cout << "pos = " << position << " dir = " << direction << std::endl;

	// check if the right wall is standing
	if( m->hasWall( position, directions_v[ right_direction() ] ) ){

		// check if front wall is standing
		if( m->hasWall( position, directions_v[ direction ] ) ){

			// check if left wall is standing
			if( m->hasWall( position, directions_v[ left_direction() ] ) ){

				// case is END OF CORRIDOR
				// std::cout << "End of corridor" << std::endl;

				// action is TURN BACK
				turn_back();

			} else {

				// case is LEFT CORRIDOR
				// std::cout << "Left corridor" << std::endl;

				// action is TURN LEFT and GO AHEAD
				turn_left();
				go_ahead();

			}

		} else {

			// case is FRONT CORRIDOR
			// std::cout << "Front corridor" << std::endl;

			// action is GO AHEAD
			go_ahead();

		}

	} else {

		// case is RIGHT CORRIDOR
		// std::cout << "Right corridor" << std::endl;

		// action is TURN RIGHT and GO AHEAD
		turn_right();
		go_ahead();

	}

}

void Wallf::solve_maze( void ){

	// set initial position as path
	m->set_state( start_point, Maze::States::Path );

	r->draw_image( "./data/img.png" );
	// std::cin.ignore();

	while( not is_solved() ) {

		solve_step();
		r->draw_image( "./data/img.png" );

		// std::cin.ignore();
		
	}

}

void Wallf::go_ahead( void ){

	// get coordinates of current position
	Coord col { to_col( position ) };
	Coord lin { to_lin( position ) };

	// previous position
	index_t previous { position };

	switch( direction ) {

		case Top:
			position = to_index( col, lin - 1 );
			break;

		case Right:
			position = to_index( col + 1, lin );
			break;

		case Bottom:
			position = to_index( col, lin + 1 );
			break;

		case Left:
			position = to_index( col - 1, lin );
			break;

		default:
			throw std::runtime_error( "Something wrong with the current direction!" );

	}

	// std::cout << "new pos = " << position << std::endl;

	if( m->isState( position, Maze::States::Path ) )
		m->set_state( previous, Maze::States::Discarded );
	else
		m->set_state( position, Maze::States::Path );

}