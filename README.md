# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2 Images
  * A simple library to load images of various formats as SDL surfaces. Install using `sudo apt-get install libsdl2-image-dev`
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

# Additional information for Capstone

This program additionally uses the sdl2 image library. See [Dependencies for Running Locally](#dependencies-for-running-locally) above.

# New Features:

## Eagle
It is widely known that eagles eat snakes, so I added an eagle to the game that chases the snake and tries to eat it! The eagle follows the snake, and on contact, the game terminates with the message "Eagle caught the snake!". The speed of the eagle is relative to that of the snake, and this value changes with different difficulty levels. The renderer loads a nice image of an eagle which moves across the screen to try and catch the snake.

## Difficulty levels
Three difficulty levels are added to the game: Easy, Medium, and Hard. The difficulty level changes the relative speed of the eagle, making it easier or harder for the eagle to catch the snake. You can change the difficulty by pressing the left and right bracket keys "[" and "]". Easy = 0, Medium = 1, and Hard = 2.

## Extra food
I added an extra option that spawns extra food every 10 seconds. You have 3 seconds to catch the extra food and obtain an additional +5 points! After that, you have to wait 7 seconds before new extra food spawns randomly and you can try again.

# Compiling and Testing
The program compiles and runs the same way as it is described in [Basic Build Instructions](#basic-build-instructions).

# Project Contributions Related to Rubrics

## Loops, Functions, I/O:
### 2.1: The project demonstrates an understanding of C++ functions and control structures:
The project uses numerous control structures throughout the program to control the flow of the game.
### 2.2: File I/O:
The program loads an image "eagle_small.png" as an SDL_Surface and renders it to the screen.

### 2.3: The project accepts user input and processes the input:
The program handles additional keyboard inputs. Namely the bracket keys "[" and "]" to change the difficulty of the game.

### 2.4: Constructor Argument Change:
In the renderer class, the argument of Renderer has been changed to `const Snake&` to introduce an immutable variable. Also, the eagle class uses getters and setters for its private members.

## Object-oriented programming:
### 3.1: Access Specifiers:
The snake and eagle classes now use appropriate access specifiers for class members.

### 3.2: Class constructors utilize member initialization lists:
The eagle class uses a member initialization lists to initializes the class.

### 3.3: Classes abstract implementation details from their interfaces:
Member functions do not change the program state in undocumented ways. Also, the Snake class is reorganized.

## Memory Management:
### 4.1: The project makes use of references in function declarations:
References are used all around the program to pass variables by reference.

### 4.2: Proper Use of Destructors:
The project uses destructors properly.

### 4.6: The project uses smart pointers instead of raw pointers:
For example, the eagle class has a shared pointer to the snake and uses that to chase the snake.
## Concurrency:

### 5.1: The project uses multithreading:
The project uses multithreading to spawn extra food on a timer.

### 5.3: A mutex or lock is used in the project:
Lock type unique_lock is used to protect, for example, the extra_food and extra_food_placed variables.

### 5.4: A condition variable is used in the project:
A condition variable is used to notify the thread that an extra food is placed.
