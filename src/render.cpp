#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "maze.h"
#include "canvas.h"
#include "render.h"

typedef std::string Str;

Render::Render( const Maze * maze, const Nat & width, const Nat & height ){

	ptr_maze = maze;

	image_width = width;
	image_height = height;

	cell_width = image_width / ptr_maze->get_width();
	cell_height = image_height / ptr_maze->get_height();

	img = new Canvas{ image_width, image_height };

	img->clear( LIGHT_GREY );

}

Render::~Render(){
	delete img;
}

void Render::draw_cell( const Coord & column, const Coord & line ){

	// todo

}

void Render::save_image() const {

	stbi_write_png_compression_level = 0;

	stbi_write_png( "./data/img.png", image_width, image_height, 3, img->buffer(), image_width*3 );

}