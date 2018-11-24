#include <iostream>

#include "maze.h"

int main( int argc, char* argv[] ){

	Maze m{3, 5}, n{5, 10};

	std::cout << m << std::endl;
	std::cout << std::endl;

	m.knock_down(1, 1, Maze::Walls::Up);
	m.knock_down(1, 1, Maze::Walls::Bottom);

	std::cout << m << std::endl;
	std::cout << std::endl;

	std::cout << n << std::endl;
	std::cout << std::endl;

	try {
		m.knock_down( 10, 2, Maze::Walls::Up);
	} catch( std::invalid_argument & e ){
		std::cout << e.what() << std::endl;
	}

	try {
		m.knock_down( 0, 2, Maze::States::Untested);
	} catch( std::invalid_argument & e ){
		std::cout << e.what() << std::endl;
	}

	return 0;
	
}