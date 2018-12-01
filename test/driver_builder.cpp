#include <iostream>

#include "builder.h"

int main(){

	Maze m{15, 10};

	HashBuilder builder{ & m };

	builder.build_maze();

	return 0;
	
}