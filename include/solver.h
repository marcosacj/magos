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
	/** The algorithm uses built-in method of the stack to keep track of the visited
		and discarded cells. */
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
		Otherwise (if target neighbor is discarded or is a wall), it is not part of the vector.
		@param index Index of the current cell.
		@return The vector will contain the codes of possible directions, or will be empty (if)
		no direction is possible. */
	std::vector<Nat> check_directions( const index_t & index ) const ;

	/// Converts the location of a cell from coordinates to index.
	/** Note this method does not check bounds, neither throws exceptions if coordinate are
		outside the maze.\n
		@param column Column of the targer cell.
		@param line Line of the target cell.
		@return Index of the target cell. */
	inline index_t to_index( const Coord & column, const Coord & line ){ return m->get_wid() * line + column; };

	/// Retrieves the column coordinate of a cell from its index.
	/** This method suppose the index is valid (inside the maze) and does not check bounds.
		@param index Index of the cell.
		@return Corresponding column of the cell. */
	inline Coord to_col( const index_t & index ) const { return index % m->get_wid(); };

	/// Retrieves the line coordinate of a cell from its index.
	/** This method suppose the index is valid (inside the maze) and does not check bounds.
		@param index Index of the cell.
		@return Corresponding line of the cell. */
	inline Coord to_lin( const index_t & index ) const { return floor( index / m->get_wid() ); };

public:

	/// Default constructor.
	/** Sets the internal pointers to maze and render objects.\n
		Sets start and end points (index of respective cells).\n
		Pushes the start point index to the stack of solution.
		@param param_m Pointer to the external maze object.
		@param param_r Pointer to the external render object. */
	Solver( Maze * param_m, Render * param_r );

	/// Constructor with start point. (not implemented)
	/** Sets the internal pointers to maze and render objects.\n
		Sets start and end points (index of respective cells).\n
		Pushes the start point index to the stack of solution.
		@param param_m Pointer to the external maze object.
		@param param_r Pointer to the external render object.
		@param start Index of the start point cell. */
	Solver( Maze * param_m, Render * param_r, const index_t & start );

	/// Constructor with start and end points. (not implemented)
	/** Sets the internal pointers to maze and render objects.\n
		Sets start and end points (index of respective cells).\n
		Pushes the start point index to the stack of solution.
		@param param_m Pointer to the external maze object.
		@param param_r Pointer to the external render object.
		@param start Index of the start point cell.
		@param end Index os the end point cell. */
	Solver( Maze * param_m, Render * param_r, const index_t & start, const index_t & end );

	/// Retrives the state of the maze
	/** @return The state of the maze, which can be Solved or Unsolved. */
	bool is_solved( void );

	/// Advances one step in the solution search.
	/** Checks if the current position is the end of the maze.\n
		If it is not the end, advance on the algorithm.\n
		Checks possible directios to take and choose an unvisited one to go.\n
		Updates the states of visited and discarded cells. */
	void solve_step( void );
	
	/// Solves the maze completely.
	/** Solves the maze by calling `solve_step()` until it is solved. */
	void solve_maze( void );

};