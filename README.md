# SlowTree

SlowTree is a 2D top-down vegetation sprite generator.

## Requirements

SlowTree is written in C++11 so you need a C++11 compiler like [Clang](http://clang.llvm.org/) or [GCC](http://gcc.gnu.org/).

SlowTree also needs external libraries:

* [Cairo](http://cairographics.org/)

## Build and install

You can download the sources directly from github:

    git clone https://github.com/jube/slowtree.git

Then you have to use [CMake](http://www.cmake.org/) to build the project:

    cd slowtree
    mkdir build
    cd build
    cmake ../src
    make

Finally, you can install the files (you may need root permissions):

    make install

## Authors

- Julien Bernard, julien dot bernard at univ dash fcomte dot fr

## Copyright

This tool is [free software](http://www.gnu.org/philosophy/free-sw.html) and is distributed under the [GPLv3 licence](http://www.gnu.org/copyleft/gpl-3.0.html).
