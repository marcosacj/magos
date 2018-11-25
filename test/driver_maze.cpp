#include <iostream>

#include "maze.h"

typedef std::size_t Nat;

int main( int argc, char* argv[] ){

	Nat w{5}, h{8};

	Maze m{w, h};

	std::cout << m << std::endl << std::endl;

	m.knock_down(0, 1, Maze::Walls::Up);
	m.knock_down(0, 3, Maze::Walls::Bottom);
	m.knock_down(2, 0, Maze::Walls::Right);
	m.knock_down(2, 3, Maze::Walls::Left);

	m.set_state(w-1, h-1, Maze::States::Visited);
	m.set_state(w-2, h-2, Maze::States::Path);

	std::cout << m << std::endl << std::endl;

	// knock down border walls
	try {
		m.knock_down(1, 0, Maze::Walls::Up);
	} catch( std::invalid_argument & e) {
		std::cout << e.what() << std::endl;
	}

	try {
		m.knock_down(1, h-1, Maze::Walls::Bottom);
	} catch( std::invalid_argument & e) {
		std::cout << e.what() << std::endl;
	}

	try {
		m.knock_down(w-1, 3, Maze::Walls::Right);
	} catch( std::invalid_argument & e) {
		std::cout << e.what() << std::endl;
	}

	try {
		m.knock_down(0, 3, Maze::Walls::Left);
	} catch( std::invalid_argument & e) {
		std::cout << e.what() << std::endl;
	}

	// knock down outside matrix
	try {
		m.knock_down( 10, 2, Maze::Walls::Up);
	} catch( std::invalid_argument & e ){
		std::cout << e.what() << std::endl;
	}

	// knock down invalid wall
	try {
		m.knock_down( 0, 2, Maze::States::Untested);
	} catch( std::invalid_argument & e ){
		std::cout << e.what() << std::endl;
	}

	// set states
	try {
		m.set_state( 0, 2, Maze::Walls::Up);
	} catch( std::invalid_argument & e ){
		std::cout << e.what() << std::endl;
	}

	return 0;
	
}