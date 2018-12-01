#ifndef MAGOS_H
#define MAGOS_H

#include "common.h"
#include "maze.h"
#include "render.h"

class Magos {

private:

	Maze * m;

	Render * r;

	enum States{

		STARTING,
		BUILDING,
		SOLVING,
		DONE

	};

	void welcome() const;

public:

	/// Default constructor.
	Magos();

	/// Default destructor.
	~Magos();

	void initializer( int argc, char* argv[] );

	void process_events();

	void update();

	void renderize();

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