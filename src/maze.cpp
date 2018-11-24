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