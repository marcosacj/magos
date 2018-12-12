#ifndef MAGOS_H
#define MAGOS_H

#include "common.h"
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

	/// counter to file names
	Nat img_idx;

public:

	/// States of the game.
	enum States {

		STARTING,
		BUILDING,
		BUILT,
		SOLVING,
		SOLVED,
		OVER,
		ERROR

	};

	/// Show an welcome message to the user.
	void welcome( void ) const;

	/// Default constructor.
	Magos( void );

	/// Default destructor.
	~Magos( void );

	/// Returns the state of the game.
	inline Nat get_state() const { return game_state; };

	/// Process and validate input arguments
	void initializer( int argc, char* argv[] );

	/// Process all input events from the user (none in this game).
	void process_events( void );

	/// Check the state of the game and do the proper action (build or solve).
	void update( void );

	/// Check the state of the game and draw the image file.
	void renderize( void );

	/// Check if the game is over (built and solver).
	bool game_over( void );

	friend std::ostream & operator << ( std::ostream & os, const Magos & mg ){

		os 	<< "Magos = [" << std::endl
			<< "  < " << std::setw(10) << std::left << "m_wid"
			<< ", " << std::setw(5) << std::right << mg.m->get_wid() << " >" << std::endl

			<< "  < " << std::setw(10) << std::left << "m_hei"
			<< ", " << std::setw(5) << std::right << mg.m->get_hei() << " >" << std::endl

			<< "  < " << std::setw(10) << std::left << "r_wid"
			<< ", " << std::setw(5) << std::right << mg.r->get_wid() << " >" << std::endl

			<< "  < " << std::setw(10) << std::left << "r_hei"
			<< ", " << std::setw(5) << std::right << mg.r->get_hei() << " >" << std::endl

			<< "]";
		
		return os;

	}

};

#endif