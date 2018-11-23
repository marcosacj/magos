#include <iostream>

#include "maze.h"

Maze::Maze( const Nat & w , const Nat & h ){

	std::cout << "Constructing maze..." << std::endl;

	width = w;
	height = h;

	board = new Nat[ width*height ];

	std::fill( board, board + width*height, Unvisited );

}

Maze::~Maze(){
	std::cout << "Destroying maze..." << std::endl;
	delete board;
}