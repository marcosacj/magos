#include <iostream>
#include <iomanip>
#include <bitset>

/// A simple natual number
typedef std::size_t Nat;

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

	/// Dimensions of the board.
	Nat width, height;

	/// Pointer to the board of cells, which represents the maze.
	Cell * board{nullptr};

	/// Converts coordinates to index in the board.
	/** @param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines). */
	inline Nat to_index( const Nat & column, const Nat & line ) const { return width*line + column; };

public:

	/// Enumeration of cell states.
	/** States are set as positive integers and, when assigned to a cell, are converted to Cell
		type (that is, an eight bits set). */
	enum States : Nat {
		
		Untested   = 8,   //!< Equivalent to 00001000
		Visited    = 4,   //!< Equivalent to 00000100
		Path       = 2,   //!< Equivalent to 00000010
		Discarded  = 1    //!< Equivalent to 00000001

	};

	/// Enumeration of walls.
	/** Walls are set as positive integers and, when assigned to a cell, are converted to Cell
		type (that is, an eight bits set). */
	enum Walls : Nat {

		Up     = 128, //!< Equivalent to 10000000
		Right  = 64,  //!< Equivalent to 01000000
		Bottom = 32,  //!< Equivalent to 00100000
		Left   = 16,  //!< Equivalent to 00010000

	};

	/// Constructor initialized with dimensions.
	/** The constructor sets width and height passed, allocates memory to the board
		and fills all cells with states Untested and all the walls up.
		@param width Width of the maze (number of columns).
		@param height Height of the maze (number of lines). */
	Maze( const Nat & width = 0, const Nat & height = 0 );

	/// Destructor of the maze.
	~Maze();

	/// Knocks down a Wall.
	/** Receives the coordinates of a cell and a target Wall (that is, the corresponding state)
		to be knocked down. Note that corresponding walls of neighboor cells are also knocked down.
		@param column Column of the target cell.
		@param line Line of the targes cell.
		@param targetWall Target wall to be knocked down.
		@throw std::invalid_argument If the coordinates are outside the board.
		@throw std::invalid_argument If the target wall does not correspond to any of the enumerated. */
	void knock_down( const Nat & column, const Nat & line, const Nat & targetWall );

	/// Sets the state of a target cell.
	void set_state( const Nat & column, const Nat & line, const Nat & state );

	/// Overload of stream operator.
	friend std::ostream & operator << ( std::ostream & os, const Maze & m ) {

		for ( Nat h{0} ; h < m.height ; h++ ){

			for ( Nat w{0} ; w < m.width ; w++ ){

				// os << std::setw(3) << (*(m.board + m.to_index(w, h) )).to_ulong() << " ";
				os << *(m.board + m.to_index(w, h) ) << " ";

			}

			// to prevent a blank line at final
			if( h < m.height - 1 ){
				os << std::endl;
			}

		}

		return os;

	}

};