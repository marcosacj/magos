#include <iostream>

#include "maze.h"
#include "render.h"

int main(){

	Maze m{5, 8};

	Render r{ & m, 600, 700 };

	std::cout << r << std::endl;

	return 0;
	
}