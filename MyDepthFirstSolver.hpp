#ifndef MYDEPTHFIRSTSOLVER_HPP
#define MYDEPTHFIRSTSOLVER_HPP

#include "MazeSolver.hpp"
#include "Direction.hpp"
#include "Maze.hpp"


class MyDepthFirstSolver:public MazeSolver{
public:
	MyDepthFirstSolver();
	std::vector<std::vector<int>> make_vector(int width, int height);
	void markCellVisited(int col, int row);
	Direction switchFromNumtoDirection(int dir);
	void move(int &col, int& row, int dir); 
	std::vector<int> possiblePlaces(const Maze& maze, int col,int row);
	void solveMazeHelper( const Maze& maze, MazeSolution& mazeSolution, int col, int row);
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	
private:
	std::vector<std::vector<int>> visited;
	bool ended; 
};

#endif