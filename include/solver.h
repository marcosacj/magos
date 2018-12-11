#include <stack>

#include "common.h"
#include "maze.h"

class Solver {

private:

	/// Index type, just for abstraction purporse.
	typedef Nat index_t;

	/// Pointer to the maze to be solved.
	Maze * m;

	/// Pointer to the render object which will draw each step of solving process.
	Render * r;

	/// Stack of indexes which compose the solution path of the maze.
	std::stack<index_t> path;

	/// Index of start point of the maze;
	index_t start_point;

	/// Index of end point of the maze.
	index_t end_point;

	/// Directions that can be taken from the current cell.
	enum Directions : Nat {
		Top,
		Right,
		Bottom,
		Left
	};

	/// Returns a vector with directions which can be taken.
	/** One direction is part of the vector if the target neighbor cell is unvisited.\n
		Otherwise (if target neighbor is discarded or is a wall), it is not part of the vector. */
	std::vector<Nat> check_directions( const index_t & index ) const ;

	/// Checks if the current position is the end point of the maze.
	bool is_end( void ) const ;

	/// Converts the location of a cell from coordinates to index.
	inline index_t to_index( const Coord & column, const Coord & line ){ return m->get_wid() * line + column; };

	/// Retrieves the column coordinate of a cell from its index.
	inline Coord to_col( const index_t & index ) const { return index % m->get_wid(); };

	/// Retrieves the line coordinate of a cell from its index.
	inline Coord to_lin( const index_t & index ) const { return floor( index / m->get_wid() ); };

public:

	/// Default constructor.
	Solver( Maze * param_m, Render * param_r );

	/// Constructor with start point.
	Solver( Maze * param_m, Render * param_r, const index_t & start );

	/// Constructor with start and end points.
	Solver( Maze * param_m, Render * param_r, const index_t & start, const index_t & end );

	/// Default destructor.
	// ~Solver( void );

	/// Retrives the state of the maze, which can be Solved or Unsolved.
	bool is_solved( void );

	/// Advances one step in the solution search.
	void solve_step( void );
	
	/// Solves the maze completely, by calling `solve_step()`.
	void solve_maze( void );

};