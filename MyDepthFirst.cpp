#include <iostream>
#include "MazeGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "MyDepthFirst.hpp"
#include "Maze.hpp"
#include <random>
#include <vector>



ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyDepthFirst, "Depth First (Required)");

MyDepthFirst::MyDepthFirst()
{ 
}

std::vector<std::vector<int>> MyDepthFirst::make_vector(int width, int height){
	for(int i=0; i<width; i++){
		std::vector<int> row;
		for(int j=0; j<height; j++){
			row.push_back(0);
		}
		visited.push_back(row);
	}
	return visited;
}

int MyDepthFirst::generateDirection(){
	std::uniform_int_distribution<int> direction_distribution{1,4};
	int direction = direction_distribution(engine);
	return direction;
}

void MyDepthFirst::move(int& col, int& row, int dir){
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

void MyDepthFirst::markCellVisited(int col, int row){
	visited[col][row] = 1;
}
// int MyDepthFirst::generateHeight(){
// 	return 0;
// }

Direction MyDepthFirst::switchFromNumtoDirection(int dir){
	Direction newDir = Direction:: up;
	if(dir == 1){
		newDir =  Direction::up;
	}
	else if(dir == 2){
		newDir= Direction::down;
	}
	else if(dir == 3){
		newDir= Direction::right;
	}
	else/* if(dir == 4)*/{
		newDir= Direction::left;
	}
	return newDir;
}

void MyDepthFirst::generateMazeHelper(Maze& maze,int col, int row){
	markCellVisited(col,row);
	//std::cout<<possiblePlaces(maze,row,col).size()<<std::endl;
	//for(int i =0; i<possiblePlaces(maze,row,col).size(); i++){
	//	std::cout<<possiblePlaces(maze, row,col)[i]<<std::endl;
	//}
	std::vector<int> pos = possiblePlaces(maze,col,row);
	//int row_holder = row;
	//int col_holder = col;
	while(pos.size() != 0){
	//while(pos.size())
		std::uniform_int_distribution<int> direction_distribution{0,static_cast<int>(pos.size()-1)};
		int dirIndex = direction_distribution(engine);
		int newDir = pos[dirIndex];
		//std::cout<<newDir<<std::endl;
		//std::cout<<row<<' '<<col<<std::endl;
		//move(row,col, newDir);
		int oldRow = row;
		int oldCol = col;
		move(oldCol,oldRow,newDir);
		if(visited[oldCol][oldRow] == 0 ){
			if(maze.wallExists(col,row,switchFromNumtoDirection(newDir))){
				maze.removeWall(col,row,switchFromNumtoDirection(newDir));
				//std::cout<<"just deleted wall"<<std::endl;
				generateMazeHelper(maze, oldCol,oldRow);
               
			}
			//else{
			//	generateMazeHelper(maze,row_holder,col_holder);
			//}
		}
		//else
		pos=possiblePlaces(maze, col ,row);
	}
		return;
}


/*
1 : up
2: down
3: right
4: left
*/
std::vector<int> MyDepthFirst::possiblePlaces(Maze& maze, int col,int row){
	std::vector<int> places; 
	if((row-1)>0 && visited[col][row-1]==0){
			places.push_back(1);
		}
	
	if((row+1)<maze.getHeight()&&visited[col][row+1] ==0){
		places.push_back(2);
	
	}
	if((col-1)>0 && visited[col-1][row] == 0){
		places.push_back(4);
	
	}
	if((col+1)<maze.getWidth() && visited[col+1][row] ==0){
		places.push_back(3);
	
	}
	//if(col-1)
	return places;
}
void MyDepthFirst::generateMaze(Maze& maze){
	make_vector(maze.getWidth(),maze.getHeight());

	maze.addAllWalls();
	int r = 0;
	int c=  0; 
	//for(int i =0; i<maze.getWidth(); i++){
	//	for(int j =0; j<maze.getHeight(); j++){
	//		if(visited[i][j] == 0){
	generateMazeHelper(maze, c,r);

}