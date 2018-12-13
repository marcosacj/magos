#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <iomanip>

#include <math.h> // floor

#include "common.h" // includes definition of a Cell and other useful types

/// Models the maze of the project.
class Maze {

private:

	/// Basic type of a cell in the maze.
	/** A cell is modeled as a byte (unsigned char), that is, a sequence of eight bits, 
	  each of then meaning an specific information.\n
	  The four first bits mean if the Up, Right, Bottom and Left walls are stand up.\n
	  The last four bits mean the state of that cell during solving process:\n
	  untested, visited, visited-path, visited-discarded. */
	typedef std::bitset<8> Cell;

	typedef std::size_t State;   //!< State of cell.
	typedef std::size_t Wall;    //!< Wall of a cell.
	typedef std::size_t index_t; //!< Index of a cell.

	/// Dimensions of the matrix.
	Nat width, height;

	/// Pointer to the matrix of cells, which represents the maze.
	Cell * matrix { nullptr };

	/// Converts coordinates to index in the matrix.
	/** @param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines).
		@return Corresponding index of the coordinates.
		@throw std::invalid_argument When the coordinates are outside the matrix. */
	Nat to_index( const Coord & column, const Coord & line ) const;

	/// Retrieves the column coordinate of a cell from its index.
	/** This method suppose the index is valid (inside the maze) and does not check bounds.
		@param index Index of the cell.
		@return Corresponding column of the cell. */
	inline Coord to_col( const index_t & index ) const { return index % width; };

	/// Retrieves the line coordinate of a cell from its index.
	/** This method suppose the index is valid (inside the maze) and does not check bounds.
		@param index Index of the cell.
		@return Corresponding line of the cell. */
	inline Coord to_lin( const index_t & index ) const { return floor( index / width ); };

	/// Checks if a coordinates pair points to inside the matrix.
	/** @param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines).
		@return True if corrdinate is valid and false otherwise. */
	bool valid_coord( const Coord & column, const Coord & line ) const ;

public:

	/// Gets the width (number of cells) in the maze.
	/** @return Number of cells, horizontal direction. */
	inline Nat get_wid( void ) const { return width; };

	/// Gets the height (number of cells) in the maze.
	/** @return Number of cells, vertical direction. */
	inline Nat get_hei( void ) const { return height; };

	/// Enumeration of cell states.
	/** States are set as positive integers and, when assigned to a cell, are converted to Cell
		type (that is, an eight bits set). */
	enum States : State {
		
		Untested   = 128, //!< Equivalent to 10000000
		Visited    = 64,  //!< Equivalent to 01000000
		Path       = 32,  //!< Equivalent to 00100000
		Discarded  = 16,  //!< Equivalent to 00010000

	};

	/// Enumeration of walls.
	/** Walls are set as positive integers and, when assigned to a cell, are converted to Cell
		type (that is, an eight bits set). */
	enum Walls : Wall {

		Top    = 1,   //!< Equivalent to 00000001
		Right  = 2,   //!< Equivalent to 00000010
		Bottom = 4,   //!< Equivalent to 00000100
		Left   = 8    //!< Equivalent to 00001000

	};

	/// Constructor initialized with dimensions.
	/** The constructor sets width and height passed, allocates memory to the matrix
		and fills all cells with states Untested and all the walls up.
		@param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines). */
	Maze( const Nat & width = 0, const Nat & height = 0 );

	/// Destructor of the maze.
	~Maze( void );

	/// Knocks down a Wall.
	/** Receives the coordinates of a cell and a target Wall (that is, the corresponding Wall enumerator)
		to be knocked down.\n
		Note that corresponding walls of neighbor cells are also knocked down.
		@param column Column of the target cell.
		@param line Line of the targes cell.
		@param targetWall Target wall to be knocked down.
		@throw std::invalid_argument When the coordinates are outside the matrix.
		@throw std::invalid_argument When the target wall does not correspond to any of the enumerated.
		@throw std::invalid_argument When try to knock down a border wall. */
	void knock_down( const Coord & column, const Coord & line, const Wall & targetWall );

	/// Sets the state of a target cell, based on coordinates.
	/** Receives the coordinates of a cell and a target State (that is, the corresponding State enumerator).
		@param column Column of the target cell.
		@param line Line of the targes cell.
		@param targetState Target State to be set.
		@throw std::invalid_argument When the coordinates are outside the matrix.
		@throw std::invalid_argument When try to set an invalid state. */
	void set_state( const Coord & column, const Coord & line, const State & targetState );

	/// Sets the state of a target cell, based on index.
	/** Receives the index of a cell and a target State (that is, the corresponding State enumerator).
		@param index Index of the target cell.
		@param targetState Target State to be set.
		@throw std::invalid_argument When the index (converted into coordinates) is outside the matrix.
		@throw std::invalid_argument When try to set an invalid state. */
	void set_state( const index_t & index, const State & targetState );

	/// Checks if a target wall is standing.
	/** This method receives a target cell and a target wall to check if this one is standing.\n
		As it converts the cell location from coordinates to index, it does bounds checking.\n
		If an invalid wall is passed, the method returns false, does not throws an exception.
		@param column Column of the target cell.
		@param line Line of the target cell.
		@param targetWall Code of the target wall. Should be one from Walls public enum.
		@throw std::runtime_error When the coordinates are outside the maze. */
	bool hasWall( const Coord & column, const Coord & line, const Wall & targetWall ) const;

	/// Checks if a target wall is standing.
	bool hasWall( const index_t & index, const Wall & targetWall ) const;

	/// Checks the state of a target cell.
	/** This method receives a target cell and a target state, and checks if that cell is set to
		that state.\n
		As it converts the cell location from coordinates to index, it does bounds checking.\n
		If an invalid state is passed, the method returns false, does not throws an exception.
		@param column Column of the target cell.
		@param line Line of the target cell.
		@param targetState Code of the target state. Should be one from States public enum. */
	bool isState( const Coord & column, const Coord & line, const State & targetState ) const;

	/// Checks the state of a target cell.
	bool isState( const index_t & index, const State & targetState ) const;

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