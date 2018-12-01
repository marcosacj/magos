## Introduction

This project implements the programming project MAGOS, which is composed of some subprojects:
Canvas, Maze, Render, Builder, Solver.

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

Note: `driver_canvas` sets relative output folder from where `canvas` (inside `run/`) is runned.
So, if you want result images be stored inside `data/`, you should run `canvas` from root directory
of the project.

Note: you should `mkdir data` before run `canvas`, otherwise the images will not be generated.

## Doxygen

A configuration file is set in the root directory, `doxygen.cfg`. If you want to generate yours, you can type:

```
$ doxygen -g [NAME]
```

Its recommended to custom the following tags: PROJECT\_NAME, OUTPUT\_DIRECTORY and EXTRACT\_PRIVATE.

## TODO

* On class Maze
	[*] introduce `valid_coord()` in `to_index()` and `get_cell()`, and implement exceptions
	[*] implement methods to get states of cells and walls
	[*] refactor order of bits: four first to be walls states
	[*] turn Cell type back to private
	[ ] refactor number of bits used, from 8 to 6
	[*] refactor method to reset states in `set_state()`

* On class Render
	[ ] document with details
	[*] refactor draw_cell() to use methods provided by Maze

* Implement MagosGame class

* Implement Builder classes
	* each class name will refer to the method used to build
	[ ] stub of class HashBuilder

* Implement Hash Table class
	[ ] implement exceptions ( key2undex, merge\_by\_key )