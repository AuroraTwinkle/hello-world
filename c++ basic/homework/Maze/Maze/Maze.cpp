#include "Maze.h"

IMAGE mazeItem(100, 20);//���ص�ͼԪ��
IMAGE mazeSight(430, 380);

Maze::Maze()
{

}


Maze::~Maze()
{
}

void Maze::HelloWorld()
{
	for (int i = 0; i<128; i++)
	{
		setlinecolor(RGB((127 - i) <<1, 2 * (127 - i) >> 1, (127 - i) <<1));
		rectangle(80 - i, 60 - (2*i >> 1), 550 + i, 440 + (2*i >> 1));
	}//�߿�
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);//͸������

	// ���Ʊ���
	settextstyle(25, 0, _T("����"));
	outtextxy(248, 30, _T("�ԡ�����"));

	// ����˵��
	settextcolor(YELLOW);
	settextstyle(16, 0, _T("����"));
	outtextxy(0, 382, _T("����˵����"));
	outtextxy(0, 402, _T("������� "));
	outtextxy(0, 420, _T("ASDW�ƶ�"));
	outtextxy(0, 440, _T("ESC���˳�"));
	outtextxy(0, 460, _T("�س����Զ�Ѱ·"));
}

void Maze::InitGame()
{
	initgraph(640, 480, SHOWCONSOLE);//��һ��ͼ�δ���
	HelloWorld();
	SetMazeSize();
	seeSight.left = 0;
	seeSight.top = 0;
	seeSight.right = 19;
	seeSight.bottom = 17;
	CreatMaze(MazeSize.cx, MazeSize.cy);
	Draw();
}

void Maze::CreatMaze(int Height, int Width)
{
	if (Height % 2 == 0 || Width % 2 == 0)
		return;

	MazeMap = new int*[Height + 2];
	IsVisit = new bool*[Height + 2];
	for (int x = 0; x < Height + 2; x++)
	{
		MazeMap[x] = new int[Width + 2];
		IsVisit[x] = new bool[Width + 2];
		memset(IsVisit[x], false, sizeof(IsVisit[x]));//��ʼ��Ϊδ������
		memset(MazeMap[x], WALL, sizeof(MazeMap[x]));//������ȫ����ʼ��Ϊǽ��
	}
	//����߽�
	for (int i = 0; i <= Width + 1; i++)
	{
		MazeMap[0][i] = BORDER;
		MazeMap[Height + 1][i] = BORDER;
	}
	for (int i = 1; i <= Height; i++)
	{
		MazeMap[0][i] = BORDER;
		MazeMap[Width + 1][i] = BORDER;
	}
	MazeMap[1][1] = ENTRANCE;//�������
	IsVisit[1][1] = true;
	MazeMap[Height - 1][Width - 1] = EXIT;//�������
	IsVisit[Height - 1][Width - 1] = true;
	POINT entrance;
	entrance.x = 1;
	entrance.y = 1;
	stack <POINT> path;
	BFS(entrance, path);

}

void Maze::SetMazeSize()//���û��������ȡ�Թ��Ĵ�С
{
	MazeSize.cx = MazeSize.cy = 0;
	TCHAR inp[4];
	while (MazeSize.cx<20 || MazeSize.cx>100)
	{
		InputBox(inp, 4, _T("�������Թ��߶�Y\n��Χ20��100"), NULL, _T("20"));
		MazeSize.cx = _ttoi(inp);
	}
	while (MazeSize.cy < 20 || MazeSize.cy>100)
	{
		InputBox(inp, 4, _T("�������Թ����\n��Χ20��100"), NULL, _T("20"));
		MazeSize.cy = _ttoi(inp);
	}

	if (MazeSize.cx % 2 == 0)MazeSize.cx++;
	if (MazeSize.cy % 2 == 0)MazeSize.cy++;

}

void Maze::TravelMakeMap(int x,int y)
{
	int d[4][2] = { 0, 1, 1, 0, 0, -1, -1, 0 };

	// ��������������
	int n, t, i;
	for (i = 0; i < 4; i++)
	{
		n = rand() % 4;
		t = d[i][0], d[i][0] = d[n][0], d[n][0] = t;
		t = d[i][1], d[i][1] = d[n][1], d[n][1] = t;
	}

	// ������Χ�ĸ�����
	MazeMap[x][y] = ROAD;
	for (i = 0; i < 4; i++)
		if (MazeMap[x + 2 * d[i][0]][y + 2 * d[i][1]] == WALL)
		{
			MazeMap[x + d[i][0]][y + d[i][1]] = ROAD;
			TravelMakeMap(x + d[i][0] * 2, y + d[i][1] * 2);       // �ݹ�
		}
}

void Maze::BFS(POINT now, stack <POINT> &path)//�����������
{
	path.push(now);
	POINT nextNode;
	srand((unsigned)time(NULL));
	while (!path.empty())
	{
		
		vector<POINT> notVisitNodes = notVisitNode(now);
		//int ran = notVisitNodes.size();
		//uniform_int_distribution<time_t> RandomEngine1(0,ran);
		if (notVisitNodes.empty())
		{
			now = path.top();
			path.pop();			
			continue;
		}
		int ran = rand() % notVisitNodes.size();
		nextNode = notVisitNodes[ran];
		int x = nextNode.x;
		int y = nextNode.y;
		if (IsVisit[x][y])
		{
			now = path.top();
			path.pop();		
		}
		else
		{
			path.push(nextNode);
			IsVisit[x][y] = true;
			MazeMap[x][y] = ROAD;
			MazeMap[(now.x + x) / 2][(now.y + y) / 2] = ROAD;
			now = nextNode;
		}

	}
}

void Maze::Draw()
{
	int x, y,k=0;
	SetWorkingImage(&mazeSight);
	for (int i = seeSight.left+1; i < seeSight.right; i++) 
	{
		for (int j = seeSight.top+1; j < seeSight.bottom; j++)
		{
			x = (i - seeSight.left)*20;
			y = (j - seeSight.top)*20;
			putimage(x, y, 20,20,&mazeItem,getMazeItem(i,j),0);
		}
	}
		
	SetWorkingImage();
	putimage(81, 61, 430, 380, &mazeSight, 10, 10);
}

MazeItem Maze::getMazeItem(int x, int y)
{
	return (MazeItem)MazeMap[x][y];
}

void Maze::loadImage()
{
	SetWorkingImage(&mazeItem);
	cleardevice();
	setorigin(WALL, 0);
	
	setlinecolor(LIGHTMAGENTA);
	setfillstyle((BYTE*)"\x4a\x2d\x66\x4b\xa5\xa2\x69\x54");
	settextcolor(LIGHTMAGENTA);
	solidrectangle(1, 1, 19, 19);
	rectangle(0, 0, 20, 20);
}

vector<POINT> Maze::notVisitNode(POINT now)
{
	vector<POINT> list;
	for (int i = 0; i < 4; i++)
	{
		int x = now.x + 2 * dir[i][0];
		int y = now.y + 2 * dir[i][1];
		if (x > 0 && x < MazeSize.cx + 1 && y>0 && y < MazeSize.cy + 1)
		{
			if (!IsVisit[x][y])
			{
				POINT node;
				node.x = x;
				node.y = y;
				list.push_back(node);
			}
		}
	}
	return list;

}
