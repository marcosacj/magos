#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <iomanip>

#include "common.h" // includes definition of a Cell and other useful types

/// Models the maze of the project.
class Maze {

private:

	/// Basic type of a cell in the maze.
	/** A cell is modeled as a byte (unsigned char), that is, a sequence of eight bits, 
	  each of then meaning an specific information.
	  The four first bits mean if the Up, Right, Bottom and Left walls are stand up.
	  The last four bits mean the state of that cell during solving process:
	  untested, visited, visited-path, visited-discarded. */
	typedef std::bitset<8> Cell;

	typedef std::size_t State; //!< State of cell.
	typedef std::size_t Wall;  //!< Wall of a cell.

	/// Dimensions of the matrix.
	Nat width, height;

	/// Pointer to the matrix of cells, which represents the maze.
	Cell * matrix{nullptr};

	/// Converts coordinates to index in the matrix.
	/** @param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines).
		@return Corresponding index of the coordinates.
		@throw std::invalid_argument When the coordinates are outside the matrix. */
	Nat to_index( const Coord & column, const Coord & line ) const;

	/// Checks if a coordinates pair points to inside the matrix.
	/** @param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines).
		@return True if corrdinate is valid and false otherwise. */
	bool valid_coord( const Coord & column, const Coord & line ) const ;

	/// Consult the state of a cell.
	/** Given the coordinates, the cell state is read and returned.
		Useful for builder, solver and render operations.
		@param column Horizontal coordinate of target cell.
		@param line Vertical coordinate of target cell.
		@return The cell state in the bitset format. */
	Cell get_cell( const Coord & column, const Coord & line ) const { 
		return matrix[ to_index( column, line ) ]; };

public:
	/// Gets the width (number of cells) in the maze.
	/** @return Number of cells, horizontal direction. */
	inline Nat get_width() const { return width; };

	/// Gets the height (number of cells) in the maze.
	/** @return Number of cells, vertical direction. */
	inline Nat get_height() const { return height; };

	/// Enumeration of cell states.
	/** States are set as positive integers and, when assigned to a cell, are converted to Cell
		type (that is, an eight bits set). */
	enum States : State {
		
		Untested   = 8,   //!< Equivalent to 00001000
		Visited    = 4,   //!< Equivalent to 00000100
		Path       = 2,   //!< Equivalent to 00000010
		Discarded  = 1    //!< Equivalent to 00000001

	};

	/// Enumeration of walls.
	/** Walls are set as positive integers and, when assigned to a cell, are converted to Cell
		type (that is, an eight bits set). */
	enum Walls : Wall {

		Top    = 128, //!< Equivalent to 10000000
		Right  = 64,  //!< Equivalent to 01000000
		Bottom = 32,  //!< Equivalent to 00100000
		Left   = 16,  //!< Equivalent to 00010000

	};

	/// Constructor initialized with dimensions.
	/** The constructor sets width and height passed, allocates memory to the matrix
		and fills all cells with states Untested and all the walls up.
		@param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines). */
	Maze( const Nat & width = 0, const Nat & height = 0 );

	/// Destructor of the maze.
	~Maze();

	/// Knocks down a Wall.
	/** Receives the coordinates of a cell and a target Wall (that is, the corresponding Wall enumerator)
		to be knocked down. Note that corresponding walls of neighboor cells are also knocked down.
		@param column Column of the target cell.
		@param line Line of the targes cell.
		@param targetWall Target wall to be knocked down.
		@throw std::invalid_argument When the coordinates are outside the matrix.
		@throw std::invalid_argument When the target wall does not correspond to any of the enumerated.
		@throw std::invalid_argument When try to knock down a border wall. */
	void knock_down( const Coord & column, const Coord & line, const Wall & targetWall );

	/// Sets the state of a target cell.
	/** Receives the coordinates of a cell and a target State (that is, the corresponding State enumerator).
		@param column Column of the target cell.
		@param line Line of the targes cell.
		@param targetState Target State to be set.
		@throw std::invalid_argument When the coordinates are outside the matrix.
		@throw std::invalid_argument When try to set an invalid state. */
	void set_state( const Coord & column, const Coord & line, const State & targetState );

	// method to get state of wall
	bool hasWall( const Coord & column, const Coord & line, const Wall & targetWall ) const;

	// methods to get state of cell
	bool isState( const Coord & column, const Coord & line, const State & targetState ) const;

	/// Overload of stream operator.
	/** @param os The target std::ostream.
		@param m The maze to be printed.
		@return The matrix of the maze in bitset format. */
	friend std::ostream & operator << ( std::ostream & os, const Maze & m ) {

		for ( Nat h{0} ; h < m.height ; h++ ){

			for ( Nat w{0} ; w < m.width ; w++ ){

				os << *(m.matrix + m.to_index(w, h) ) << " ";

			}

			// to prevent a blank line at final
			if( h < m.height - 1 ){
				os << std::endl;
			}

		}

		return os;

	}

};

#endif