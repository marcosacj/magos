#include "common.h"
#include "maze.h"

class Solver {

private:

	/// Index type, just for abstraction purporse.
	typedef Nat index_t;

	/// Pointer to the maze to be solved.
	Maze * m;

	/// Stack of indexes which compose the solution path of the maze.
	std::stack<index_t> path;

	/// Index of start point of the maze;
	index_t start_point;

	/// Index of end point of the maze.
	index_t end_point;

	/// Directions that can be taken from the current cell.
	enum Directions : Nat {
		TOP,
		RIGHT,
		BOTTOM,
		LEFT
	};

	/// Returns a vector with directions which can be taken.
	/** One direction is part of the vector if the target neighbor cell is unvisited.\n
		Otherwise (if target neighbor is discarded or is a wall), it is not part of the vector. */
	std::vector<Nat> check_directions( const index_t & index ) const ;

	/// Returns if a cell is and end of corridor.
	/** An end of corridor is a cell whose unique possible moviment is to come back. */
	bool end_corridor( const index_t & index ) const ;

	/// Checks if the current position is the end point of the maze.
	bool is_end( void ) const ;

	inline index_t to_index( const Coord & column, const Coord & line ){ return m->get_wid() * line + column; };

	inline Coord to_column( const index_t & index ) { return index % m->get_wid(); };

	inline Coord to_line( const index_t & index ) { return floor( index / m->get_wid() ); };

public:

	/// Default constructor.
	Solver( Maze * param_m );

	/// Default destructor.
	~Solver( void );

	/// Retrives the state of the maze, which can be Solved or Unsolved.
	bool is_solved( void );

	/// Advances one step in the solution search.
	void solve_step( void );
	
	/// Solves the maze completely, by calling `solve_step()`.
	void solve_maze( void );

};