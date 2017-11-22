#include "Maze.h"

IMAGE mazeItem(200, 20);//加载地图元素
IMAGE mazeSight(360, 280);
IMAGE Photo(20, 20);
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
		rectangle(149 - i, 109 - (i >> 1), 490 + i, 370 + (i >> 1));
	}//边框
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);//透明背景

	// 绘制标题
	settextstyle(25, 0, _T("黑体"));
	outtextxy(248, 30, _T("迷　　宫"));

	// 绘制说明
	settextcolor(YELLOW);
	settextstyle(16, 0, _T("黑体"));
	outtextxy(0, 382, _T("操作说明："));
	outtextxy(0, 402, _T("方向键或 "));
	outtextxy(0, 420, _T("ASDW移动"));
	outtextxy(0, 440, _T("ESC：退出"));
	outtextxy(0, 460, _T("回车：自动寻路"));
}

void Maze::InitGame()
{
	initgraph(640, 480, SHOWCONSOLE);//打开一个图形窗口
	HelloWorld();
	SetMazeSize();
	seeSight.left = 0;
	seeSight.top = 0;
	seeSight.right = 17;
	seeSight.bottom = 13;
	Player.x = 2;
	Player.y = 2;
	CreatMaze(MazeSize.cx, MazeSize.cy);
	Draw();
}

void Maze::CreatMaze(int Width, int Height)
{
	if (Height % 2 == 0 || Width % 2 == 0)
		return;

	MazeMap = new int*[Width + 2];
	IsVisit = new bool*[Height + 2];
	for (int x = 0; x < Width + 2; x++)
	{
		MazeMap[x] = new int[Height + 2];
		IsVisit[x] = new bool[Width + 2];
		memset(IsVisit[x], false, sizeof(IsVisit[x]));//初始化为未被访问
		memset(MazeMap[x], WALL, (Height+2)*sizeof(int));//将数组全部初始化为墙壁
	}
	//定义边界
	for (int i = 0; i <= Width + 1; i++)
	{
		MazeMap[i][0] = ROAD;
		MazeMap[i][Height + 1] = ROAD;
		
	}
	for (int i = 1; i <= Height; i++)
	{
		MazeMap[0][i] = ROAD;
		MazeMap[Width+1][i] = ROAD;
	}
	MazeMap[1][2] = ENTRANCE;//定义入口
	
	MazeMap[Height - 1][Width - 1] = EXIT;//定义出口
	//TravelMakeMap(((rand() % (Width - 1)) & 0xfffe) + 2, ((rand() % (Height - 1)) & 0xfffe) + 2);
	
	POINT entrance;
	entrance.x = 2;
	entrance.y = 2;
	stack <POINT> path;
	BFS(entrance, path);
	for (int i = 0; i <= Width + 1; i++)
	{
		MazeMap[i][0] = BORDER;
		MazeMap[i][Height + 1] = BORDER;
		cout << MazeMap[i][0];
	}
	for (int i = 1; i <= Height; i++)
	{
		MazeMap[0][i] = BORDER;
		MazeMap[Width + 1][i] = BORDER;
	}
	

}

void Maze::SetMazeSize()//从用户的输入获取迷宫的大小
{
	MazeSize.cx = MazeSize.cy = 0;
	TCHAR inp[4];
	while (MazeSize.cx<20 || MazeSize.cx>100)
	{
		InputBox(inp, 4, _T("请输入迷宫高度Y\n范围20～100"), NULL, _T("20"));
		MazeSize.cx = _ttoi(inp);
	}
	while (MazeSize.cy < 20 || MazeSize.cy>100)
	{
		InputBox(inp, 4, _T("请输入迷宫宽度\n范围20～100"), NULL, _T("20"));
		MazeSize.cy = _ttoi(inp);
	}

	if (MazeSize.cx % 2 == 0)MazeSize.cx++;
	if (MazeSize.cy % 2 == 0)MazeSize.cy++;

}

void Maze::TravelMakeMap(int x,int y)
{
	int d[4][2] = { 0, 1, 1, 0, 0, -1, -1, 0 };

	// 将遍历方向乱序
	int n, t, i;
	for (i = 0; i < 4; i++)
	{
		n = rand() % 4;
		t = d[i][0], d[i][0] = d[n][0], d[n][0] = t;
		t = d[i][1], d[i][1] = d[n][1], d[n][1] = t;
	}

	// 尝试周围四个方向
	MazeMap[x][y] = ROAD;
	for (i = 0; i < 4; i++)
		if (MazeMap[x + 2 * d[i][0]][y + 2 * d[i][1]] == WALL)
		{
			MazeMap[x + d[i][0]][y + d[i][1]] = ROAD;
			TravelMakeMap(x + d[i][0] * 2, y + d[i][1] * 2);       // 递归
		}
}

void Maze::BFS(POINT now, stack <POINT> &path)//深度优先搜索
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
		if (MazeMap[x][y] == WALL)
		{
			path.push(nextNode);
			IsVisit[x][y] = true;
			MazeMap[x][y] = ROAD;
			MazeMap[(now.x + x) / 2][(now.y + y) / 2] = ROAD;
			now = nextNode;
			
		}
		else
		{
			now = path.top();
			path.pop();
		}

	}
}

void Maze::Draw()
{
	int x, y;
	SetWorkingImage(&mazeSight);
	for (int i = seeSight.left; i < seeSight.right; i++) 
	{
		for (int j = seeSight.top; j < seeSight.bottom; j++)
		{
			x = (i - seeSight.left)*20;
			y = (j - seeSight.top)*20;
			putimage(x, y, 20,20,&mazeItem,getMazeItem(i,j),0);
			//cout << getMazeItem(i, j)<<"\t";
		}
		//cout << endl;
	}
	x = (Player.x - seeSight.left) * 20;
	y = (Player.y - seeSight.top) * 20;
	putimage(x, y, 20, 20, &mazeItem, PLAYER, 0);
		
	SetWorkingImage();
	putimage(150, 110, 340, 260, &mazeSight, 10, 10);

}

MazeItem Maze::getMazeItem(int x, int y)
{
	return (MazeItem)MazeMap[x][y];
}

void Maze::loadImage()
{
	
	SetWorkingImage(&mazeItem);
	cleardevice();
	//玩家
	loadimage(&Photo,_T("timg.jpg"),20,20, true);

	setorigin(PLAYER, 0);
	setfillstyle(BS_DIBPATTERN, NULL, &Photo);
	solidrectangle(0, 0, 19, 19);
	

	//墙壁
	setorigin(WALL, 0);
	setlinecolor(LIGHTMAGENTA);
	setfillstyle((BYTE*)"\x4a\x2d\x66\x4b\xa5\xa2\x69\x54");
	settextcolor(LIGHTMAGENTA);
	solidrectangle(1, 1, 19, 19);
	rectangle(0, 0, 20, 20);
	//边框
	setorigin(BORDER, 0);
	settextcolor(WHITE);
	setfillstyle((BYTE*)"\x50\x55\x25\xa0\x05\x55\x22\x02");
	solidrectangle(0, 0, 19, 19);
	//入口
	setorigin(ENTRANCE, 0);
	settextcolor(WHITE);
	setfillcolor(WHITE);
	setfillstyle(2,5);
	solidrectangle(1, 1, 19, 19);
	//出口
	setorigin(EXIT, 0);
	settextcolor(WHITE);
	setfillstyle(2, 5);
	solidrectangle(1, 1, 19, 19);

	setorigin(0, 0);


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
			if (MazeMap[x][y]==WALL)
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
