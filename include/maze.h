#include <iostream>
#include <iomanip>

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
	typedef unsigned char Cell;

	// enum de estados
	enum States : Nat {
		
		UpWall     = 128, //!< Equivalent to 10000000
		RightWall  = 64,  //!< Equivalent to 01000000
		BottomWall = 32,  //!< Equivalent to 00100000
		LeftWall   = 16,  //!< Equivalent to 00010000
		
		Unvisited  = 8,   //!< Equivalent to 00001000
		Visited    = 4,   //!< Equivalent to 00000100
		Path       = 2,   //!< Equivalent to 00000010
		Discarded  = 1    //!< Equivalent to 00000001

	};

	// dimensions of board
	Nat width;
	Nat height;

	// board pointer
	Nat * board{nullptr};

public:

	// constructor
	Maze( const Nat & width = 0, const Nat & height = 0 );

	// destructor
	~Maze();

	// overload <<
	friend std::ostream & operator << ( std::ostream & os, const Maze & m ) {

		for ( Nat h{0} ; h < m.height ; h++ ){

			for ( Nat w{0} ; w < m.width ; w++ ){

				os << std::setw(3) << *(m.board + w*h) << " ";

			}

			// to prevent a blank line at final
			if( h < m.height - 1 ){
				os << std::endl;
			}

		}

		return os;

	}

};