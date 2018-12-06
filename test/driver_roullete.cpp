#include <iostream>

#include "roulette.h"

int main(){

	std::cout << "running..." << std::endl;

	Roulette<int> r;

	try {
		std::cout << "value = " << r.value() << std::endl;
	} catch( std::runtime_error & e ) {
		std::cout << e.what() << std::endl;
	}

	for ( int i(0) ; i < 5 ; i++ )
		r.add( i );

	std::cout << "r = " << r << std::endl;

	for ( int i(0) ; i < 15 ; i++ ){
		std::cout << "value = " << r.value() << std::endl;
		r.step();
	}

	r.point_to( 0 );
	std::cout << "point_to( 0 ) = " << r.value() << std::endl;

	r.point_to( 2 );
	std::cout << "point_to( 2 ) = " << r.value() << std::endl;

	r.point_to( 7 );
	std::cout << "point_to( 7 ) = " << r.value() << std::endl;

	r.remove();

	std::cout << "r = " << r << std::endl;

	for ( int i(0) ; i < 8 ; i++ )
		std::cout << "value = " << r.step_value() << std::endl;

	r.shuffle();

	std::cout << "r = " << r << std::endl;

	return 0;
	
}