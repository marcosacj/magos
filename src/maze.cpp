#include <iostream>

#include "maze.h"

Maze::Maze( const Nat & w , const Nat & h ){

	std::cout << "\nConstructing maze..." << std::endl;

	width = w;
	height = h;

	board = new Cell[ width*height ];

	std::fill( board, board + width*height, Untested | UpWall | RightWall | BottomWall | LeftWall );

}

Maze::~Maze(){
	std::cout << "\nDestroying maze..." << std::endl;
	delete board;
}

void Maze::knockDown( const Nat & column, const Nat & line, const Nat & targetWall ){

	if( column >= width or column < 0 or line >= height or line < 0 ){
		throw std::invalid_argument("Coordinates should be inside the board!");
	}

	// if targetWall is none of defined
	if( targetWall != UpWall and targetWall != RightWall and targetWall != BottomWall and targetWall != LeftWall ){
		throw std::invalid_argument("Target Wall should correspond to the predefined ones!");
	}

	board[ to_index(column,line) ] &= ~targetWall;

	// todo: knockDown the neighboor cell wall

}