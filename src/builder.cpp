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
	std::cout << "s = [ ";
	for ( Nat i{0} ; i < m_size ; i++ ){
		std::cout << aux[i] << " ";
		s.push( aux[i] );
		h->insert( i, i );
	}
	std::cout << "]" << std::endl;

}

HashBuilder::~HashBuilder(){

	std::cout << "Destroying HashBuilder..." << std::endl;

}

void HashBuilder::build_maze(){

	std::cout << "Building maze..." << std::endl;

	// while( h->size() > 1 ){

		// shuffle walls to pick one from last element
		std::vector<Nat> walls { Maze::Walls::Top, Maze::Walls::Right, Maze::Walls::Bottom, Maze::Walls::Left };
		std::shuffle( std::begin(walls), std::end(walls), std::mt19937{ std::random_device{}() } );

		// choose a random cell (index, from stack)
		Nat cell{ s.top() };

		// get coordinates of the cell
		Coord col{ to_column( cell ) };
		Coord lin{ to_line( cell ) };

		// choose a wall until pick one which is standing
		while( not m->hasWall( col , lin, walls.back() ) ){
			walls.pop_back();
		}

		// get neighbor cell
		Nat nbor;

		try{

			nbor = neighbor( cell , walls.back() );

		} catch( std::runtime_error & e ) {

			std::cout << e.what() << std::endl;
			walls.pop_back();

			try {

				nbor = neighbor( cell , walls.back() );

			} catch( std::runtime_error & e ) {

				std::cout << e.what() << std::endl;
				walls.pop_back();
				nbor = neighbor( cell , walls.back() );

			}
		}

		std::cout << "wall = " << walls.back() << std::endl;

		// std::cout << "cell = " << cell << " " << col             << " " << lin           << std::endl;
		// std::cout << "nbor = " << nbor << " " << to_column(nbor) << " " << to_line(nbor) << std::endl;

		// get keys
		Nat cell_k{ h->get_key(cell) };
		Nat nbor_k{ h->get_key(nbor) };

		std::cout << "cell = " << cell << " " << col             << " " << lin           << " " << cell_k << std::endl;
		std::cout << "nbor = " << nbor << " " << to_column(nbor) << " " << to_line(nbor) << " " << nbor_k << std::endl;
 
		// std::cout << "cell_k = " << cell_k << std::endl;
		// std::cout << "nbor_k = " << nbor_k << std::endl;

		if( not h->isEqualKey( cell, nbor ) ){

			std::cout << "merging nodes..." << std::endl;
			h->merge_by_key( cell_k , nbor_k );
			m->knock_down( col, lin , walls.back() );
			std::cout << *h << std::endl;
			s.pop();

		} else {
			std::cout << "equal keys..." << std::endl;
		}

		std::cout << "s = " << s.size() << std::endl;

		// std::cin.ignore();

	// }
	if( h->size() > 1 ){
		build_maze();
	}

}

Nat HashBuilder::neighbor( const Nat & index, const Nat & targetWall ){

	return neighbor( to_column( index ) , to_line( index ) , targetWall );

}

Nat HashBuilder::neighbor( const Coord & column, const Coord & line, const Nat & targetWall ){

	switch( targetWall ){

		case Maze::Walls::Top:
			if( line == 0 )
				throw std::runtime_error( "Can't get top neighbor, the cell is on border!" );
			else
				return to_index( column, line - 1 );
			break;

		case Maze::Walls::Right:
			if( column == m->get_wid() - 1 )
				throw std::runtime_error( "Can't get right neighbor, the cell is on border!" );
			else
				return to_index( column + 1, line );
			break;

		case Maze::Walls::Bottom:
			if( line == m->get_hei() - 1)
				throw std::runtime_error( "Can't get bottom neighbor, the cell is on border!" );
			else
				return to_index( column, line + 1 );
			break;

		case Maze::Walls::Left:
			if( column == 0 )
				throw std::runtime_error( "Can't get left neighbor, the cell is on border!" );
			else
				return to_index( column - 1 , line );
			break;

		default:
			throw std::runtime_error( "The choosen wall is not valid!" );

	}

}