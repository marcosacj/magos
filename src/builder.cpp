#include <algorithm> // std::shuffle
#include <numeric> // std::iota
#include <vector> // std::vector
#include <iterator> // std::begin, std::end
#include <random> // std::random_device, std::mt19937

#include "builder.h"

HashBuilder::HashBuilder( Maze * param_m, Render * param_r ){

	std::cout << "Constructing HashBuilder..." << std::endl;

	// set builder pointer to target maze
	m = param_m;

	// set render object to draw maze image file
	r = param_r;

	// determine size of maze indexes
	Nat m_size{ m->get_wid() * m->get_hei() };

	// create the HashTable used during build process
	h = new HashTable< Nat, Nat > ( m_size );

	for ( Nat i{0} ; i < m_size ; i++ ){
		c.add( i );
		h->insert( i, i );
	}

	c.shuffle();

}

HashBuilder::~HashBuilder( void ){

	std::cout << "Destroying HashBuilder..." << std::endl;

}

void HashBuilder::build_maze( void ){

	std::cout << "Building maze..." << std::endl;

	std::string build_path { "./data/building_" };

	// counter to file names
	Nat img_idx{ 0 };

	// draw initial version of maze
	r->draw_image( build_path + std::to_string( img_idx++ ) + ".png" );

	while( not is_built() ){

		if( build_step() ){

			// draw currente version of maze
			r->draw_image( build_path + std::to_string( img_idx++ ) + ".png" );

		}

	}

	// show final hashes configuration
	// h->show();

	std::cout << "Maze is built..." << std::endl;

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

bool HashBuilder::build_step( void ){

	// h->show();

	// cells
	Nat cell, nbor;

	// keys
	Nat cell_k, nbor_k;

	// choose a random cell
	cell = c.step_value();

	// this key do not change during the iteration
	cell_k = h->get_key(cell);

	// possible target neighbors
	std::vector<Nat> target_neighbor;

	// shuffle walls
	std::vector<Nat> target_wall { Maze::Walls::Top, Maze::Walls::Right, Maze::Walls::Bottom, Maze::Walls::Left };
	std::shuffle( std::begin(target_wall), std::end(target_wall), std::mt19937{ std::random_device{}() } );

	// this loop fills the targets vector with possible neighbor cells
	for( auto w{ std::begin(target_wall) } ; w < std::end(target_wall) ; w++ ){

		try {
			nbor = neighbor( cell, *w );
		} catch ( std::runtime_error & e ){
			// mark wall as invalid because neighbor does not exist
			*w = 0;
			continue;
		}

		// get neighbor key
		nbor_k = h->get_key(nbor);

		if( h->isEqualKey( cell_k, nbor_k ) ){
			// mark wall as invalid because its not knockable
			*w = 0;
		} else {
			// this neighbor is valid
			target_neighbor.push_back( nbor );
		}

	}

	// erase invalid walls
	target_wall.erase( std::remove( target_wall.begin(), target_wall.end(), 0 ), target_wall.end() );

	// if there is at least one neighbor to be linked, link it
	if( target_wall.size() ){

		nbor = target_neighbor.front();
		
		nbor_k = h->get_key(nbor);

		if( not h->isEqualKey( cell_k, nbor_k ) ){

			// get coordinates of the cell
			Coord col{ to_column( cell ) };
			Coord lin{ to_line( cell ) };

			// knock down the target wall
			m->knock_down( col, lin, target_wall.front() );

			// merge cells in HashTable
			h->merge_by_key( nbor_k , cell_k );

			return true;

		}

	}

	return false;

}