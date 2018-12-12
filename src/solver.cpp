#include <iostream>
#include <vector>
#include <iterator> // std::ostream_iterator
#include <algorithm> // std::shuffle

#include <math.h> // floor

#include "render.h"
#include "solver.h"

Solver::Solver( Maze * param_m, Render * param_r ){

	m = param_m;

	r = param_r;

	start_point = 0;

	end_point = m->get_wid()*m->get_hei() - 1;

	path.push( start_point );

}

void Solver::solve_step( void ){

	// check if current cell is the end point
	if( path.top() == end_point ){

		// if yes, the maze is solved
		std::cout << "end point found" << std::endl;
		return;

	} else {

		// check the possible directions to go
		std::vector<index_t> directions { check_directions( path.top() ) };

		// if there is at least one direction, choose one and go ahead
		if( directions.size() > 0 ){

			// shuffle direction to grant randomness to the choice
			std::shuffle( std::begin(directions), std::end(directions), std::mt19937{ std::random_device{}() } );

			// get column and line of current cell
			Coord col { to_col( path.top() ) };
			Coord lin { to_lin( path.top() ) };
			
			// depending on the direction
			switch( directions.front() ) {

				case Directions::Top:
					path.push( to_index( col, lin - 1 ) );
					break;

				case Directions::Right:
					path.push( to_index( col + 1, lin) );
					break;

				case Directions::Bottom:
					path.push( to_index( col, lin + 1 ) );
					break;

				case Directions::Left:
					path.push( to_index( col - 1, lin ) );
					break;

				default:
					throw std::runtime_error( "The direction choosen is invalid!" );

			}

			// mark current new position as visited
			m->set_state( to_col( path.top() ), to_lin( path.top() ), Maze::States::Path );

		} else {

			// if there is no direction

			// mark current cells as discarded
			m->set_state( to_col( path.top() ), to_lin( path.top() ), Maze::States::Discarded );

			// go back along the path poping the stack
			path.pop();

		}

	}

}

std::vector<Nat> Solver::check_directions( const index_t & index ) const {

	std::vector<Nat> directions;

	// get column and line of current cell
	Coord col { to_col( path.top() ) };
	Coord lin { to_lin( path.top() ) };

	if( ( not m->hasWall( col, lin, Maze::Walls::Top ) ) and m->isState( col, lin - 1, Maze::States::Untested ) ){
		directions.push_back( Directions::Top );
	}

	if( ( not m->hasWall( col, lin, Maze::Walls::Right ) ) and m->isState( col + 1, lin , Maze::States::Untested ) ){
		directions.push_back( Directions::Right );
	}

	if( ( not m->hasWall( col, lin, Maze::Walls::Bottom ) ) and m->isState( col, lin + 1, Maze::States::Untested ) ){
		directions.push_back( Directions::Bottom );
	}

	if( ( not m->hasWall( col, lin, Maze::Walls::Left ) ) and m->isState( col - 1, lin , Maze::States::Untested ) ){
		directions.push_back( Directions::Left );
	}

	return directions;

}

void Solver::solve_maze( void ){

	std::cout << "Solving maze..." << std::endl;

	// counter to file names
	Nat img_idx{ 0 };

	std::string solve_path { "./data/solving_" };

	// mark initial posision as path
	m->set_state( to_col( path.top() ), to_lin( path.top() ), Maze::States::Path );

	// draw initial version of maze
	r->draw_image( solve_path + std::to_string( img_idx++ ) + ".png" );

	while( not is_solved() ){

		// advance one step in solutio search
		solve_step();

		// draw currente version of maze
		r->draw_image( solve_path + std::to_string( img_idx++ ) + ".png" );

	}

	std::cout << "Maze is solved..." << std::endl;

}

bool Solver::is_solved( void ){

	return path.top() == end_point;

}