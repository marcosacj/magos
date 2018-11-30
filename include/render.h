#ifndef RENDER_H
#define RENDER_H

#include <iomanip>

#include "common.h"
#include "maze.h"
#include "canvas.h"

using namespace canvas;

/// Receives a Maze object and make a png file.
class Render {

private:

	Nat cell_width;  //!< Width of each cell on image, in pixels.
	Nat cell_height; //!< Height of each cell on image, in pixels.

	Nat border_wid; //!< Lenght of the horizontal border on image, in pixels.
	Nat border_hei; //!< Lenght of the vertical border on image, in pixels.

	/// Pointer to target maze.
	const Maze * ptr_maze{nullptr};

	/// Pointer to a Canvas object which represents the image.
	Canvas * img{nullptr};

	/// Draws a single cell on the image Canvas object.
	void draw_cell( const Coord & column, const Coord & line );

	/// Draws all cells of the Maze to image Canvas object.
	void draw_maze();

public:

	/// Default constructor.
	Render( const Maze * maze, const Nat & width, const Nat & height );

	/// Default destructor.
	~Render();

	/// Saves the image Canvas object to a png file.
	void draw_image( const Str & path = "./data/img.png" );

	/// Overload of ostream operator.
	friend std::ostream & operator << ( std::ostream & os, const Render & r ){
		os 	<< "Render = [\n"
			<< "  < maze_width    , " << std::setw(5) << r.ptr_maze->get_wid()  << " >\n"
			<< "  < maze_height   , " << std::setw(5) << r.ptr_maze->get_hei() << " >\n"
			<< "  < image_width   , " << std::setw(5) << r.img->width()  << " >\n"
			<< "  < image_height  , " << std::setw(5) << r.img->height() << " >\n"
			<< "  < cell_width    , " << std::setw(5) << r.cell_width    << " >\n"
			<< "  < cell_height   , " << std::setw(5) << r.cell_height   << " >\n"
			<< "  < border_width  , " << std::setw(5) << r.border_wid    << " >\n"
			<< "  < border_height , " << std::setw(5) << r.border_hei    << " >\n"
			<< "]";

		return os;
	}

};

#endif