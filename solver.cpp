/*******************************
NAME           -N.R.Pussadeniya
INDEX NO       -19/ENG/082
MODULE         - CO2201
PRACTICAL	   -2
SUBMISSION DATE-29/06/2021
********************************/

#include <iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;


//Defining the function to solve the maze
bool mazeSolver(int x, int y,char **Maze,int size)
{
   
    Maze[y][x] = '#';
    if (Maze[y][x]=='B')
    {
        return true;
    }
    if (Maze[y-1][x]!='B'&&Maze[y][x+1]!='B'&&Maze[y][x-1]!='B'&&x > 0 && Maze[y][x- 1] == '0' && mazeSolver(x - 1, y,Maze,size))//recursion used to until found the way to solve maze
    {
        return true;
    }
    if (Maze[y-1][x]!='B'&&Maze[y][x+1]!='B'&&Maze[y][x-1]!='B'&&x < size-1 && Maze[y][x + 1] == '0' && mazeSolver(x + 1, y, Maze, size))
    {
        return true;
    }
    if (Maze[y-1][x]!='B'&&Maze[y][x+1]!='B'&&Maze[y][x-1]!='B'&&y > 0 && Maze[y - 1][x] == '0' && mazeSolver(x, y - 1, Maze, size))
    {
        return true;
    }
    if (Maze[y-1][x]!='B'&&Maze[y][x+1]!='B'&&Maze[y][x-1]!='B'&&y < size-1 && Maze[y + 1][x] == '0' && mazeSolver(x, y + 1, Maze, size))
    {
        return true;
    }
    
  if(Maze[y-1][x]!='B'&&Maze[y][x+1]!='B'&&Maze[y][x-1]!='B'){
  
      Maze[y][x] = '0';
    return false;
  
}
	
}


int main()
{
    ifstream read("Maze Puzzle.txt");
    string x;
    //Taking the size of the maze
    getline(read, x);
    read.close();
    x.erase(remove(x.begin(), x.end(), ' '), x.end());
    int size = x.length();
    char** maze = new char* [size];
    for (int i = 0; i < size; i++) {
        maze[i] = new char[size];
    }
    
    read.open("Maze Puzzle.txt");//get the maze input to dynamically allocated array
    for (int i = 0; i < size; i++) {
        getline(read, x);
        x.erase(remove(x.begin(), x.end(), ' '), x.end());
        for (int j = 0; j < size; j++) {
            maze[i][j] = x[j];
        }
    }
    
    //Finding the point A
    int initpositionX,initpositionY;
    initpositionY=size-2;
    for(int i=0;i<size;i++){
    	if(maze[size-1][i]=='A'){
    		initpositionX=i;
    		break;
		}
	}

  mazeSolver(initpositionX, initpositionY,maze,size);//call the solve function
 for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << maze[i][j] << " ";
        }
        cout << "\n";
    }
      ofstream write("Maze Solution.txt");//write the solved maze in to text file
    for(int i=0;i<size;i++){
   	for(int j=0;j<size;j++){
   	 write<<maze[i][j]<<" ";
	   }
	   write<<"\n";
   }
}
