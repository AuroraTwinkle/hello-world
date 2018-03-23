#pragma once
#include <graphics.h>
#include <stack>
#include <random>
#include <ctime>
#include <iostream>
#include <vector>
#include <mmsystem.h>
#include <fstream>
#pragma comment(lib, "winmm.lib") 

using namespace std;

enum MazeItem
{
	WALL = 0,
	PLAYER = 20,
	ROAD = 40,
	ENTRANCE = 60,
	EXIT = 80,
	BORDER = 100,
	ROADMARK = 120
};//枚举迷宫元素
enum Command
{
	UP_OK = 14,
	DOWN_OK = 2,
	LEFT_OK=4,
	RIGHT_OK=6,
	QUIT_OK=8,
	MARK_OK=10,
	CLEARMARK_OK=12,
	FINDPATH=16
};
class Maze
{
public:
	Maze();
	~Maze();
	void HelloWorld();//开始界面
	void InitGame();//初始化游戏数据，包括地图，人物等
	void CreatMaze(int Height, int Width);//创建迷宫
	void SetMazeSize();//设置迷宫大小
	//void TravelMakeMap(int x,int y);//通过随机遍历生成迷宫
	void BFS(POINT pos, stack <POINT> path);//深度优先遍历产生随机迷宫
	int** MazeMap = NULL;//二维数组用来存储迷宫地图
	int** IsVisit = NULL;//标记访问过的点
	void Draw();//绘制迷宫中的元素
	void Move(int c);//玩家移动函数
	bool AutoFindPath();//自动寻路
	void StartPlay();//游戏主循环
	int GetKey();//捕获用户命令
	bool arriveExit();//判断是否到达出口
	bool Quit();//询问用户是否确认退出
	bool FileOrRand;//用来判断是否从文件导入地图
	MazeItem getMazeItem(int x, int y);
	void loadImage();
	vector<POINT> notVisitNode(POINT now);
	//static std::default_random_engine direct;
	IMAGE mazeItem;//加载地图元素
	IMAGE mazeSight;//绘制迷宫
	IMAGE Photo;//存放文件加载的图片
private:
	SIZE MazeSize;//迷宫尺寸
	RECT seeSight;//视野
	POINT Player;
	int cc;//用来避免重复寻路操作
	stack <POINT> PathStack;//路径栈	
	int dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
};

