#include "magos.h"

Magos::Magos(){

	std::cout << "Constructing Magos Game..." << std::endl;

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

	// check number of input arguments (mininum is 4)
	// [NAME OF PROGRAM] [MAZE WIDTH] [MAZE HEIGHT] [IMAGE WIDTH]
	if( argc < 4 ){
		throw std::invalid_argument( "Usage..." );
	}
 	
 	// initialize main attributes
	Nat maze_wid { static_cast<Nat> ( std::atoi( argv[1] ) ) };
	Nat maze_hei { static_cast<Nat> ( std::atoi( argv[2] ) ) };
	Nat img_wid  { static_cast<Nat> ( std::atoi( argv[3] ) ) };

	// depending on input, image heigth will be passed or calculated
	Nat img_hei;

	if( argc > 4 )
		img_hei = static_cast<Nat> ( std::atoi( argv[4] ) );
	else
		img_hei = maze_hei * img_wid / maze_wid;

	// create new Maze object
	m = new Maze( maze_wid, maze_hei );

	// create new Render object
	r = new Render( m, img_wid, img_hei );

	// check Maze object created
	std::cout << *m << std::endl;

}