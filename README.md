# c-ray-caastor by [@joey12198](https://github.com/joey121982/) | version 1.1

<p> a simple ray caster made in C++ using SDL2 </p>

## Prerequisites

Make sure you have SDL2 installed, as well as SDL Image.
To build this, we will use the make toolset.

## Building and running

The makefile contains the following commands:

* ```make clean``` - cleans everything inside the build directory (bins, copied assets, obj files)
* ```make run``` - runs the executable
* ```make copy-assets``` - copies assets from the project root directory (this is done automatically when building.)

To build, run ```make``` inside the project root directory.

## Features

- 3D / 2D view (map mode)
- toggleable fish eye fix
- toggleable shading on walls
- changeable distance for wall shading

## Controls

- ESC - toggle mouse lock
- WASD or Arrow Keys - movement and camera rotation
- F1 - fish-eye fix toggle
- F2 - shading toggle
- F3 - map mode toggle
- Page Up - Shading Distance increase
- Page Down - Shading Distance decrease

## TODO

- error handling
- fix different scaling rendering issue
- add map reader
