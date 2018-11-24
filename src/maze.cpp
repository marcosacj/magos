#include <iostream>

#include "maze.h"

// Constructor
Maze::Maze( const Nat & w , const Nat & h ){

	// std::cout << "\nConstructing maze..." << std::endl;

	width = w;
	height = h;

	board = new Cell[ width*height ];

	std::fill( board, board + width*height, States::Untested | Walls::Up | Walls::Right | Walls::Bottom | Walls::Left );

}

// Destructor
Maze::~Maze(){
	// std::cout << "\nDestroying maze..." << std::endl;
	delete board;
}

void Maze::knock_down( const Coord & column, const Coord & line, const Wall & targetWall ){

	// check if coordinates are inside the board
	if( column >= width or column < 0 or line >= height or line < 0 ){
		throw std::invalid_argument("Coordinates should be inside the board!");
	}

	// check if target wall is correct and 
	// knocks down wall of corresponing neighboor cell
	switch( targetWall ){

		case Walls::Up:
			if( line == 0 )
				throw std::invalid_argument("Can't knock down top border wall!");
			else
				board[ to_index(column, line - 1) ] &= ~Walls::Bottom;

			break;

		case Walls::Right:
			if( column == width-1 )
				throw std::invalid_argument("Can't knock down right border wall!");
			else
				board[ to_index(column + 1, line) ] &= ~Walls::Left;

			break;

		case Walls::Bottom:
			if( line == height-1 )
				throw std::invalid_argument("Can't knock down bottom border wall!");
			else
				board[ to_index(column, line + 1) ] &= ~Walls::Up;

			break;

		case Walls::Left:
			if( column == 0 )
				throw std::invalid_argument("Can't knock down left border wall!");
			else
				board[ to_index(column - 1, line) ] &= ~Walls::Right;
			break;

		default:
			throw std::invalid_argument("Target Wall not valid!");

	}

	// knocks down target wall of target cell
	board[ to_index(column, line) ] &= ~targetWall;

}

void Maze::set_state( const Coord & column, const Coord & line, const State & state ){

	// todo

}