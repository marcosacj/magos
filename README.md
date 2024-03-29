## Introduction

This project implements the programming project MAGOS,
which means Maze GeneratOr and Solver and is composed of some subprojects:
Canvas, Maze, Render, Builder, Solver.

The project is a perfect maze generator and solver.

A perfect maze is a maze where each location (cell) is reachable from any other one,
and where there is one, and only one, path connecting each pair of locations.

## Authorship

Marcos Antonio Cavalcanti Junior

marcos.acj@outlook.com

## Structure

The folder and files structure is the following:

* `include` folder contains the headers of classes

* `helpers` folder contains other resources useful to implementation

* `src` folder contains the implementation of the classes

* `test` folder contains codes to test classes and other codes

* `build` folder will contain compilation files generated with help of CMake

* `run` folder will contain the executables generated

* `data` folder will contain data used by the project, like images, configurations, inputs, ouputs, etc

	* `builder` folder will contain imagens generated by the builder application
	* `solver` folder will contain imagens generated by the solver application

## Compilation

You can go to root directory of the project and:

```
$ mkdir build
$ cd build/
$ cmake ..
$ make
```

Or, if you would like to do all from root:

```
$ mkdir build
$ cmake -H. -Bbuild
$ make -C build/ --no-print-directory
```

## Execution

All executables will be placed in `run/` folder. So, you can run typing:

```
$ ./run/[EXECUTABLE]
```

These are the main executables:

* `builder` builds a new maze using Hash Table strategy
* `solver` solves a maze (currently, using the Backtracking strategy)
* `magos` performs the game it self building and solving a maze

More details about each executables can be found at `CMakeLists.txt` file.

## Doxygen

A configuration file is set in the root directory, `doxygen.cfg`.
If you want to generate yours, you can type:

```
$ doxygen -g [NAME]
```

Its recommended to custom the following tags: PROJECT_NAME, OUTPUT_DIRECTORY and EXTRACT_PRIVATE.

To generate the files containing the documentation, type:

```
$ doxygen doxygen.cfg
```

## Video

You can use `ffmpeg` to make video files of building and solving processes. For example:

```
ffmpeg -framerate 10 -i building_%06d.png -c:v libx264 -r 30 -pix_fmt yuv420p  -vf "pad=ceil(iw/2)*2:ceil(ih/2)*2" builder.mp4

ffmpeg -framerate 10 -i solving_%06d.png -c:v libx264 -r 30 -pix_fmt yuv420p  -vf "pad=ceil(iw/2)*2:ceil(ih/2)*2" solver.mp4
```

## TODO

* On class `Maze`

	- [x] introduce `valid_coord()` in `to_index()` and `get_cell()`, and implement exceptions
	- [x] implement methods to get states of cells and walls
	- [x] refactor order of bits: four first to be walls states
	- [x] turn Cell type back to private
	- [x] refactor method to reset states in `set_state()`
	- [ ] refactor number of bits used, from 8 to 6

* On class `Render`

	- [x] refactor `draw_cell()` to use methods provided by Maze
	- [x] document with details
	- [x] draw cell and path of solution

* On class `MagosGame`

	- [x] prevent executable to run without parameters

* Implement `Builder` and `Solver` classes (each class name will refer to the method used)

	- [x] class `HashBuilder`
	- [x] class `Solver`

* On class `HashBuilder`

	- [x] introduce render object
	- [x] save snapshots of maze
	- [x] remove internal render and receive it by parameter
	- [x] create `step()` method
	- [ ] rename class `roulette` and port it to inside `HashBuilder`
	- [ ] implement Hash Table as a `std::vector` (internal class)
	- [ ] number format in file names

* On class `HashTable`

	- [x] implement exceptions ( `key2index()`, `merge_by_key()` )
	- [x] document with details
	- [x] separate `build_maze()` to `build_maze()` + `build_step()` (use class `Roulette`?)
	- [ ] delete statement on destructor

* On class `Solver`

	- [x] comment with details
	- [ ] number format in file names

* General/Missing

	- [x] improve comments
	- [x] implement `delete` statements
	- [x] update `draw_cell()`
	- [x] number format in file names
	- [ ] comment Magos Game class