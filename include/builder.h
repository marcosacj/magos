#ifndef BUILDER_H
#define BUILDER_H

#include <stack>

#include <math.h> // floor

#include "common.h"
#include "maze.h"
#include "hash.h"

class HashBuilder {

private:

	/// pointer to the initial maze to be built.
	Maze * m;

	HashTable< Nat, Nat > * h;

	/// stack of indexes to be picked used during build process.
	std::stack<Nat> s;

	// Convert from coordinates to index of a cell
	inline Nat to_index( const Coord & column, const Coord & line ){ return m->get_wid() * line + column; }

	/// Convert from index to column of a cell.
	inline Coord to_column( const Nat & index ) { return index % m->get_wid(); };

	/// Convert from index to line of a cell.
	inline Coord to_line( const Nat & index ) { return floor( index / m->get_wid() ); };

	// receives a cell (coorinates) and a wall and returns the index of the neighbor cell.
	Nat neighbor( const Coord & column, const Coord & line, const Nat & targetWall );

	// receives a cell (index) and a wall and returns the index of the neighbor cell.
	Nat neighbor( const Nat & index, const Nat & targetWall );

public:

	/// Default constructor.
	HashBuilder( Maze * target );

	/// Default destructor.
	~HashBuilder();

	/// Receives a pointer to a Maze object and turns it into a perfect Maze.
	void build_maze();

};

#endif