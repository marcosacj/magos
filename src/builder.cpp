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

	std::cout << "s = [ ";
	std::copy( std::begin(aux) , std::end(aux) , std::ostream_iterator<Nat>( std::cout, " ") );
	std::cout << "]" << std::endl;

}

HashBuilder::~HashBuilder(){

	std::cout << "Destroying HashBuilder..." << std::endl;

}

void HashBuilder::build_maze(){

	std::cout << "Building maze..." << std::endl;

	// while( h->size() > 14 ){

	// cells
	Nat cell, nbor;

	// keys
	Nat cell_k, nbor_k;

	// choose a random cell
	cell = s.top();

	// get coordinates of the cell
	// Coord col{ to_column( cell ) };
	// Coord lin{ to_line( cell ) };

	// possible target neighbors
	std::vector<Nat> targets;

	// shuffle walls
	std::vector<Nat> walls { Maze::Walls::Top, Maze::Walls::Right, Maze::Walls::Bottom, Maze::Walls::Left };
	std::shuffle( std::begin(walls), std::end(walls), std::mt19937{ std::random_device{}() } );

	// for ( int i{ std::distance( std::begin(walls), std::end(walls) ) } ; i > 0  ; i++ ){
	for( auto i{ std::end(walls) - 1 } ; i > std::begin(walls) - 1 ; i-- ){

		try {
			nbor = neighbor( cell, *i );
		} catch ( std::runtime_error & e ){
			std::cout << e.what() << std::endl;
			walls.erase(i);
			continue;
		}

		// get keys
		cell_k = h->get_key(cell);
		nbor_k = h->get_key(nbor);

		if( h->isEqualKey( cell_k, nbor_k ) ){
			std::cout << cell << " and " << nbor << " has equal keys..." << std::endl;
		} else {
			targets.push_back( nbor );
		}

	}

	std::cout << "cell = " << to_column(cell) << " " << to_line(cell) << std::endl;

	std::cout << "walls =   [ ";
	for ( Nat i(0) ; i < walls.size() ; i++ ){
		switch( walls[i] ){
			case Maze::Walls::Top:
				std::cout << "t ";
				break;
			case Maze::Walls::Right:
				std::cout << "r ";
				break;
			case Maze::Walls::Bottom:
				std::cout << "b ";
				break;
			case Maze::Walls::Left:
				std::cout << "l ";
				break;
			default:
				std::cout << "x ";
		}
	}
	// std::copy( std::begin(walls) , std::end(walls) , std::ostream_iterator<Nat>( std::cout, " ") );
	std::cout << "]" << std::endl;

	std::cout << "targets = [ ";
	std::copy( std::begin(targets) , std::end(targets) , std::ostream_iterator<Nat>( std::cout, " ") );
	std::cout << "]" << std::endl;
	
	// if there is linkable neighbors
	if( targets.size() > 0 ){
		// knock down the target wall
		m->knock_down( to_column(cell), to_line(cell), walls.back() );

		std::cout << "knock down..." << std::endl;

		// merge cells in HashTable

	}

	// dircard currente cell and go to next
	s.pop();

	// }

/*

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
			// std::cout << *h << std::endl;
			h->show();
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

*/

}

bool HashBuilder::valid_coord( const Coord & column, const Coord & line ) const {

	if( column >= m->get_wid() or column < 0 or line >= m->get_hei() or line < 0 )
		return false;
	else
		return true;

}

Nat HashBuilder::neighbor( const Nat & index, const Nat & targetWall ){

	return neighbor( to_column( index ) , to_line( index ) , targetWall );

}

Nat HashBuilder::neighbor( const Coord & column, const Coord & line, const Nat & targetWall ){

	if( not valid_coord( column, line ) ){
		throw std::invalid_argument("Coordinates/index is outside the maze!");
	}

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