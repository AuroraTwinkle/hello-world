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
	BORDER = 100,
	ROADMARK = 120
};//ö���Թ�Ԫ��
enum Command
{
	UP_OK = 14,
	DOWN_OK = 2,
	LEFT_OK=4,
	RIGHT_OK=6,
	QUIT_OK=8,
	MARK_OK=10,
	CLEARMARK_OK=12
};
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
	void Draw();//�����Թ��е�Ԫ��
	void Move(int c);//����ƶ�����
	void StartPlay();//��Ϸ��ѭ��
	int GetKey();//�����û�����
	bool arriveExit();//�ж��Ƿ񵽴����
	MazeItem getMazeItem(int x, int y);
	void loadImage();
	vector<POINT> notVisitNode(POINT now);
	//static std::default_random_engine direct;
private:
	SIZE MazeSize;//�Թ��ߴ�
	RECT seeSight;//��Ұ
	POINT Player;
	stack <POINT> PathStack;//·��ջ	
	int dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
};

