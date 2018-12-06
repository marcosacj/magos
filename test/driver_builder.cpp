#include <iostream>

#include "render.h"
#include "builder.h"

int main(){

	Maze m{8, 5};

	Render r{ & m, 800, 600 };

	HashBuilder builder{ & m, & r };

	builder.build_maze();

	return 0;
	
}