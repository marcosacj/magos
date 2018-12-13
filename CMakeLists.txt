# MAIN CONFIGURATIONS =============================

cmake_minimum_required( VERSION 3.5 )
project( magos )

add_compile_options( -Wall -std=c++11 -g )
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/run )
include_directories( include helpers )

# EXECUTABLES DEFINITION ==========================

add_executable( canvas
	src/canvas.cpp
	test/driver_canvas.cpp
)

add_executable( maze
	src/maze.cpp
	test/driver_maze.cpp
)

add_executable( roullete
	test/driver_roullete.cpp
)

add_executable( builder
	src/canvas.cpp
	src/maze.cpp
	src/render.cpp
	src/builder.cpp
	test/driver_builder.cpp
)

add_executable( render
	src/canvas.cpp
	src/maze.cpp
	src/render.cpp
	test/driver_render.cpp
)

add_executable( hash
	test/driver_hash.cpp
)

add_executable( solver
	src/maze.cpp
	src/canvas.cpp
	src/render.cpp
	src/builder.cpp
	src/solver.cpp
	test/driver_solver.cpp
)

add_executable( wallfollower
	src/maze.cpp
	src/canvas.cpp
	src/render.cpp
	src/builder.cpp
	src/wallf.cpp
	test/driver_wallf.cpp
)

add_executable( magos
	src/canvas.cpp
	src/maze.cpp
	src/render.cpp
	src/builder.cpp
	src/solver.cpp
	src/magos.cpp
	test/driver_magos.cpp
)