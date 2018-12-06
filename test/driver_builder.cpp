#include <iostream>

#include "render.h"
#include "builder.h"

int main(){

	Maze m{6, 4};

	Render r{ & m, 800, 600 };

	HashBuilder builder{ & m, & r };

	// builder.build_maze();

	while( not builder.is_built() )
		builder.build_step();

	return 0;
	
}