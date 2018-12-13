#include "common.h"
#include "maze.h"
#include "render.h"

class Wallf {

private:

	/// Index type, just for abstraction purporse.
	typedef Nat index_t;

	/// Direction type, just for abstraction purporse.
	typedef Nat direction_t;

	/// Pointer to the maze to be solved.
	Maze * m;

	/// Pointer to the render object which will draw each step of solving process.
	Render * r;

	/// Index of start point of the maze;
	index_t start_point;

	/// Index of end point of the maze.
	index_t end_point;

	/// Current position of the agent.
	index_t position;

	/// Current direction of the agent.
	direction_t direction;

	/// Directions that can be taken from the current cell.
	enum Directions : direction_t {
		Top    = 0,
		Right  = 1,
		Bottom = 2,
		Left   = 3
	};

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

	/// Make the agente go ahead one cell relative to current direction and position.
	void go_ahead( void );

	inline void turn_left( void ) { direction = ( direction - 1 ) % 4;
		std::cout << "new dir = " << direction << std::endl; };

	inline void turn_right( void ) { direction = ( direction + 1 ) % 4;
		std::cout << "new dir = " << direction << std::endl; };

	inline void turn_back( void ) { direction = ( direction + 2 ) % 4;
		std::cout << "new dir = " << direction << std::endl; };

public:

	/// Default constructor
	Wallf( Maze * param_m , Render * param_r );

	/// Default destructor
	~Wallf( void );

	/// Retrives the state of the maze
	/** @return The state of the maze, which can be Solved or Unsolved. */
	bool is_solved( void );

	/// Advances one step in the solution search.
	/** Checks if the current position is the end of the maze.\n
		If it is not the end, advance on the algorithm.\n
		Updates the states of visited and discarded cells. */
	void solve_step( void );
	
	/// Solves the maze completely.
	/** Solves the maze by calling `solve_step()` until it is solved. */
	void solve_maze( void );

};