#include <iostream>

#include "maze.h"

int main( int argc, char* argv[] ){

	Maze m{3, 5}, n{5, 10};

	std::cout << m << std::endl;
	std::cout << std::endl;

	m.knockDown(1, 1, m.UpWall);
	m.knockDown(1, 1, m.BottomWall);

	std::cout << m << std::endl;
	std::cout << std::endl;
	std::cout << n << std::endl;
	std::cout << std::endl;

	try {
		m.knockDown( 10, 2, m.UpWall);
	} catch( std::invalid_argument & e ){
		std::cout << e.what() << std::endl;
	}

	try {
		m.knockDown( 0, 2, m.Untested);
	} catch( std::invalid_argument & e ){
		std::cout << e.what() << std::endl;
	}

	return 0;
	
}