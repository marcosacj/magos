#ifndef MAGOS_H
#define MAGOS_H

#include "common.h"
// #include "maze.h"
// #include "render.h"
#include "builder.h"
#include "solver.h"

class Magos {

private:

	/// Pointer to the maze object of the game.
	Maze * m;

	/// Pointer to the render object which will draw the image files.
	Render * r;

	/// Pointer the the HashBuilder object, which will construct the maze using Hash Table strategy.
	HashBuilder * b;

	/// Pointer to the Solver object, which will solve the maze using Backtracking strategy.
	Solver * s;

	/// Flag to represent the state of the game.
	Nat game_state;

public:

	/// States of the game.
	enum States {

		STARTING,
		BUILDING,
		SOLVING,
		DONE,
		ERROR

	};

	/// Show an welcome message to the user.
	void welcome( void ) const;

	/// Default constructor.
	// Magos( Maze * param_m, Render * param_r, HashBuilder * param_b, Solver * param_s );
	Magos( void );

	/// Default destructor.
	~Magos( void );

	inline Nat get_state() const { return game_state; };

	/// Process and validate input arguments
	void initializer( int argc, char* argv[] );

	/// Process all input events from the user (none in this game).
	void process_events( void );

	void update( void );

	void renderize( void );

	bool game_over( void );

	friend std::ostream & operator << ( std::ostream & os, const Magos & mg ){

		os 	<< "Magos = [" << std::endl
			<< "  < " << std::setw(10) << std::left << "maze_wid"
			<< ", " << std::setw(5) << std::right << mg.m->get_wid() << " >" << std::endl

			<< "  < " << std::setw(10) << std::left << "maze_hei"
			<< ", " << std::setw(5) << std::right << mg.m->get_hei() << " >" << std::endl

			<< "  < " << std::setw(10) << std::left << "img_wid"
			<< ", " << std::setw(5) << std::right << mg.r->get_wid() << " >" << std::endl

			<< "  < " << std::setw(10) << std::left << "img_hei"
			<< ", " << std::setw(5) << std::right << mg.r->get_hei() << " >" << std::endl

			<< "]";
		
		return os;

	}

};

#endif