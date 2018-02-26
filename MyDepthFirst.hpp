#ifndef MYDEPTHFIRST_HPP
#define MYDEPTHFIRST_HPP

#include "MazeGenerator.hpp"
#include <random>
#include <vector>
#include "Direction.hpp"

class MyDepthFirst:public MazeGenerator
{
public: 

    MyDepthFirst();
    int generateDirection();
    void move(int &col, int&row, int dir);
    void markCellVisited(int col, int row);
    //int generateRandomHeight();
    Direction switchFromNumtoDirection(int dir);
    std::vector<int> possiblePlaces(Maze& maze, int col,int row);
    void generateMazeHelper(Maze&  maze, int col, int row);
    std::vector<std::vector<int>> make_vector(int width, int height);
    virtual void generateMaze(Maze& maze);
    
private:
	std::random_device device; 
	std::default_random_engine engine{device()}; 
	std::vector<std::vector<int>> visited;
	//std::vector<std::vector<int>> possible_directions; 

};

#endif
