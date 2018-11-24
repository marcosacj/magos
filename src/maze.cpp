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

void Maze::knock_down( const Nat & column, const Nat & line, const Nat & targetWall ){

	if( column >= width or column < 0 or line >= height or line < 0 ){
		throw std::invalid_argument("Coordinates should be inside the board!");
	}

	if( targetWall != Walls::Up and 
		targetWall != Walls::Right and 
		targetWall != Walls::Bottom and 
		targetWall != Walls::Left ){
		throw std::invalid_argument("Target Wall should correspond to the predefined ones!");
	}

	board[ to_index(column,line) ] &= ~targetWall;

	// todo: knockDown the neighboor cell wall

}