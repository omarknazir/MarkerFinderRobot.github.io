# README

## Robot Movement Program

### Description

 This C program simulates the movement of a robot in a grid-based environment. The robot can navigate through empty spaces, pick up markers, and return them to a designated home square.
 The grid contains home squares, immovable blocks, and markers.
 The robot moves forward, turns right, and turns left based on its current facing direction. 
 The program uses simple graphics to visualize the robot's movements. 
 However, since the robot is not allowed to map the grid it does not use a pathfinding algorithm to find the markers rather uses random movement

### Completed Features

- Robot movement: The robot can move forward, turn right, and turn left.
- Marker handling: The robot can pick up markers and drop them at a designated home square.
- Movement storage: robot stores moves in a fixed size large array(due to random nature of moves) of chars(to keep file size small)
- Grid setup: The program initializes a grid with home squares and immovable blocks.
- Completed till stage 6

### Compilation and Execution

To compile and run the program, follow these steps:

1. Ensure you have the necessary libraries installed. This program uses the "graphics.h" library.

2. Compile the program using this command on the terminal, make sure graphics.c and graphics.h files are in same folder

   gcc ass.c graphics.c
   
*use clang instead of gcc if using clang compiler

3. Run the compiled program using this command on the terminal:

   ./a  <x> <y> <direction> | java -jar drawapp-3.0.jar
   

   Replace `<x>`, `<y>`, and `<direction>` with the initial position(x,y) and direction of the robot.
   Keep in mind the grid starts at (100,100) in the window, with each square cell having length 40px
   Direction can have values 1,2,3,4 corresponding to North, South, West , East respectively

### Example


./a 100 100 1

The above command spawns the robot and home square on the first top left grid cell(100,100) facing North


### Notes

- Ensure that the graphics.h, graphics.c , and robot.png file are in the same directory as the program(ass.c) file
- The program uses random movements for the robot.
- The robot picks up markers when it reaches their location and drops them at the designated home square using a stack structure containing previous moves.
