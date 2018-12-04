#include <iostream>

#include "builder.h"

int main(){

	Maze m{5, 3};

	HashBuilder builder{ & m };

	builder.build_maze();

	std::cout << m << std::endl;

	return 0;
	
}