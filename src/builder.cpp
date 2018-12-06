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

	// determine size of maze indexes
	Nat m_size{ m->get_wid() * m->get_hei() };

	// create the HashTable used during build process
	h = new HashTable< Nat, Nat > ( m_size );

	// set render object to draw maze image file
	r = param_r;

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

	// counter to file names
	Nat img_idx{ 0 };

	// draw initial version of maze
	r->draw_image( "./data/maze_" + std::to_string( img_idx++ ) + ".png" );

	while( h->size() > 1 ){

		h->show();

		// cells
		Nat cell, nbor;

		// keys
		Nat cell_k, nbor_k;

		// choose a random cell
		cell = s.top();

		// this key do not change during the iteration
		cell_k = h->get_key(cell);

		// possible target neighbors
		std::vector<Nat> targets;

		// shuffle walls
		std::vector<Nat> walls { Maze::Walls::Top, Maze::Walls::Right, Maze::Walls::Bottom, Maze::Walls::Left };
		std::shuffle( std::begin(walls), std::end(walls), std::mt19937{ std::random_device{}() } );

		// this loop fills the targets vector with possible neighbor cells
		for( auto i{ std::begin(walls) } ; i < std::end(walls) ; i++ ){

			try {
				nbor = neighbor( cell, *i );
			} catch ( std::runtime_error & e ){
				// mark wall as invalid because neighbor does not exist
				*i = 0;
				continue;
			}

			// get neighbor key
			nbor_k = h->get_key(nbor);

			if( h->isEqualKey( cell_k, nbor_k ) ){
				// mark wall as invalid because its not knockable
				*i = 0;
			} else {
				// this neighbor is valid
				targets.push_back( nbor );
			}

		}

		// erase invalid walls
		walls.erase( std::remove( walls.begin(), walls.end(), 0 ), walls.end() );

		// this loop operates on each target neighbor to link them on HashTable
		for ( auto nbor{ std::begin(targets) } ; nbor < std::end(targets) ; nbor++ ){

			nbor_k = h->get_key(*nbor);

			if( not h->isEqualKey( cell_k, nbor_k ) ){

				// get coordinates of the cell
				Coord col{ to_column( cell ) };
				Coord lin{ to_line( cell ) };

				// knock down the target wall
				m->knock_down( col, lin, walls[ std::distance( std::begin(targets) , nbor ) ] );

				// merge cells in HashTable
				h->merge_by_key( nbor_k , cell_k );

				// draw current step of building process
				// the set_state() methods should be removed on final version
				m->set_state( to_column(cell), to_line(cell), Maze::States::Visited );
				m->set_state( to_column(*nbor), to_line(*nbor), Maze::States::Path );
				r->draw_image( "./data/maze_" + std::to_string( img_idx++ ) + ".png" );
				m->set_state( to_column(cell), to_line(cell), Maze::States::Untested );
				m->set_state( to_column(*nbor), to_line(*nbor), Maze::States::Untested );

			}

		}

		// dircard current cell and go to next
		s.pop();

	}

	// show final hashes configuration
	h->show();

	// draw final version of maze
	r->draw_image( "./data/maze_" + std::to_string( img_idx++ ) + ".png" );

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