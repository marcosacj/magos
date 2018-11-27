#include <iostream>

#include "maze.h"
#include "render.h"

int main(){

	Maze m{10, 6};
	// Maze m{50, 30};

	m.knock_down(1, 1, Maze::Walls::Up);
	m.knock_down(2, 2, Maze::Walls::Right);
	m.knock_down(0, 3, Maze::Walls::Right);
	m.knock_down(1, 5, Maze::Walls::Left);

	m.set_state( 6, 0, Maze::States::Visited );
	m.set_state( 7, 2, Maze::States::Path );
	m.set_state( 8, 4, Maze::States::Discarded );

	Nat scale{100};
	// Nat scale{20};
	Render r{ & m, m.get_width() * scale, m.get_height() * scale };

	std::cout << r << std::endl;

	r.draw_image();
	// r.save_image( "./data/image.png" );

	std::cout << "Done!" << std::endl;

	return 0;
	
}