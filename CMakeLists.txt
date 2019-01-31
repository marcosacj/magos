# MAIN CONFIGURATIONS =============================

cmake_minimum_required( VERSION 3.5 )
project( magos )

add_compile_options( -Wall -std=c++11 -g )
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/run )
include_directories( include helpers )

# EXECUTABLES DEFINITION ==========================

# Tests Canvas class
# creates three test images
add_executable( canvas
	src/canvas.cpp
	test/driver_canvas.cpp
)

# Tests Maze class
# constructs and prints a maze
# tests exceptions
add_executable( maze
	src/maze.cpp
	test/driver_maze.cpp
)

# Tests Roullete class
add_executable( roullete
	test/driver_roullete.cpp
)

# Tests Builder class
# this builder uses Hash Table strategy
# produces images to data folder
add_executable( builder
	src/canvas.cpp
	src/maze.cpp
	src/render.cpp
	src/builder.cpp
	test/driver_builder.cpp
)

# Testes Render class
# produces three images to data folder
# prints detailed informations about maze and render
# testes knocked-down walls and colored cells
add_executable( render
	src/canvas.cpp
	src/maze.cpp
	src/render.cpp
	test/driver_render.cpp
)

# Tests helper HashTable class
# prints the process of joining the keys
add_executable( hash
	test/driver_hash.cpp
)

# Tests Solver class
# this solver uses Backtracking strategy
# produces images to data folder
add_executable( solver
	src/maze.cpp
	src/canvas.cpp
	src/render.cpp
	src/builder.cpp
	src/solver.cpp
	test/driver_solver.cpp
)

# Tests Wallfoller class
# produces images to data folder
add_executable( wallfollower
	src/maze.cpp
	src/canvas.cpp
	src/render.cpp
	src/builder.cpp
	src/wallf.cpp
	test/driver_wallf.cpp
)

# The de-facto game executable
# uses the Backtracking solver
add_executable( magos
	src/canvas.cpp
	src/maze.cpp
	src/render.cpp
	src/builder.cpp
	src/solver.cpp
	src/magos.cpp
	test/driver_magos.cpp
)