#include <iostream>

#include "builder.h"
#include "solver.h"

int main(){

	Maze m { 8, 5 };

	Render r { & m , 800 };

	HashBuilder b { & m, & r };

	b.build_maze();

	Solver s { & m, & r };

	s.solve_maze();

	return 0;
	
}