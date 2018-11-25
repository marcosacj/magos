#ifndef RENDER_H
#define RENDER_H

#include "stb_image_write.h"

#include "maze.h"
#include "canvas.h"

typedef std::size_t Nat; //!< Simple natural number.

using namespace canvas;

/// This class is responsible for read a Maze object, draw to an image and save it to a png file.
class Render {

private:

	/// Dimensions of the image, in pixels.
	Nat image_width, image_height;

	/// Dimensions of each cell on image, in pixels.
	Nat cell_width, cell_height;

	/// Pointer to target maze.
	const Maze * ptr_maze{nullptr};

	/// Pointer to a Canvas object which represents the image.
	Canvas * img{nullptr};

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