#include <iostream>

#include "maze.h"

int main( int argc, char* argv[] ){

	Maze m{5, 10}, n{10, 20};

	std::cout << m << std::endl;
	std::cout << std::endl;
	std::cout << n << std::endl;

	return 0;
	
}