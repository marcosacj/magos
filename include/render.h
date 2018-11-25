#ifndef RENDER_H
#define RENDER_H

#include "stb_image_write.h"

#include "maze.h"
#include "canvas.h"

typedef std::size_t Nat; //!< Simple natural number.
typedef std::size_t Coord; //!< Coordinate of a cell.

using namespace canvas;

/// Receives a Maze object and make a png file.
class Render {

private:

	Nat image_width;  //!< Width of the image, in pixels.
	Nat image_height; //!< Height of the image, in pixels.

	Nat cell_width;  //!< Width of each cell on image, in pixels.
	Nat cell_height; //!< Height of each cell on image, in pixels.

	/// Pointer to target maze.
	const Maze * ptr_maze{nullptr};

	/// Pointer to a Canvas object which represents the image.
	Canvas * img{nullptr};

	/// Draws a single cell on the image Canvas object.
	void draw_cell( const Coord & column, const Coord & line );

public:

	/// Default constructor.
	Render( const Maze * maze, const Nat & width, const Nat & height );

	/// Default destructor.
	~Render();

	/// Overload of ostream operator.
	friend std::ostream & operator << ( std::ostream & os, const Render & r ){
		os 	<< "Render = [\n"
			<< "  < image_width  , " << r.image_width  << " >\n"
			<< "  < image_height , " << r.image_height << " >\n"
			<< "  < cell_width   , " << r.cell_width   << " >\n"
			<< "  < cell_height  , " << r.cell_height  << " >\n"
			<< "]";

		return os;
	}

};

#endif