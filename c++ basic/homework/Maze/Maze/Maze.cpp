#include "Maze.h"

IMAGE mazeItem(200, 20);//���ص�ͼԪ��
IMAGE mazeSight(360, 280);//�����Թ�
IMAGE Photo(20, 20);//����ļ����ص�ͼƬ
Maze::Maze()
{

}


Maze::~Maze()
{
}

void Maze::HelloWorld()
{
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);//͸������

	// ���Ʊ���
	settextstyle(25, 0, _T("����"));
	outtextxy(248, 30, _T("�ԡ�����"));

	// ����˵��
	settextcolor(YELLOW);
	settextstyle(16, 0, _T("����"));
	outtextxy(0, 382, _T("����˵����"));
	outtextxy(0, 402, _T("������ƶ� "));
	outtextxy(0, 420, _T("ESC���˳�"));
	outtextxy(0, 440, _T("�س����Զ�Ѱ·"));
	outtextxy(0, 460, _T("C:���·�� �ո�:·��"));
}

void Maze::InitGame()
{
	initgraph(640, 480, SHOWCONSOLE);//��һ��ͼ�δ���
	HelloWorld();
	
	if (MazeMap != NULL)
	{
		for (int x = 0; x < MazeSize.cx + 2; x++)
		{
			delete[] MazeMap[x];
		}
		delete[] MazeMap;
	}
	SetMazeSize();
	//��Ұ��Χ
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
	IsVisit = new int*[Height + 2];
	for (int x = 0; x < Width + 2; x++)
	{
		MazeMap[x] = new int[Height + 2];
		IsVisit[x] = new int[Width + 2];
		memset(IsVisit[x], 0, (Height+2)*sizeof(int));//��ʼ��Ϊδ������
		memset(MazeMap[x], WALL, (Height+2)*sizeof(int));//������ȫ����ʼ��Ϊǽ��
	}
	//����߽�
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
	MazeMap[1][2] = ENTRANCE;//�������
	
	MazeMap[Height -1][Width] = EXIT;//�������
	//TravelMakeMap(((rand() % (Width - 1)) & 0xfffe) + 2, ((rand() % (Height - 1)) & 0xfffe) + 2);
	POINT entrance;
	entrance.x = 20;
	entrance.y = 20;
	stack <POINT> path;
	BFS(entrance, path);
	for (int i = 0; i <= Width + 1; i++)
	{
		MazeMap[i][0] = BORDER;
		MazeMap[i][Height + 1] = BORDER;
	}
	for (int i = 1; i <= Height; i++)
	{
		MazeMap[0][i] = BORDER;
		MazeMap[Width + 1][i] = BORDER;
	}
	

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

//void Maze::TravelMakeMap(int x,int y)
//{
//	int d[4][2] = { 0, 1, 1, 0, 0, -1, -1, 0 };
//	int n, t, i;
//	for (i = 0; i < 4; i++)
//	{
//		n = rand() % 4;
//		t = d[i][0], d[i][0] = d[n][0], d[n][0] = t;
//		t = d[i][1], d[i][1] = d[n][1], d[n][1] = t;
//	}
//	MazeMap[x][y] = ROAD;
//	for (i = 0; i < 4; i++)
//		if (MazeMap[x + 2 * d[i][0]][y + 2 * d[i][1]] == WALL)
//		{
//			MazeMap[x + d[i][0]][y + d[i][1]] = ROAD;
//			TravelMakeMap(x + d[i][0] * 2, y + d[i][1] * 2); 
//		}
//}

void Maze::BFS(POINT now, stack <POINT> path)//�����������
{
	path.push(now);
	POINT nextNode;
	srand((unsigned)time(NULL));
	while (!path.empty())
	{
		
		vector<POINT> notVisitNodes = notVisitNode(now);
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
	for (int i = seeSight.left; i <= seeSight.right; i++) 
	{
		for (int j = seeSight.top; j <= seeSight.bottom; j++)
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
	putimage(x, y, 20, 20, &mazeItem, PLAYER, 0);//���
		
	SetWorkingImage();
	putimage(150, 110, 340, 260, &mazeSight, 10, 10);

}

void Maze::Move(int c)
{
	//����
	if (c == LEFT_OK)
	{
		if (Player.x > 1 && MazeMap[Player.x - 1][Player.y] != WALL && MazeMap[Player.x - 1][Player.y] != ENTRANCE)
		{
			Player.x--;
			if (seeSight.left > 0 && Player.x - seeSight.left < 5)
			{
				seeSight.left--;
				seeSight.right--;
			}
		}
		
	}
		
	//����
	if (c == DOWN_OK) 
	{
		if (Player.y < MazeSize.cy && MazeMap[Player.x][Player.y + 1] != WALL)
		{
			Player.y++;
			if (seeSight.bottom <= MazeSize.cy && seeSight.bottom - Player.y < 4)
			{
				seeSight.top++;
				seeSight.bottom++;
			}
		}
	}
	
	//����
	if (c == UP_OK)
	{
		if (Player.y > 1 && MazeMap[Player.x][Player.y - 1] != WALL)
		{
			Player.y--;
			if (seeSight.top > 0 && Player.y - seeSight.top < 4)
			{
				seeSight.bottom--;
				seeSight.top--;
			}
		}
	}

	//����
	if (c == RIGHT_OK)
	{
		if (Player.x < MazeSize.cx && MazeMap[Player.x + 1][Player.y] != WALL)
		{
			Player.x++;
			if (seeSight.right <= MazeSize.cx && seeSight.right - Player.x < 4)
			{
				seeSight.right++;
				seeSight.left++;
			}
		}
	}

	//�����
	if (c == MARK_OK)
	{
		MazeMap[Player.x][Player.y] = ROADMARK;
	}

	//���·��
	if (c == CLEARMARK_OK)
	{
		MazeMap[Player.x][Player.y] = ROAD;
	}
	
	//Ѱ·
	if (c == FINDPATH)
	{
		static int cc = 0;
		bool road=false;
		if (cc == 0) 
		{
			cc++;
			road=AutoFindPath();
		}
		else if(road)
		{
			HWND hwnd = GetHWnd();
			MessageBox(hwnd, TEXT("���ѳɹ�Ѱ·�������ظ�Ѱ·������"), TEXT("��ʾ"), MB_ICONEXCLAMATION);
		}
		else
		{
			cc = 0;
		}
		
	}
}

bool Maze::AutoFindPath()
{
	stack <POINT> Path;
	POINT now;
	now.x = 2;
	now.y = 2;
	POINT nextNode = now;
	MazeMap[now.x][now.y] = ROADMARK;
	Path.push(now);
	while (!Path.empty())
	{
		now = Path.top();
		nextNode = now;
		if (now.x==MazeSize.cx-1 && now.y==MazeSize.cy-1)
		{
			HWND hwnd = GetHWnd();
			MessageBox(hwnd, TEXT("��ϲ��Ѱ·�ɹ�����C�������������λ�õ�·�꣡"), TEXT("��ʾ"), MB_ICONEXCLAMATION);
			return true;
		}
		//���ϳ���Ѱ·
		nextNode.x -= 1;
		if (nextNode.x>0 && nextNode.x<MazeSize.cx+1 && nextNode.y>0&&nextNode.y<MazeSize.cy+1 && IsVisit[nextNode.x][nextNode.y]==0 && MazeMap[nextNode.x][nextNode.y] == ROAD)
		{
			MazeMap[nextNode.x][nextNode.y] = ROADMARK;
			IsVisit[nextNode.x][nextNode.y] = 1;
			Path.push(nextNode);
			continue;
		}
		nextNode = now;

		//���³���Ѱ·
		nextNode.x += 1;
		if (IsVisit[nextNode.x][nextNode.y]==0&&nextNode.x>0 && nextNode.x<MazeSize.cx + 1 && nextNode.y>0 && nextNode.y<MazeSize.cy + 1 && MazeMap[nextNode.x][nextNode.y] == ROAD)
		{
			MazeMap[nextNode.x][nextNode.y] = ROADMARK;
			IsVisit[nextNode.x][nextNode.y] = 1;
			Path.push(nextNode);
			continue;
		}
		nextNode = now;

		//������Ѱ·
		nextNode.y -= 1;
		if (IsVisit[nextNode.x][nextNode.y]==0&&nextNode.x>0 && nextNode.x<MazeSize.cx + 1 && nextNode.y>0 && nextNode.y<MazeSize.cy + 1 && MazeMap[nextNode.x][nextNode.y] == ROAD)
		{
			MazeMap[nextNode.x][nextNode.y] = ROADMARK;
			Path.push(nextNode);
			IsVisit[nextNode.x][nextNode.y] = 1;
			continue;
		}
		nextNode = now;

		//���ҳ���Ѱ·
		nextNode.y += 1;
		if (IsVisit[nextNode.x][nextNode.y]==0&&nextNode.x>0 && nextNode.x<MazeSize.cx + 1 && nextNode.y>0 && nextNode.y<MazeSize.cy + 1 && MazeMap[nextNode.x][nextNode.y] == ROAD)
		{
			MazeMap[nextNode.x][nextNode.y] = ROADMARK;
			Path.push(nextNode);
			IsVisit[nextNode.x][nextNode.y] = 1;
			continue;
		}
		POINT temp = Path.top();
		MazeMap[temp.x][temp.y] = ROAD;
		Path.pop();
		if (Path.empty())
		{
			HWND hwnd=GetHWnd();
			MessageBox(hwnd, TEXT("��Ǹ���Թ���ͨ·��"), TEXT("��ʾ"), MB_ICONEXCLAMATION);
			return false;
		}
	}
}



void Maze::StartPlay()
{
	int c = 0;
	
	PlaySound(TEXT("Star.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!(((c = GetKey())==QUIT_OK) && Quit()))
	{
		
		Move(c);
		Draw();
		if (arriveExit())
		{
			
			break;
		}
		Sleep(100);
	}
	//�����ڴ�
	if (MazeMap != NULL)
	{
		for (int x = 0; x < MazeSize.cx + 2; x++)
		{
			delete[] MazeMap[x];
		}
		delete[] MazeMap;
	}
	closegraph();
}

int Maze::GetKey()
{
	int cmd = 0;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		cmd |= DOWN_OK;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		cmd |= UP_OK;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		cmd |= LEFT_OK;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		cmd |= RIGHT_OK;
	}
	if (GetAsyncKeyState(' ') & 0x8000)
	{
		cmd |= MARK_OK;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		cmd |= QUIT_OK;
	}
	if (GetAsyncKeyState('C') & 0x8000)
	{
		cmd |= CLEARMARK_OK;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		cmd |= FINDPATH;
	}

	return cmd;
}

bool Maze::arriveExit()
{
	if (Player.x == MazeSize.cx - 1 && MazeSize.cy == Player.y)
	{
		HWND hwnd = GetHWnd();
		if (MessageBox(hwnd, TEXT("���ѵ����յ㣬�Ƿ�����һ�֣�"), TEXT("�󼪴���������Լ�"), MB_ICONERROR | MB_YESNO) == IDYES)
		{
			InitGame();
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool Maze::Quit()
{
	HWND hwnd = GetHWnd();
	if (MessageBox(hwnd, TEXT("���Ƿ�Ҫ�˳���Ϸ��"), TEXT("ע��"), MB_ICONQUESTION | MB_YESNO) == IDYES)
		return true;
	return false;
}

MazeItem Maze::getMazeItem(int x, int y)
{
	return (MazeItem)MazeMap[x][y];
}

void Maze::loadImage()
{
	
	SetWorkingImage(&mazeItem);
	cleardevice();
	//���
	loadimage(&Photo,_T("timg.jpg"),20,20, true);

	setorigin(PLAYER, 0);
	setfillstyle(BS_DIBPATTERN, NULL, &Photo);
	solidrectangle(0, 0, 19, 19);
	

	//ǽ��
	setorigin(WALL, 0);
	setlinecolor(LIGHTMAGENTA);
	setfillstyle((BYTE*)"\x4a\x2d\x66\x4b\xa5\xa2\x69\x54");
	settextcolor(LIGHTMAGENTA);
	solidrectangle(1, 1, 19, 19);
	rectangle(0, 0, 20, 20);
	//�߿�
	setorigin(BORDER, 0);
	settextcolor(WHITE);
	setfillstyle((BYTE*)"\x50\x55\x25\xa0\x05\x55\x22\x02");
	solidrectangle(0, 0, 19, 19);
	//���
	setorigin(ENTRANCE, 0);
	settextcolor(WHITE);
	setfillcolor(WHITE);
	setfillstyle(2,5);
	solidrectangle(1, 1, 19, 19);
	//����
	setorigin(EXIT, 0);
	settextcolor(RED);
	setfillcolor(RED);
	setfillstyle(2, 5);
	solidrectangle(1, 1, 19, 19);
	//·��
	setorigin(ROADMARK, 0);
	settextcolor(WHITE);
	setfillcolor(WHITE);
	setfillstyle(0);
	solidrectangle(1, 1, 19, 19);
	setlinecolor(WHITE);
	//rectangle(1, 1, 10, 10);�ڿӣ�ʹ��������ִ�����ѧ����֪��Ϊʲô

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
