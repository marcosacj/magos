#include <iostream>

#include "render.h"
#include "builder.h"

int main( int argc, char* argv[] ){

	// initialize main attributes
	Nat m_wid { static_cast<Nat> ( std::atoi( argv[1] ) ) };
	Nat m_hei { static_cast<Nat> ( std::atoi( argv[2] ) ) };
	Nat h_wid { static_cast<Nat> ( std::atoi( argv[3] ) ) };

	// depending on input, image heigth will be passed or calculated
	Nat h_hei;

	if( argc > 4 )
		h_hei = static_cast<Nat> ( std::atoi( argv[4] ) );
	else
		h_hei = m_hei * h_wid / m_wid;


	Maze m{ m_wid , m_hei };

	Render r{ & m, h_wid , h_hei };

	HashBuilder builder{ & m, & r };

	builder.build_maze();

	return 0;
	
}