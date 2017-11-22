#pragma once
#include <graphics.h>
#include <stack>
#include <random>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

enum MazeItem
{
	WALL = 0,
	PLAYER = 20,
	ROAD = 40,
	ENTRANCE = 60,
	EXIT = 80,
	BORDER = 100
};//ö�ٳ����Թ�Ԫ��
class Maze
{
public:
	Maze();
	virtual ~Maze();
	void HelloWorld();//��ʼ����
	void InitGame();//��ʼ����Ϸ���ݣ�������ͼ�������
	void CreatMaze(int Height, int Width);//�����Թ�
	void SetMazeSize();//�����Թ���С
	void TravelMakeMap(int x,int y);//ͨ�����������Թ�
	void BFS(POINT pos, stack <POINT> &path);//�����������
	int** MazeMap = NULL;//��ά���������洢�Թ���ͼ
	bool** IsVisit = NULL;//��Ƿ��ʹ��ĵ�
	void Draw();
	MazeItem getMazeItem(int x, int y);
	void loadImage();
	vector<POINT> notVisitNode(POINT now);
	//static std::default_random_engine direct;
private:
	SIZE MazeSize;//�Թ��ߴ�
	RECT seeSight;
	stack <POINT> PathStack;//·��ջ	
	int dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
};

