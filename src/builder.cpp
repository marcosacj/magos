#include <algorithm> // std::shuffle
#include <numeric> // std::iota
#include <vector> // std::vector
#include <iterator> // std::begin, std::end
#include <random> // std::random_device, std::mt19937

#include "builder.h"

HashBuilder::HashBuilder( Maze * target ){

	std::cout << "Constructing HashBuilder..." << std::endl;

	// set builder pointer to target maze
	m = target;

	// determine size of maze indexes
	Nat m_size{ m->get_wid() * m->get_hei() };

	// create the HashTable used during build process
	h = new HashTable< Nat, Nat > ( m_size );

	// auxiliar array to fill stack
	std::vector<Nat> aux( m_size );

	// fill auxiliar array from 0 to m_size
	std::iota( std::begin(aux), std::end(aux), 0 );

	// shuffle elements to be pushed to stack
	std::shuffle( std::begin(aux), std::end(aux), std::mt19937{ std::random_device{}() } );

	// fill hash table and stack
	for ( Nat i{0} ; i < m_size ; i++ ){
		s.push( aux[i] );
		h->insert( i, i );
	}

}

HashBuilder::~HashBuilder(){

	std::cout << "Destroying HashBuilder..." << std::endl;

}

void HashBuilder::build_maze(){

	std::cout << "Building maze..." << std::endl;

	// srand( time( NULL ) );

	// choose a random cell (just top from stack)

	// choose a random wall until find a non-connected cell or had tried all walls

	std::vector<Nat> walls { Maze::Walls::Top, Maze::Walls::Right, Maze::Walls::Bottom, Maze::Walls::Left };
	std::shuffle( std::begin(walls), std::end(walls), std::mt19937{ std::random_device{}() } );

	Coord col{ to_column( s.top() ) };
	Coord lin{ to_line( s.top() ) };

	while( not m->hasWall( col , lin, walls.back() ) ){
		walls.pop_back();
	}

	// std::cout << "index = " << s.top() << std::endl;
	// std::cout << "col = " << col << std::endl;
	// std::cout << "lin = " << lin << std::endl;
	// std::cout << "wall = " << walls.back() << std::endl;

	Nat nbor{ neighbor( col, lin, walls.back() ) };

	// std::cout << "nbor = " << nbor << std::endl;
	// std::cout << "col = " << to_column(nbor) << std::endl;
	// std::cout << "lin = " << to_line(nbor) << std::endl;

	// get neighbor cell

	// if found a wall, knock down it and connect cells on hash table

	// if not found a wall, choose another cell (remember: shuffle)

}

Nat HashBuilder::neighbor( const Nat & index, const Nat & targetWall ){

	return neighbor( to_column( index ) , to_line( index ) , targetWall );

}

Nat HashBuilder::neighbor( const Coord & column, const Coord & line, const Nat & targetWall ){

	switch( targetWall ){

		case Maze::Walls::Top:
			return to_index( column, line - 1 );
			break;

		case Maze::Walls::Right:
			return to_index( column + 1, line );
			break;

		case Maze::Walls::Bottom:
			return to_index( column, line + 1 );
			break;

		case Maze::Walls::Left:
			return to_index( column - 1 , line );
			break;

		default:
			throw std::runtime_error( "Something very wrong happened..." );

	}

}