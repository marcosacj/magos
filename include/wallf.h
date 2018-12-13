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

	/// Current index of direction of the agent.
	direction_t direction;

	/// Directions that can be taken from the current cell.
	enum directions_e : direction_t {
		Top    = 0,
		Right  = 1,
		Bottom = 2,
		Left   = 3
	};

	/// Directions that can be taken from the current cell.
	std::vector<direction_t> directions_v { 
		Maze::Walls::Top, 
		Maze::Walls::Right, 
		Maze::Walls::Bottom, 
		Maze::Walls::Left 
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

	// inline Nat dir2wall( const direction_t & dir ) { return pow( 2, dir ); };

	inline direction_t left_direction( void ) { return ( direction - 1 ) % 4; };

	inline direction_t right_direction( void ) { return ( direction + 1 ) % 4; };

	inline direction_t back_direction( void ) { return ( direction + 2 ) % 4; };

	inline void turn_left( void ) { direction = left_direction(); };

	inline void turn_right( void ) { direction = right_direction(); };

	inline void turn_back( void ) { direction = back_direction(); };

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