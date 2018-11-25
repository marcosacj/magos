#include <iostream>

#include "maze.h"
#include "render.h"

int main(){

	Maze m{10, 6};

	m.knock_down(1, 1, Maze::Walls::Up);
	m.knock_down(2, 2, Maze::Walls::Right);
	m.knock_down(0, 3, Maze::Walls::Right);
	m.knock_down(1, 5, Maze::Walls::Left);

	Render r{ & m, 1000, 600 };

	std::cout << r << std::endl;

	std::cout << "Drawing..." << std::endl;
	r.draw_maze();

	std::cout << "Saving..." << std::endl;
	r.save_image( "./data/image.png" );

	std::cout << "Done!" << std::endl;

	return 0;
	
}