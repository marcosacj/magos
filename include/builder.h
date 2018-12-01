#ifndef BUILDER_H
#define BUILDER_H

#include <stack>

#include "common.h"
#include "maze.h"
#include "hash.h"

class HashBuilder {

private:

	/// pointer to the initial maze to be built.
	Maze * m;

	HashTable< int, int > * h;

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