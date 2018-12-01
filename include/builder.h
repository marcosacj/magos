#ifndef BUILDER_H
#define BUILDER_H

#include <stack>

#include "common.h"
#include "maze.h"

class HashBuilder {

private:

	/// pointer to the initial maze to be built.
	Maze * m;

	/// pointer to hash table used during build process.
	/** 1st element represents the index of the cell.
		2nd element represents the "path group" (hash) of the cell. */
	std::pair<int, int> * hasht;

	/// stack of indexes to be picked used during build process.
	std::stack<int> shuffled;

public:

	/// Default constructor.
	HashBuilder( Maze * target );

	/// Default destructor.
	~HashBuilder();

	/// Receives a pointer to a Maze object and turns it into a perfect Maze.
	void build_maze();

};

#endif