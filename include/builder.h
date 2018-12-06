#ifndef BUILDER_H
#define BUILDER_H

#include <stack>

#include <math.h> // floor

#include "common.h"
#include "maze.h"
#include "render.h"
#include "hash.h"
#include "roulette.h"

class HashBuilder {

private:

	/// Pointer to maze to be built.
	Maze * m;

	/// Pointer to a render object.
	Render * r;

	/// Roulette to store shuffle cell indexes
	Roulette<Nat> c;

	// counter to file names
	Nat img_idx;

	HashTable< Nat, Nat > * h;

	/// stack of indexes to be picked used during build process.
	std::stack<Nat> s;

	// Convert from coordinates to index of a cell
	inline Nat to_index( const Coord & column, const Coord & line ){ return m->get_wid() * line + column; };

	/// Convert from index to column of a cell.
	inline Coord to_column( const Nat & index ) { return index % m->get_wid(); };

	/// Convert from index to line of a cell.
	inline Coord to_line( const Nat & index ) { return floor( index / m->get_wid() ); };

	// receives a cell (coorinates) and a wall and returns the index of the neighbor cell.
	Nat neighbor( const Coord & column, const Coord & line, const Nat & targetWall );

	// receives a cell (index) and a wall and returns the index of the neighbor cell.
	Nat neighbor( const Nat & index, const Nat & targetWall );

	/// Checks if a coordinates pair points to inside the matrix.
	/** @param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines).
		@return True if corrdinate is valid and false otherwise. */
	bool valid_coord( const Coord & column, const Coord & line ) const ;

public:

	/// Default constructor.
	HashBuilder( Maze * m, Render * r );

	/// Default destructor.
	~HashBuilder();

	inline bool is_built( void ) const { return h->size() == 1; };

	/// Receives a pointer to a Maze object and turns it into a perfect Maze.
	void build_maze( void );

	// Comment
	void build_step( void );

};

#endif