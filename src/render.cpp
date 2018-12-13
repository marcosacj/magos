#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "common.h"
#include "maze.h"
#include "canvas.h"
#include "render.h"

Render::Render( const Maze * maze, const Nat & width, const Nat & height ){

	std::cout << "Constructing Render..." << std::endl;

	ptr_maze = maze;

	border_wid = width  * 0.02;
	border_hei = height * 0.02;

	cell_width  = (width  - 2*border_wid) / ptr_maze->get_wid();
	cell_height = (height - 2*border_hei) / ptr_maze->get_hei();

	// calculate gap and update border size
	border_wid = ( width  - ptr_maze->get_wid() * cell_width  ) / 2;
	border_hei = ( height - ptr_maze->get_hei() * cell_height ) / 2;

	img = new Canvas{ width, height };

	img->clear( LIGHT_GREY );

}

Render::Render( const Maze * maze, const Nat & width ){

	std::cout << "Constructing Render..." << std::endl;

	Nat height{ width * maze->get_hei() / maze->get_wid() };

	ptr_maze = maze;

	border_wid = width  * 0.02;
	border_hei = height * 0.02;

	cell_width  = (width  - 2*border_wid) / ptr_maze->get_wid();
	cell_height = (height - 2*border_hei) / ptr_maze->get_hei();

	// calculate gap and update border size
	border_wid = ( width  - ptr_maze->get_wid() * cell_width  ) / 2;
	border_hei = ( height - ptr_maze->get_hei() * cell_height ) / 2;

	img = new Canvas{ width, height };

	img->clear( LIGHT_GREY );

}

Render::~Render( void ){

	std::cout << "Destroying Render..." << std::endl;

	delete img;
	
}

void Render::draw_cell( const Coord & column, const Coord & line ){

	// coordinates of start pixel in image
	Coord start_column{ column * cell_width  + border_wid };
	Coord start_line  { line   * cell_height + border_hei };

	// adjustable percetual of border inside cell relative to colored box of state
	float box_percentual { 0.30 };

	// dimensions of borders between wall and colored box
	Nat inside_border_wid { static_cast<Nat>( cell_width  * box_percentual ) };
	Nat inside_border_hei { static_cast<Nat>( cell_height * box_percentual ) };

	// coordinates of colored box of state information
	Coord box_column{ static_cast<Coord>( start_column + inside_border_wid ) };
	Coord box_line  { static_cast<Coord>( start_line   + inside_border_hei ) };

	// dimensions of colored box
	Nat box_width { static_cast<Nat>( cell_width  - 2*inside_border_wid ) };
	Nat box_height{ static_cast<Nat>( cell_height - 2*inside_border_hei ) };

	// draw bottom wall
	if( ptr_maze->hasWall( column, line, Maze::Walls::Bottom ) )
		img->hline( start_column , start_line + cell_height , cell_width , BLACK );

	// draw right wall
	if( ptr_maze->hasWall( column, line, Maze::Walls::Right ) )
		img->vline( start_column + cell_width , start_line , cell_height , BLACK );

	// draw top wall
	if( ptr_maze->hasWall( column, line, Maze::Walls::Top ) )
		img->hline( start_column , start_line , cell_width , BLACK );

	// draw left wall
	if( ptr_maze->hasWall( column, line, Maze::Walls::Left ) )
		img->vline( start_column , start_line , cell_height , BLACK );

	// draw Visited state
	if( ptr_maze->isState( column, line, Maze::States::Visited ) )
		img->box( box_column, box_line, box_width, box_height, LIGHT_BLUE );

	// draw path cells
	if( ptr_maze->isState( column, line, Maze::States::Path ) ){

		// draw current cell if it is path
		img->box( box_column, box_line, box_width, box_height, RED );

		// draw top neighbor path cell
		if( not ptr_maze->hasWall( column, line, Maze::Walls::Top ) )
			if( ptr_maze->isState( column, line - 1, Maze::States::Path ) )
				img->box( box_column , box_line - 2*inside_border_hei , box_width , 2*inside_border_hei , RED );

		// draw right neighbor path cell
		if( not ptr_maze->hasWall( column, line, Maze::Walls::Right ) )
			if( ptr_maze->isState( column + 1 , line , Maze::States::Path ) )
				img->box( box_column + box_width , box_line , 2*inside_border_wid , box_height , RED );

		// draw bottom neighbor path cell
		if( not ptr_maze->hasWall( column, line, Maze::Walls::Bottom ) )
			if( ptr_maze->isState( column , line + 1 , Maze::States::Path ) )
				img->box( box_column, box_line + box_height , box_width, 2*inside_border_hei, RED );

		// draw left neighbor path cell
		if( not ptr_maze->hasWall( column, line, Maze::Walls::Left ) )
			if( ptr_maze->isState( column - 1 , line , Maze::States::Path ) )
				img->box( box_column - 2*inside_border_wid , box_line , 2*inside_border_wid , box_height , RED );

	}

	// draw discarded cells
	if( ptr_maze->isState( column, line, Maze::States::Discarded ) ){

		// draw current cell if it is discarded
		img->box( box_column, box_line, box_width, box_height, YELLOW );

		// draw top neighbor path cell
		if( not ptr_maze->hasWall( column, line, Maze::Walls::Top ) )
			if( not ptr_maze->isState( column, line - 1, Maze::States::Untested ) )
				img->box( box_column , box_line - 2*inside_border_hei , box_width , 2*inside_border_hei , YELLOW );

		// draw right neighbor path cell
		if( not ptr_maze->hasWall( column, line, Maze::Walls::Right ) )
			if( not ptr_maze->isState( column + 1 , line , Maze::States::Untested ) )
				img->box( box_column + box_width , box_line , 2*inside_border_wid , box_height , YELLOW );

		// draw bottom neighbor path cell
		if( not ptr_maze->hasWall( column, line, Maze::Walls::Bottom ) )
			if( not ptr_maze->isState( column , line + 1 , Maze::States::Untested ) )
				img->box( box_column, box_line + box_height , box_width, 2*inside_border_hei, YELLOW );

		// draw left neighbor path cell
		if( not ptr_maze->hasWall( column, line, Maze::Walls::Left ) )
			if( not ptr_maze->isState( column - 1 , line , Maze::States::Untested ) )
				img->box( box_column - 2*inside_border_wid , box_line , 2*inside_border_wid , box_height , YELLOW );

	}


}

void Render::draw_maze( void ){

	for ( Coord column{0u} ; column < ptr_maze->get_wid() ; column++ ){
		for ( Coord line{0u} ; line < ptr_maze->get_hei() ; line++ ){
			draw_cell( column, line );
		}
	}

}

void Render::draw_image( const Str & path ){

	img->clear( LIGHT_GREY );

	// std::cout << "Drawing..." << std::endl;
	draw_maze();

	stbi_write_png_compression_level = 0;

	// std::cout << "Saving..." << std::endl;
	stbi_write_png( path.c_str(), img->width(), img->height(), 3, img->buffer(), img->width()*3 );

}