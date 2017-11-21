#pragma once
#include <graphics.h>
#include <stack>
#include <random>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;
class Maze
{
public:
	Maze();
	virtual ~Maze();
	void InitGame();//初始化游戏数据，包括地图，人物等
	void CreatMaze(int Height, int Width);//创建迷宫
	void SetMazeSize();//设置迷宫大小
	void TravelMakeMap();//通过遍历生成迷宫
	void BFS(POINT pos, stack <POINT> &path);//深度优先搜索
	int** MazeMap = NULL;//二维数组用来存储迷宫地图
	bool** IsVisit = NULL;//标记访问过的点
	vector<POINT> notVisitNode(POINT now);
	static std::default_random_engine direct;
private:
	SIZE MazeSize;//迷宫尺寸
	stack <POINT> PathStack;//路径栈
	enum MazeItem
	{
		ROAD = 0,
		WALL = 1,
		PLAYER = 2,
		ENTRANCE = 3,
		EXIT = 4,
		BORDER = 5
	};//枚举常用迷宫元素
	int dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
};

