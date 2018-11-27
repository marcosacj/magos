#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "common.h"
#include "maze.h"
#include "canvas.h"
#include "render.h"

Render::Render( const Maze * maze, const Nat & width, const Nat & height ){

	ptr_maze = maze;

	image_width = width;
	image_height = height;

	border_size = std::min( image_width, image_height ) * 0.05;

	cell_width = (image_width - border_size) / ptr_maze->get_width();
	cell_height = (image_height - border_size) / ptr_maze->get_height();

	img = new Canvas{ image_width, image_height };

	img->clear( LIGHT_GREY );

}

Render::~Render(){
	delete img;
}

void Render::draw_cell( const Coord & column, const Coord & line ){

	// Cell to be drawn
	Cell cell{ ptr_maze->get_cell( column, line ) };

	// coordinates of start pixel in image
	Coord start_column{ column*cell_width + border_size/2 };
	Coord start_line{ line*cell_height + border_size/2 };

	// top wall
	if( cell[7] )
		img->hline( start_column , start_line , cell_width , BLACK );

	// left wall
	if( cell[4] )
		img->vline( start_column , start_line , cell_height , BLACK );

	// bottom wall
	if( cell[5] )
		img->hline( start_column , start_line + cell_height , cell_width , BLACK );

	// right wall
	if( cell[6] )
		img->vline( start_column + cell_width , start_line , cell_height , BLACK );

	// coordinates of colored box of state information
	Coord box_column{ start_column + cell_width/4 };
	Coord box_line{ start_line + cell_height/4 };

	// dimensions of colored box
	Nat box_width{ cell_width/2 };
	Nat box_height{ cell_height/2 };

	if( cell[2] ) // Visited
		img->box( box_column, box_line, box_width, box_height, LIGHT_BLUE );

	if( cell[1] ) // Path
		img->box( box_column, box_line, box_width, box_height, RED );

	if( cell[0] ) // Discarded
		img->box( box_column, box_line, box_width, box_height, YELLOW );

}

void Render::draw_maze(){

	for ( Coord column{0u} ; column < ptr_maze->get_width() ; column++ ){
		for ( Coord line{0u} ; line < ptr_maze->get_height() ; line++ ){
			draw_cell( column, line );
		}
	}

}

void Render::draw_image( const Str & path ){

	std::cout << "Drawing..." << std::endl;
	draw_maze();

	stbi_write_png_compression_level = 0;

	std::cout << "Saving..." << std::endl;
	stbi_write_png( path.c_str(), image_width, image_height, 3, img->buffer(), image_width*3 );

}