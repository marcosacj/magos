#include <iostream>

#include "maze.h"

// Constructor
Maze::Maze( const Nat & w , const Nat & h ){

	std::cout << "\nConstructing maze..." << std::endl;

	width = w;
	height = h;

	board = new Cell[ width*height ];

	std::fill( board, board + width*height, States::Untested | Walls::Up | Walls::Right | Walls::Bottom | Walls::Left );

}

// Destructor
Maze::~Maze(){
	std::cout << "\nDestroying maze..." << std::endl;
	delete board;
}

void Maze::knock_down( const Coord & column, const Coord & line, const Wall & targetWall ){

	// check if coordinates are inside the board
	if( column >= width or column < 0 or line >= height or line < 0 ){
		throw std::invalid_argument("Coordinates should be inside the board!");
	}

	// check if target wall is correnct and knocks down wall of corresponing neighboor cell
	switch( targetWall ){

		case Walls::Up:
			if( line != 0 and line != width )
				knock_down( column, line - 1, Walls::Bottom );
			break;

		case Walls::Right:
			break;

		case Walls::Bottom:
			if( line != 0 and line != width )
				knock_down( column, line - 1, Walls::Up );
			break;

		case Walls::Left:
			break;

		default:
			throw std::invalid_argument("Target Wall should correspond to the predefined ones!");

	}

	// knocks down wall of target cell
	board[ to_index(column,line) ] &= ~targetWall;

}

void Maze::set_state( const Coord & column, const Coord & line, const State & state ){

	// todo

}