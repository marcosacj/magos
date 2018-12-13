#include <iostream>

#include "maze.h"

// Constructor
Maze::Maze( const Nat & w , const Nat & h ){

	std::cout << "Constructing Maze..." << std::endl;

	width = w;
	height = h;

	matrix = new Cell[ width*height ];

	std::fill( matrix, matrix + width*height, States::Untested | Walls::Top | Walls::Right | Walls::Bottom | Walls::Left );

}

// Destructor
Maze::~Maze( void ){

	std::cout << "Destroying Maze..." << std::endl;

	if( matrix != nullptr ) delete matrix;

}

void Maze::knock_down( const Coord & column, const Coord & line, const Wall & targetWall ){

	// check if coordinates are inside the matrix
	if( not valid_coord( column, line ) ){
		throw std::invalid_argument("Coordinates should be inside the matrix!");
	}

	// check if target wall is correct and 
	// knocks down wall of corresponing neighboor cell
	switch( targetWall ){

		case Walls::Top:
			if( line == 0 )
				throw std::invalid_argument("Can't knock down top border wall!");
			else
				matrix[ to_index(column, line - 1) ] &= ~Walls::Bottom;

			break;

		case Walls::Right:
			if( column == width-1 )
				throw std::invalid_argument("Can't knock down right border wall!");
			else
				matrix[ to_index(column + 1, line) ] &= ~Walls::Left;

			break;

		case Walls::Bottom:
			if( line == height-1 )
				throw std::invalid_argument("Can't knock down bottom border wall!");
			else
				matrix[ to_index(column, line + 1) ] &= ~Walls::Top;

			break;

		case Walls::Left:
			if( column == 0 )
				throw std::invalid_argument("Can't knock down left border wall!");
			else
				matrix[ to_index(column - 1, line) ] &= ~Walls::Right;
			break;

		default:
			throw std::invalid_argument("Target Wall not valid!");

	}

	// knocks down target wall of target cell
	matrix[ to_index(column, line) ] &= ~targetWall;

}

void Maze::set_state( const Coord & column, const Coord & line, const State & targetState ){

	// check if coordinates are inside the matrix
	if( not valid_coord( column, line ) ){
		throw std::invalid_argument("Coordinates should be inside the matrix!");
	}

	// reset state bits
	Cell reseter{ 15 }; // equivalent to 00001111
	matrix[ to_index(column, line) ] &= reseter;

	// set new state bits
	switch( targetState ){

		case States::Untested:
		case States::Visited:
		case States::Path:
		case States::Discarded:
			matrix[ to_index(column, line) ] |= targetState;
			break;

		default:
			throw std::invalid_argument("Target State not valid!");
	}

}

void Maze::set_state( const index_t & index, const State & targetState ){

	set_state( to_col( index ), to_lin( index ), targetState );

}

bool Maze::valid_coord( const Coord & column, const Coord & line ) const {

	if( column >= width or column < 0 or line >= height or line < 0 )
		return false;
	else
		return true;

}

Nat Maze::to_index( const Coord & column, const Coord & line ) const {

	if( valid_coord( column, line ) ){
		return width*line + column;
	} else {
		throw std::invalid_argument("Coordinates should be inside the matrix!");
	}

}

bool Maze::hasWall( const Coord & column, const Coord & line, const Wall & targetWall ) const {

	// yes, it is correct to assign a wall to a cell type!
	// this assignment is used for binary comparison to retrieve the information of the wall
	Cell targetW{ targetWall };

	if( ( matrix[ to_index( column, line ) ] & targetW ) == targetW ){
		return true;
	} else {
		return false;
	}

}

bool Maze::isState( const Coord & column, const Coord & line, const State & targetState ) const {

	// yes, it is correct to assign a state to a cell type!
	// this assignment is used for binary comparison to retrieve the information of the state
	Cell targetS{ targetState };

	if( ( matrix[ to_index( column, line ) ] & targetS ) == targetS ){
		return true;
	} else {
		return false;
	}

}