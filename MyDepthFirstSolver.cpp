#include <iostream>
#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "MyDepthFirstSolver.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MyDepthFirstSolver, "Depth First Solution (Required)");
MyDepthFirstSolver::MyDepthFirstSolver(){
	ended = false;
}
std::vector<std::vector<int>> MyDepthFirstSolver::make_vector(int width, int height){
	for(int i=0; i<width; i++){
		std::vector<int> row;
		for(int j=0; j<height; j++){
			row.push_back(0);
		}
		visited.push_back(row);
	}
	return visited;
}

void MyDepthFirstSolver::markCellVisited(int col, int row){
	visited[col][row] = 1;
}

Direction MyDepthFirstSolver::switchFromNumtoDirection(int dir){
	Direction newDir;
	if(dir == 1){
		newDir =  Direction::up;
	}
	else if(dir == 2){
		newDir= Direction::down;
	}
	else if(dir == 3){
		newDir= Direction::right;
	}
	else /*if(dir == 4)*/{
		newDir= Direction::left;
	}
	return newDir;
}

void MyDepthFirstSolver::move(int& col, int& row, int dir){
	//up
	if(dir == 1){
		row-=1;
	}
	//down
	else if(dir ==2){
		row+=1;
	}
	//right
	else if(dir == 3){
		col+=1;
	}
	else if(dir ==4){
		col-=1;
	}
}

std::vector<int> MyDepthFirstSolver::possiblePlaces(const Maze& maze,int col,int row){
	std::vector<int> places;
	if((row-1)>0 && !maze.wallExists(col, row, Direction::up) && visited[col][row-1] == 0){
			places.push_back(1);
		}
	if((row+1)<maze.getHeight()&&!maze.wallExists(col, row, Direction::down) && visited[col][row+1] ==0){
		places.push_back(2);
	
	}
	if((col-1)>0 && !maze.wallExists(col,row,Direction::left) && visited[col-1][row]==0){
		places.push_back(4);
	
	}
	if((col+1)<maze.getWidth() && !maze.wallExists(col,row, Direction::right) && visited[col+1][row] == 0){
		places.push_back(3);
	
	}
	return places;
}


void MyDepthFirstSolver::solveMazeHelper(const Maze& maze, MazeSolution& mazeSolution, int col , int row){

	if(!mazeSolution.isComplete()){
		markCellVisited(col,row);	
		std::vector<int>pos = possiblePlaces(maze,col,row);
		while(pos.size()!= 0)
		{
			int newDir = pos[0];
			int newRow = row;
			int newCol = col;
			move(newCol, newRow, newDir);
			if(!maze.wallExists(col, row, switchFromNumtoDirection(newDir)))
			{
				mazeSolution.extend(switchFromNumtoDirection(newDir));
				solveMazeHelper(maze,mazeSolution,newCol, newRow);
				if(mazeSolution.isComplete())
				{
					return;
				}
			}
				
			pos = possiblePlaces(maze,col,row);
		}
			
		if(mazeSolution.isComplete()){
			return;
		}
		else{
		mazeSolution.backUp();
		}
		

	}


}
		
	
	

/*1. mark current cell as visited
2. check surringdings for possible place (this means NO wall)
3. if you hit a wall, then you backtrack and go the other way
*/
void MyDepthFirstSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
	mazeSolution.restart();
	int r = mazeSolution.getStartingCell().first;
	int c = mazeSolution.getStartingCell().second;
	make_vector(maze.getWidth(),maze.getHeight());
	solveMazeHelper(maze, mazeSolution,c,r);
	//mazeSolution.extend(Direction::right);
}