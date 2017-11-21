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
	void InitGame();//��ʼ����Ϸ���ݣ�������ͼ�������
	void CreatMaze(int Height, int Width);//�����Թ�
	void SetMazeSize();//�����Թ���С
	void TravelMakeMap();//ͨ�����������Թ�
	void BFS(POINT pos, stack <POINT> &path);//�����������
	int** MazeMap = NULL;//��ά���������洢�Թ���ͼ
	bool** IsVisit = NULL;//��Ƿ��ʹ��ĵ�
	vector<POINT> notVisitNode(POINT now);
	static std::default_random_engine direct;
private:
	SIZE MazeSize;//�Թ��ߴ�
	stack <POINT> PathStack;//·��ջ
	enum MazeItem
	{
		ROAD = 0,
		WALL = 1,
		PLAYER = 2,
		ENTRANCE = 3,
		EXIT = 4,
		BORDER = 5
	};//ö�ٳ����Թ�Ԫ��
	int dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
};

