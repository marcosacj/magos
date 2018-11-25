#include <iostream>

#include "maze.h"
#include "render.h"

int main(){

	Maze m{10, 6};

	m.knock_down(1, 1, Maze::Walls::Up);
	m.knock_down(2, 2, Maze::Walls::Right);
	m.knock_down(0, 3, Maze::Walls::Right);
	m.knock_down(1, 5, Maze::Walls::Left);

	m.set_state( 6, 0, Maze::States::Visited );
	m.set_state( 7, 2, Maze::States::Path );
	m.set_state( 8, 4, Maze::States::Discarded );

	Render r{ & m, 1000, 600 };

	std::cout << r << std::endl;

	std::cout << "Drawing..." << std::endl;
	r.draw_maze();

	std::cout << "Saving..." << std::endl;
	r.save_image();
	r.save_image( "./data/imgage.png" );

	std::cout << "Done!" << std::endl;

	return 0;
	
}