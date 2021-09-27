/*******************************
NAME           -N.R.Pussadeniya
INDEX NO       -19/ENG/082
MODULE         - CO2201
PRACTICAL	   -2
SUBMISSION DATE-29/06/2021
********************************/
#include<iostream>
#include<cstdlib>
#include<stack>
#include<fstream>

using namespace std;


//Defining the function to move up and down
int moveUpAndDown(int pathway, int y) {
    if (pathway == 0)
        return y - 1;
    else if (pathway == 1)
        return y + 1;
    else
        return y;
}

//Defining the function to move  left and right
int moveSides(int pathway, int x) {
    if (pathway ==2)
        return x + 1;
    else if (pathway == 3)
        return x - 1;
    else
        return x;
}


//Defining the function to availability of the cell to visit
bool checkingPathway(int x, int y, int pathway, char** grid, int size) {
	x=	moveSides(pathway, x);
	y=	moveUpAndDown(pathway, y);
    if (grid[y][x] == '0' || x >= (size - 1) || x <= 0 || y <= 0 || y >= (size - 1)) {
        return false;
    }
    if (pathway == 0) {
        if (grid[y][x - 1] != '0' && grid[y - 1][x] != '0' && grid[y][x + 1] != '0' && grid[y - 1][x - 1] != '0' && grid[y - 1][x + 1] != '0') {
            return true;
        }
    }
    if (pathway == 1) {
        if (grid[y][x - 1] != '0' && grid[y + 1][x] != '0' && grid[y][x + 1] != '0' && grid[y + 1][x - 1] != '0' && grid[y + 1][x + 1] != '0') {
            return true;
        }
    }
    if (pathway == 2) {
        if (grid[y][x + 1] != '0' && grid[y - 1][x] != '0' && grid[y + 1][x] != '0' && grid[y - 1][x + 1] != '0' && grid[y + 1][x + 1] != '0') {
            return true;
        }
    }
    if (pathway == 3) {
        if (grid[y][x - 1] != '0' && grid[y - 1][x] != '0' && grid[y + 1][x] != '0' && grid[y - 1][x - 1] != '0' && grid[y + 1][x - 1] != '0') {
            return true;
        }
    }
    return false;
}


int main() {
    int size,possibleWays;
    int startingPontX,startingPontY,endingPointX,endingPointY;
    cout << "------------------------------Maze Generator-----------------------------------"<<endl;
    cout << "\nEnter the size of the square Maze: ";
    cin >> size;
    char** Maze = new char* [size];
    for (int i = 0; i < size; i++) {
        Maze[i] = new char[size];
    }
    
    // Fills the grid with walls ('1' characters).
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Maze[i][j] = '1';
        }
    }

    //defining stack for back propogation
    stack<int> x;
    stack<int> y;

    
    //Selectig the starting point randomly 
    int pathway = 0;
    startingPontX=rand()%(size-2)+1;
    startingPontY=1;
   	endingPointX=startingPontX;
   	endingPointY=startingPontY;
    do {
		possibleWays=0;
       
       //checking the number of possible paths that can be visited
        for (int i = 0; i < 4; i++) {
            if (checkingPathway(startingPontX, startingPontY, i, Maze, size))
                possibleWays++;
        }

        //backpropogation
        if (possibleWays== 0) {
            startingPontX = x.top();
            startingPontY = y.top();
            x.pop();
            y.pop();
        }

        //visiting the cell if it is possible
        else{
            x.push(startingPontX);
            y.push(startingPontY);
            do {
                pathway = rand() % 4;
            } while (!checkingPathway(startingPontX, startingPontY, pathway, Maze, size));

            startingPontX = moveSides(pathway, startingPontX);
            startingPontY = moveUpAndDown(pathway, startingPontY);
        }

    //the path from 0's
        Maze[startingPontY][startingPontX] = '0';
        
	 } while (!x.empty());
	 
    //ending point- B
	Maze[endingPointY][endingPointX]='B';
	endingPointY=size-1;
	endingPointX=1;
	
    //Positioning starting point-A
	while(Maze[endingPointY-1][endingPointX]!='0'){
		endingPointX++;
	}
  	Maze[endingPointY][endingPointX]='A';
  	
   for(int i=0;i<size;i++){
   	for(int j=0;j<size;j++){
   		cout<<Maze[i][j]<<" ";
	   }
	   cout<<"\n";
   }

   //Store in a text file
   ofstream write("Maze Puzzle.txt");
    for(int i=0;i<size;i++){
   	for(int j=0;j<size;j++){
   	 write<<Maze[i][j]<<" ";
	   }
	   write<<"\n";
   }
  
   for(int i=0;i<size;i++){
   	delete[]Maze[i];
   }
   delete[]Maze;
    return 0;
}
