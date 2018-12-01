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

	// create hash table
	hasht = new std::pair<int,int> [ m_size ];

	// auxiliar array to fill stack
	std::vector<Nat> aux( m_size );

	// fill auxiliar array from 0 to m_size
	std::iota( std::begin(aux), std::end(aux), 0 );

	// shuffle elements to be pushed to stack
	std::shuffle( std::begin(aux), std::end(aux), std::mt19937{ std::random_device{}() } );

	// fill hash table and stack with indexes
	for ( Nat i{0} ; i < m_size ; i++ ){
		hasht[i] = std::make_pair( i, i );
		shuffled.push( aux[i] );
	}

}

HashBuilder::~HashBuilder(){

	std::cout << "Destroying HashBuilder..." << std::endl;

	delete hasht;

}

void HashBuilder::build_maze(){

	std::cout << "Building maze..." << std::endl;

	srand( time( NULL ) );

	// choose a random cell (just top from stack)

	// choose a random wall until find a non-connected cell or had tried all walls

	Nat target_wall{ (Nat) std::pow( rand() % 4 , 2 ) };

	// if found a wall, knock down it and connect cells on hash table

	// if not found a wall, choose another cell (remember: shuffle)

}