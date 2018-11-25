#include <iostream>

#include "maze.h"
#include "render.h"

int main(){

	Maze m{5, 8};

	Render r{ & m, 800, 500 };

	std::cout << r << std::endl;

	r.save_image();

	return 0;
	
}