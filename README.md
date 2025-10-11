# TrainingCounter
Simple console program for Linux and Windows to count the remaining workouts with trainer in the gym. This program uses C++, CMake

To build this program you need:

 * OC Linux or Windows on your computer;
 * C++ compiler with C++17 standard support
 * CMake version 3.8 or greater
 * Any supported generator, like "Make", "Ninja" for Linux and "Visual Studio" for Windows.

Build:

1) Clone this repository in any place you want;
2) Go to cloned repository;
3) Enter:

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cmake --install .
```
