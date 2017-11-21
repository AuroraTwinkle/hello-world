#include "Maze.h"

std::default_random_engine Maze::direct(time(NULL));

Maze::Maze()
{

}


Maze::~Maze()
{
}

void Maze::InitGame()
{
	initgraph(680, 480, SHOWCONSOLE);//打开一个图形窗口
	SetMazeSize();
	CreatMaze(MazeSize.cx, MazeSize.cy);
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
		memset(IsVisit[x], false, sizeof(IsVisit[x]));//初始化为未被访问
		memset(MazeMap[x], WALL, sizeof(MazeMap[x]));//将数组全部初始化为墙壁
	}
	//定义边界
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
	MazeMap[1][1] = ENTRANCE;//定义入口
	IsVisit[1][1] = true;
	MazeMap[Height - 1][Width - 1] = EXIT;//定义出口
	IsVisit[Height - 1][Width - 1] = true;
	POINT entrance;
	entrance.x = 1;
	entrance.y = 1;
	stack <POINT> path;
	BFS(entrance, path);

}

void Maze::SetMazeSize()//从用户的输入获取迷宫的大小
{
	MazeSize.cx = MazeSize.cy = 0;
	TCHAR inp[4];
	while (MazeSize.cx<10 || MazeSize.cx>100)
	{
		InputBox(inp, 4, _T("请输入迷宫高度Y\n范围10～100"), NULL, _T("10"));
		MazeSize.cx = _ttoi(inp);
	}
	while (MazeSize.cy < 10 || MazeSize.cy>100)
	{
		InputBox(inp, 4, _T("请输入迷宫宽度\n范围10～100"), NULL, _T("10"));
		MazeSize.cy = _ttoi(inp);
	}

	if (MazeSize.cx % 2 == 0)MazeSize.cx++;
	if (MazeSize.cy % 2 == 0)MazeSize.cy++;

}

void Maze::TravelMakeMap()
{

}

void Maze::BFS(POINT now, stack <POINT> &path)//深度优先搜索
{
	path.push(now);
	POINT nextNode;
	while (!path.empty())
	{
		cout << "cheng";
		vector<POINT> notVisitNodes = notVisitNode(now);
		uniform_int_distribution<time_t> RandomEngine1(0, notVisitNodes.size());
		if (notVisitNodes.empty())
		{
			path.pop();
			if (!path.empty())
			{
				now = path.top();
			}			
			continue;
		}
		nextNode = notVisitNodes[RandomEngine1(direct)];
		int x = nextNode.x;
		int y = nextNode.y;
		if (IsVisit[x][y])
		{
			path.pop();
			if (!path.empty())
			{
				now = path.top();
			}
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

vector<POINT> Maze::notVisitNode(POINT now)
{
	vector<POINT> list;
	for (int i = 0; i < 4; i++)
	{
		int x = now.x + 2 * dir[i][0];
		int y = now.y + 2 * dir[i][1];
		if (x > 0 && x < MazeSize.cy + 1 && y>0 && y < MazeSize.cx + 1)
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

//&& nextNode.x > 0 && nextNode.x < MazeSize.cy + 1 && nextNode.y>0 && nextNode.y < MazeSize.cx + 1