#include <iostream>

#include "maze.h"

int main( int argc, char* argv[] ){

	Maze m{3, 5}, n{5, 10};

	std::cout << m << std::endl;
	std::cout << std::endl;
	// std::cout << n << std::endl;

	m.knockDown(1, 1, m.UpWall);
	m.knockDown(1, 1, m.BottomWall);

	std::cout << m << std::endl;

	return 0;
	
}