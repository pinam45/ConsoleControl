# ConsoleControl

[![Build Status](https://travis-ci.org/pinam45/ConsoleControl.svg?branch=master)](https://travis-ci.org/pinam45/ConsoleControl)
![platform](https://img.shields.io/badge/platform-UNIX%20%7C%20Windows-lightgrey.svg)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://opensource.org/licenses/MIT)

ConsoleControl is a C, easy to use, library to control your console. 

This library, without any dependencies, supply useful functions to quickly made user interfaces and simple shapes drawings providing basic features (moving the cursor, colors...) and function to print shapes (line, rectangle, circle...) and UI elements (menu, messages...).

For a complete library to make complex console UI using terminfo/termcap go check [ncurses](http://invisible-island.net/ncurses/ncurses.html).

## Features

### Basic features

- set background / foreground color
- set and move the cursor position
- get console width / height
- save / restore cursor position
- position check functions
- clean the screen / the complete console
- non-blocking *getchar*
- inputs API
	- recognize special keys
	- check if an input is waiting
	- get input (key + **char**)

The library recognize the following keys:
Home, End, Page up, Page down, Up arrow, Down arrow, Left arrow, Right arrow, Backspace, Tab, Enter / Carriage return, Escape, Space / Space bar, Insert, Delete, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12

When a key is recognized, it is given with the associated **char**, if the key is not recognized, only the **char** is given (same behaviour as *getchar*)

### Shapes

The library provide function to draw:
- lines (simple char or pattern string)
- rectangles
- full rectangles
- circles

The lines and rectangles have special functions to print tables using
- ``-`` for horizontal lines
- ``|`` for vertical lines
- ``+`` for intersections

### UI elements

Each element is available in a *table* style and with colors:
- Multiple choices menu
	- Allow to choose an option from a string array
	- Default choice
	- Configurable behavior on *escape* key input

## Dependencies

No dependencies, the library only uses:
- The standard library
	- stdio.h
	- stdlib.h
	- stdbool.h
	- string.h
- On UNIX based systems: the system interface from [The Single UNIX Specification](http://www.unix.org/what_is_unix/single_unix_specification.html)
	- unistd.h
	- termios.h
	- fcntl.h
	- sys/ioctl.h
- On Windows systems: the windows API
	- windows.h

## Build

To build the lib you need a c11 compliant compiler.

A *CMakeLists.txt* is available, see [Running CMake](https://cmake.org/runningcmake/) for more information.

If you use **GCC** you can also use the *Makefile*:

To build the lib:

``$ make lib``

To build the lib and the examples:

``$ make all``

or just:

``$ make``

## Copyright

This work is under the MIT License

[Read the license file](LICENSE)
