#include "graphics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// in some places in the code, lines like "(x-100)/40" or "i*40 + 100" are there to conevrt pixel coords to grid coords or vice versa

const int width = 600;
const int height = 600;
const int waitTime = 300;
const int squareSize = 40;
const int moveDistance = 40;
const int grid_width = 400;
const int boxes = 10;
const int spacing = grid_width/boxes;

char grid[10][10]; // 0:empty square, 1:home square, 2:immovable block
int marker[2][3] = {{100, 180, 0},{300, 300,0}}; // {x coord, y coord, picked up?(0 = False, 1 = True, 2 = at_home)} 

struct object
{
  int facing; // can have values 1,2,3,4 corresponding to North, South, West , East
  int x;
  int y;
  char moves[2000]; //create a stack using fixed size array | moves stored as: forward=5, right=6, left=7 
  int last_move; //null pointer would have -1 value
};

struct object robot;

void create_robot(int x, int y, int facing)// problem free
{
  robot.last_move = -1;
  robot.facing = facing;
  robot.x = x;
  robot.y = y;
  for (int i = 0; i < 100; i++)
  {robot.moves[i] = 0;}
  grid[(x-100)/40][(y-100)/40] = 1;
}

void push_move(char move)
{
  if(robot.last_move == -1)
  { robot.last_move = 0;}
  else
  {robot.last_move += 1;}
  robot.moves[robot.last_move] = move;
}

char pop_move()
{
  char temp;
  if(robot.last_move == -1)
  {
    temp = 0;
  }
  else
  {
    temp = robot.moves[robot.last_move];
    robot.moves[robot.last_move] = 0;
    robot.last_move -= 1;
  }
  return temp;
}

int can_move_forward() // cause problem with robot location
{
  if((robot.facing == 1 && (grid[(robot.x-100)/40][(robot.y-100)/40-1] == 2 || robot.y == 100))||
     (robot.facing == 2 && (grid[(robot.x-100)/40][(robot.y-100)/40+1] == 2 || robot.y == 460))|| 
     (robot.facing == 3 && (grid[(robot.x-100)/40-1][(robot.y-100)/40] == 2 || robot.x == 100))||
     (robot.facing == 4 && (grid[(robot.x-100)/40+1][(robot.y-100)/40] == 2 || robot.x == 460)))
  {return 0;}
  else
  {return 1;}
}

void right()
{
  switch (robot.facing)
  {
  case 1:// n to e
    robot.facing = 4;
    break;

  case 4: // e to s
    robot.facing = 2;
    break;
  
  case 2: // s to w
    robot.facing = 3;
    break;

  case 3: // w to n
    robot.facing = 1;
    break;
  }
}

void left()
{
   switch (robot.facing)
  {
  case 1: // n to w
    robot.facing = 3;
    break;

  case 4: // e to n
    robot.facing = 1;
    break;
  
  case 2: // s to e
    robot.facing = 4;
    break;

  case 3: // w to s
    robot.facing = 2;
    break;
  }
}

int at_marker()
{
  int on_a_marker = -1;
  for(int i=0; i<sizeof(marker)/12; i++)
  {
  if(((marker[i][0]==robot.x && marker[i][1]==robot.y)|| marker[i][2] == 1) && marker[i][2] != 2)
  {on_a_marker = i;}
  }
  return on_a_marker; // on_a_marker is boolean along with index of marker
}
// after creating marker
void pickup_marker(int index) // picks up marker by linking robot and marker coords
{
  marker[index][2] = 1;
  marker[index][0] = robot.x;
  marker[index][1] = robot.y;
}

int at_home()
{
  if(grid[(robot.x-100)/40][(robot.y-100)/40] == 1) // check if home by seeing if 1 in grid
  {
    return 1;
    char del_move =pop_move();
    while (del_move != 0) //empty stack to restore moves from home
    {char del_move = pop_move();}
  }
  else
  {return 0;}
}

void drop_marker(int index)
{
   marker[index][2] = 2;
   int home_status = at_home();
   if(home_status == 1)
   {marker[index][2] = 2;}
}

int is_carrying_marker()
{
  int carry_status = 0;
  for(int i =0; i<sizeof(marker)/12; i++)
  {
   if(marker[i][0]==robot.x && marker[i][1]==robot.y && marker[i][2] == 1)
   {carry_status = 1;}
  }
  return carry_status;
}



void forward()   // update direction of robot based on direction
{
   if(robot.facing== 1)
   {robot.y -= spacing;}
   if(robot.facing == 2)
   {robot.y += spacing;}
   if(robot.facing == 3)
   {robot.x -= spacing;}
   if(robot.facing == 4)
   {robot.x += spacing;}
}

void reverse_mover(char move)
{
  switch (move)
  {
  case 5: //forward
    forward();
    break;
  
  case 6: //right
    left();
    break;
  
  case 7: //left
    right();
    break;
  }
}

void draw_background()
{
  int x= 100;
  int y= 100;
  background(); 
  clear();
  //filling with home square and markers and blocks
  for(int i = 0; i<sizeof(marker)/12; i++) // drawing markers
      {
        setColour(gray);
        fillRect(marker[i][0],marker[i][1], squareSize,squareSize);
      }
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      if(grid[i][j]==1) // drawing home square
      {
        setColour(red);
        fillRect(i*40 + 100,j*40 +100, squareSize,squareSize);
      }
      if(grid[i][j]==2) // drawing immovable block
      {
        setColour(black);
        fillRect(i*40 + 100,j*40 +100, squareSize,squareSize);
      }
    }
  }
  setColour(black);
  drawRect(x,y, grid_width,grid_width);
  for(int line = 0; line<boxes ;line++)
  {
    drawLine(x, y,x+400,y);
    y += spacing;
  }
  y = 100;
  for(int line = 0; line<boxes ;line++)
    {
      drawLine(x, y,x,y+400);
      x += spacing;
    }
}

void  draw_foreground()// Update the foreground layer to display the square(image) in a new position
{
  foreground();
  clear();
  setRGBColour(51,77,92);
  char *file = "robot.png";
  fillOval(robot.x, robot.y, squareSize,squareSize);//incase pic not display
  displayImage(file,robot.x,robot.y); // call erno here incase file not works
}

void main(int argc, char **argv) //input x,y,facing from command line
{
  for(int i = 0; i < 10; i++) // initialize grid
  {
    for(int j = 0; j < 10; j++)
    {grid[i][j] = 0 ;}
  }
  grid[1][0] = 2; //putting in blocks in the grid
  grid[7][8] = 2;
  create_robot(atoi(argv[1]), atoi(argv[2]),atoi(argv[3])); // convert ascii arguments to int eq numbers
  setWindowSize(width, height);

  //start a loop that terminates when all markers found
  int found = 0;
  while (found == 0)
  //for(int i = 0; i < 1000; i++)
  {
    draw_background();
    draw_foreground();
    found = 1;
    int marker_index = at_marker(); // getting status or index of active marker
    int reversed; //boolean to ensure that direction fliping occurs once reverse movement starts
    
    if(marker[marker_index][2] != 1) //if not holding marker
    {
      if (can_move_forward()) 
      { //use random movement instead like a robot vaccum and store movement
        forward(); 
        push_move(5);
        if(rand()%2 ==1)
        {
          right();
          push_move(6);
        }
        else
        {
          left();
          push_move(7);
        }
      }
      else 
      {
        right();
        push_move(6);
      }
      reversed = 0;
    }
    else //if a marker found reverse movement
    {
      if(reversed == 0)
      {
        right();
        right();
        reversed = 1;
      }
      reverse_mover(pop_move()); // pop elements of move array and move accordingly
    }
    
    if((marker_index != -1 && marker[marker_index][2] != 2)) // links marker and robot coords, if not at home and at marker
    {pickup_marker(marker_index);}

    if(at_home() && marker[marker_index][2] ==1) //drops marker at home
    {drop_marker(marker_index);}
    
    for(int i=0; i<sizeof(marker)/12; i++) //checking all markers home
    {
      if(marker[i][2] != 2)
      {found = 0;}
    }
    sleep(waitTime);
  }
  draw_background();
  draw_foreground();
}