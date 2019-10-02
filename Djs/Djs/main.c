#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct Side//边
{
	int toVertex;//边指向的点
	int data;
	struct Side *next;
}Side, *sLink;
typedef struct Vertex//顶点
{
	int data;
	int dis;//距离
	sLink first;//第一个边
}Vertex, AdjList[20];
typedef struct Graph//图
{
	AdjList adj;//顶点数组，注意不是指针，用.不用->
	int n, v;//顶点数，边数
}Graph, *gLink;

void createGraph(gLink g)
{
	int n, v, data;
	printf("请输入顶点数与边数");
	scanf("%d %d", &n, &v);
	g->n = n;
	g->v = v;
	int i;
	for (i = 0; i<n; i++)
	{
		printf("请输入顶点%d权值", i);
		scanf("%d", &data);
		g->adj[i].data = data;
		g->adj[i].dis = 1000;
		g->adj[i].first = NULL;
	}
	printf("请输入边信息");
	int v1, v2, da;
	for (i = 0; i<v; i++)
	{
		scanf("%d %d %d", &v1, &v2, &da);
		sLink s = (sLink)malloc(sizeof(Side));
		s->toVertex = v2;
		s->next = g->adj[v1].first;
		g->adj[v1].first = s;
		s->data = da;
	}
}
void dijkstra(gLink g)
{
	//初始化所有路径
	g->adj[0].dis = 0;
	sLink s = g->adj[0].first;
	while (s)
	{
		int v = s->toVertex;
		g->adj[v].dis = s->data;
		s = s->next;
	}
	int i, j;
	int ss[15], u[15], snum = 0, unum = g->n;//s存完事的边，u存未完事的边
											 //执行算法
	g->adj[0].dis = 0;
	for (i = 0; i<unum; i++)
	{
		u[i] = i;
	}
	while (snum<g->n)
	{
		//找最近的点加入s，并从u删除
		int min = 1000;
		int index;
		for (i = 0; i<unum; i++)
		{
			int v = u[i];
			if (g->adj[v].dis<min)
			{
				min = g->adj[v].dis;
				index = i;
			}
		}
		int v = u[index];
		ss[snum++] = v;//加入ss
		unum--;
		for (j = index; j<unum; j++)//从u中删除
		{
			u[j] = u[j + 1];
		}
		//重新附权值
		sLink s = g->adj[v].first;
		while (s)
		{
			if (g->adj[v].dis + s->data<g->adj[s->toVertex].dis)
			{
				g->adj[s->toVertex].dis = g->adj[v].dis + s->data;
			}
			s = s->next;
		}
	}
}

int main()
{
	gLink g = (gLink)malloc(sizeof(Graph));
	createGraph(g);
	dijkstra(g);
	int i;
	for (i = 0; i<g->n; i++)
	{
		printf("%-5d", g->adj[i].dis);
	}
	return 0;
}
