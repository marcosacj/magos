#include <iostream>

#include "maze.h"
#include "render.h"

int main(){

	Maze m{10, 6};

	Render r{ & m, 800, 500 };

	std::cout << r << std::endl;

	r.draw_maze();

	r.save_image();

	return 0;
	
}