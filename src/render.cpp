#include <iostream>

#include "render.h"
#include "maze.h"
#include "canvas.h"

Render::Render( const Maze * maze, const Nat & width, const Nat & height ){

	ptr_maze = maze;

	image_width = width;
	image_height = height;

	cell_width = image_width / ptr_maze->get_width();
	cell_height = image_height / ptr_maze->get_height();

}