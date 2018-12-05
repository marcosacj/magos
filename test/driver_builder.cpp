#include <iostream>

#include "builder.h"

int main(){

	Maze m{8, 5};

	HashBuilder builder{ & m };

	builder.build_maze();

	return 0;
	
}