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
	const Maze * ptr_maze { nullptr };

	/// Pointer to a Canvas object which represents the image.
	Canvas * img { nullptr };

	/// Draws a single cell on the image Canvas object.
	/** This method is responsible for drawing a single cell on the Canvas object.
		It receives the coordinates of the target cell, checks which of the walls are standing,
		through Maze built-in methods, and draw them.
		Also checks the state of the cell, also through Maze methods, and draw a colored box inside it,
		depending on each state.
		This method can throw exceptions acording to Maz built-in method.
		@param column Column of the target cell to be drawn.
		@param line Line of the target cell to be drawn. */
	void draw_cell( const Coord & column, const Coord & line );

	/// Draws all cells of the Maze to image Canvas object.
	/** This method uses two loops (horizontal and vertical) to draw all the cells of the maze.
		Make use of the method `draw_cell()`.
		It is used by `draw_image()` method. */
	void draw_maze( void );

public:

	/// Returns the width of the image Canvas object.
	inline Nat get_wid( void ) const { return img->width(); };

	/// Returns the height of the image Canvas object.
	inline Nat get_hei( void ) const { return img->height(); };

	/// Default constructor.
	/** This constructor calculates dimensions and attributes of the image and also allocates
		memory to Canvas image object.
		Borders and cells dimensions (width and height) are calculated and updated.
		@param maze Pointer to a Maze object to be drawn.
		@param width Horizontal dimension of the image, in pixels.
		@param height Vertical dimention of the image, in pixels. */
	Render( const Maze * maze, const Nat & width, const Nat & height );

	/// Deductive constructor.
	/** This constructor calculates dimensions and attributes of the image and also allocates
		memory to Canvas image object.
		Borders and cells dimensions (width and height) are calculated and updated.
		In particular, this constructor receives just the width of the image and automatically
		assigns the height in the same proportion of Maze dimensions.
		@param maze Pointer to a Maze object to be drawn.
		@param width Horizontal dimension of the image, in pixels. */
	Render( const Maze * maze, const Nat & width );

	/// Default destructor.
	~Render( void );

	/// Saves the image Canvas object to a png file.
	/** This method receives a destination file name and save the maze as a png image file.
		Its useful to save snapshots of the maze during building or solving processes.
		@param path path and filename of the file to be created. */
	void draw_image( const Str & path = "./data/img.png" );

	/// Overload of ostream operator.
	/** Shows informations about maze and image characteristics (image, borders and cell dimensions). */
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