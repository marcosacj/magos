#ifndef MAGOS_H
#define MAGOS_H

#include "common.h"
#include "maze.h"
#include "render.h"

class Magos {

private:

	Maze * m;

	Render * r;

	Nat game_state;

public:

	enum States {

		STARTING,
		BUILDING,
		SOLVING,
		DONE,
		ERROR

	};

	void welcome() const;

	/// Default constructor.
	Magos();

	/// Default destructor.
	~Magos();

	inline Nat get_state() const { return game_state; };

	void initializer( int argc, char* argv[] );

	void process_events();

	void update();

	void renderize();

	bool game_over();

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