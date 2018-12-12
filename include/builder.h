#ifndef BUILDER_H
#define BUILDER_H

#include <math.h> // floor

#include "common.h"
#include "maze.h"
#include "render.h"
#include "hash.h"
#include "roulette.h"

/// This class implements a building method of a maze base on Hash Table.
class HashBuilder {

private:

	/// Pointer to maze to be built.
	Maze * m;

	/// Pointer to a render object used to make a png file of the maze.
	Render * r;

	/// Vector of index of the maze, which works like a linked list.
	/** This object uses built-in methods to randomly traverse all cells of the maze
		during building process.\n
		It is initialized inside the constructor acording to dimensions of the maze. */
	Roulette<Nat> c;

	/// Pointer to a Hash Table object, which controls the building process.
	/** This object uses built-in methods to control the building process through the idea of
		groups of paths (represented by the keys of each value).\n
		In this building strategy, two cells should have one, and only one, path connecting each other.\n
		When this connection happens, the two cells are merged in the HashTable, having the same key.\n
		The building process ends when all cells have one, and only one, path connecting them, two by two.\n
		This situation happens when the Hash Table has only one element, with only one key. */
	HashTable< Nat, Nat > * h;

	/// Converts the location of a cell from coordinates to index.
	/** Note this method does not do bounds checking, neither throws exceptions if coordinate are
		outside the maze.\n
		If necessary, the method `valid_coord()` may be used before calling this method.
		@param column Column of the targer cell.
		@param line Line of the target cell.
		@return Index of the targed cell. */
	inline Nat to_index( const Coord & column, const Coord & line ){ return m->get_wid() * line + column; };

	/// Retrieves the column coordinate of a cell from its index.
	/** This method suppose the index is valid (inside the maze) and does not check bounds.
		@param index Index of the cell.
		@return Corresponding column of the cell. */
	inline Coord to_column( const Nat & index ) { return index % m->get_wid(); };

	/// Retrieves the line coordinate of a cell from its index.
	/** This method suppose the index is valid (inside the maze) and does not check bounds.
		@param index Index of the cell.
		@return Corresponding line of the cell. */
	inline Coord to_line( const Nat & index ) { return floor( index / m->get_wid() ); };

	/// Calculates the index of the neighbor cell of a given cell and given wall.
	/** This method receives the coordinates of the choosen cell.\n
		Also, do bounds checking and throws	exceptions in invalid cases.
		@param column Column of the given cell.
		@param line Line of the given cell.
		@param targetWall Target wall whose neighbor should be taken.
		@throw std::runtime_error When the coordinates are not valid or outside the maze.
		@throw std::runtime_error When the target wall is not valid.
		@throw std::runtime_error When the target wall is a border of the maze (this case is composed
			of 4 subcases). */
	Nat neighbor( const Coord & column, const Coord & line, const Nat & targetWall );

	/// Receives a cell (index) and a wall and returns the index of the neighbor cell.
	/** This method is just an overload, for convenience of giving index of the choosen cell instead
		its coordinates.\n
		This just converts index to coordinates and calls the method which receives	coordinates as parameters.
		@param index Index of the choosen cell.
		@param targetWall Target wall whose neighbor should be taken. */
	Nat neighbor( const Nat & index, const Nat & targetWall );

	/// Checks if a coordinates pair points to inside the matrix.
	/** @param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines).
		@return True if corrdinate is valid and false otherwise. */
	bool valid_coord( const Coord & column, const Coord & line ) const ;

public:

	/// Default constructor.
	/** This constructor updates maze and render pointers, allocates memory to HashTable object
		and fills it with the values of the indexes of the maze.\n
		Also, fills and shuffles the vector of indexes inside the roulette object.
		@param m Pointer to the maze object.
		@param r Pointer to the render object. */
	HashBuilder( Maze * m, Render * r );

	/// Default destructor.
	~HashBuilder( void );

	/// Returns the state of the maze acording to the building process.
	/** This method may be use by an external controller of the building process.
		@return True if the maz is built (that is, if the size of HashTable is just 1)
		or False otherwise. */
	inline bool is_built( void ) const { return h->size() == 1; };

	/// Building method for test purposes.
	/** This method implements an example in how to control the building process. */
	void build_maze( void );

	/// Advance one step in the building process, usually knock down a random wall.
	/** This method performs one step in the building proceess.\n
		It uses the shuffled vector of indexes to pick a random cell.\n
		Then it choose a random wall and calculate the respective neighbor.\n
		A connection checking is made through the HashTable object.\n
		If there is no connection, the choosen wall is knock down, connecting the cells.\n
		The boolean return value may be used to control when a snapshot of the maze should be
		drawn to a png file, by an external controller of the process.
		@return True if a wall was knocked down and False otherwise. */
	bool build_step( void );

};

#endif