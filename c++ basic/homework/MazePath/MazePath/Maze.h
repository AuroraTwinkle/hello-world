#pragma once
#include <graphics.h>
class Maze
{
public:
	Maze();
	virtual ~Maze();
	void InitGame();
	void CreatMaze(int Height, int Width);
	void SetMazeSize();
	int** MazeMap=NULL;
	

private:
	SIZE MazeSize;
	enum MazeItem
	{
		ROAD = 0,
		WALL = 1
	};
};

