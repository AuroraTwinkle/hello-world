#include "Maze.h"



Maze::Maze()
{
}


Maze::~Maze()
{
}

void Maze::InitGame()
{
	initgraph(680, 480, SHOWCONSOLE);
	SetMazeSize();
}

void Maze::CreatMaze(int Height,int Width)
{
	if (Height % 2 == 0 || Width % 2 == 0)
		return;
	MazeMap = new int*[Height + 2];
	for (int x = 0; x < Height + 2; x++)
	{
		MazeMap[x] = new int[Width + 2];
		memset(MazeMap[x], WALL, sizeof(MazeMap[x]));
	}
}

void Maze::SetMazeSize()
{
	MazeSize.cx = MazeSize.cy = 0;
	TCHAR inp[4];
	while (MazeSize.cx<10||MazeSize.cx>100)
	{
		InputBox(inp, 4, _T("«Î ‰»Î√‘π¨∏ﬂ∂»Y\n∑∂Œß10°´100"),NULL, _T("10"));
		MazeSize.cx = _ttoi(inp);
	}
	while (MazeSize.cy < 10 || MazeSize.cy>100)
	{
		InputBox(inp, 4, _T("«Î ‰»Î√‘π¨øÌ∂»\n∑∂Œß10°´100"),NULL, _T("10"));
		MazeSize.cy = _ttoi(inp);
	}
	if (MazeSize.cx % 2 == 0)MazeSize.cx++;
	if (MazeSize.cy % 2 == 0)MazeSize.cy++;

}
