#include "magos.h"

Magos::Magos( const Nat & maze_wid , const Nat & maze_hei , const Nat & img_wid , const Nat & img_hei ){

	std::cout << "Constructing Magos Game..." << std::endl;

	m = new Maze( maze_wid, maze_hei );

	r = new Render( m, img_wid, img_hei );

	std::cout << *m << std::endl;

}

Magos::Magos( const Nat & maze_wid , const Nat & maze_hei , const Nat & img_wid ){

	std::cout << "Constructing Magos Game..." << std::endl;

	m = new Maze( maze_wid, maze_hei );

	Nat img_hei{ maze_hei * img_wid / maze_wid };

	r = new Render( m, img_wid, img_hei );

	std::cout << *m << std::endl;

}

Magos::~Magos(){

	std::cout << "Destroying Magos Game..." << std::endl;

	delete m;
	delete r;

}

void Magos::welcome() const {

	// todo

}

void Magos::initializer( int argc, char* argv[] ){

	std::cout << argv[0] << std::endl;

	// here will go the new statements to maze and render, based on argc and argv

	// remove constructor methods

}