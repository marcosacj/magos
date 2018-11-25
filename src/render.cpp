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

	cell_width = (image_width - border_size) / ptr_maze->get_width();
	cell_height = (image_height - border_size) / ptr_maze->get_height();

	img = new Canvas{ image_width, image_height };

	img->clear( LIGHT_GREY );

}

Render::~Render(){
	delete img;
}

void Render::draw_cell( const Coord & column, const Coord & line ){

	// Type of a Cell in the Maze
	typedef std::bitset<8> Cell;

	// Cell to be drawn
	Cell cell{ ptr_maze->get_cell( column, line ) };

	// Coordinates of start pixel in image
	Coord start_column{ column*cell_width };
	Coord start_line{ line*cell_height };

	// top wall
	if( cell[7] )
		img->hline( start_column + border_size/2 , start_line + border_size/2 , cell_width , BLACK );

	// left wall
	if( cell[4] )
		img->vline( start_column + border_size/2 , start_line + border_size/2 , cell_height , BLACK );

	// bottom wall
	if( cell[5] )
		img->hline( start_column + border_size/2 , start_line + border_size/2 + cell_height , cell_width , BLACK );

	// right wall
	if( cell[6] )
		img->vline( start_column + border_size/2 + cell_width , start_line + border_size/2 , cell_height , BLACK );

}

void Render::draw_maze(){

	for ( Coord column{0u} ; column < ptr_maze->get_width() ; column++ ){
		for ( Coord line{0u} ; line < ptr_maze->get_height() ; line++ ){
			draw_cell( column, line );
		}
	}

}

void Render::save_image() const {

	stbi_write_png_compression_level = 0;

	stbi_write_png( "./data/img.png", image_width, image_height, 3, img->buffer(), image_width*3 );

}