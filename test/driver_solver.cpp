#include <iostream>

#include "maze.h"
#include "canvas.h"
#include "render.h"
#include "builder.h"
#include "solver.h"

int main(){

	Maze m{ 10, 8 };

	Render r{ & m , 800 };

	HashBuilder b{ & m, & r };

	// b.build_maze();



	return 0;
	
}