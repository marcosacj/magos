#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "common.h"
#include "maze.h"
#include "canvas.h"
#include "render.h"

Render::Render( const Maze * maze, const Nat & width, const Nat & height ){

	ptr_maze = maze;

	border_wid = width  * 0.02;
	border_hei = height * 0.02;

	cell_width  = (width  - 2*border_wid) / ptr_maze->get_width ();
	cell_height = (height - 2*border_hei) / ptr_maze->get_height();

	// calculate gap and update border size
	border_wid = ( width  - ptr_maze->get_width () * cell_width  ) / 2;
	border_hei = ( height - ptr_maze->get_height() * cell_height ) / 2;

	img = new Canvas{ width, height };

	img->clear( LIGHT_GREY );

}

Render::~Render(){
	delete img;
}

void Render::draw_cell( const Coord & column, const Coord & line ){

	// coordinates of start pixel in image
	Coord start_column{ column * cell_width  + border_wid };
	Coord start_line  { line   * cell_height + border_hei };

	// top wall
	if( ptr_maze->hasWall( column, line, Maze::Walls::Top ) )
		img->hline( start_column , start_line , cell_width , BLACK );

	// left wall
	if( ptr_maze->hasWall( column, line, Maze::Walls::Left ) )
		img->vline( start_column , start_line , cell_height , BLACK );

	// bottom wall
	if( ptr_maze->hasWall( column, line, Maze::Walls::Bottom ) )
		img->hline( start_column , start_line + cell_height , cell_width , BLACK );

	// right wall
	if( ptr_maze->hasWall( column, line, Maze::Walls::Right ) )
		img->vline( start_column + cell_width , start_line , cell_height , BLACK );

	// coordinates of colored box of state information
	Coord box_column{ start_column + cell_width /4 };
	Coord box_line  { start_line   + cell_height/4 };

	// dimensions of colored box
	Nat box_width { cell_width /2 };
	Nat box_height{ cell_height/2 };

	if( ptr_maze->isState( column, line, Maze::States::Visited ) ) // Visited
		img->box( box_column, box_line, box_width, box_height, LIGHT_BLUE );

	if( ptr_maze->isState( column, line, Maze::States::Path ) ) // Path
		img->box( box_column, box_line, box_width, box_height, RED );

	if( ptr_maze->isState( column, line, Maze::States::Discarded ) ) // Discarded
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
	stbi_write_png( path.c_str(), img->width(), img->height(), 3, img->buffer(), img->width()*3 );

}