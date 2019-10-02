#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct Side//��
{
	int toVertex;//��ָ��ĵ�
	int data;
	struct Side *next;
}Side, *sLink;
typedef struct Vertex//����
{
	int data;
	int dis;//����
	sLink first;//��һ����
}Vertex, AdjList[20];
typedef struct Graph//ͼ
{
	AdjList adj;//�������飬ע�ⲻ��ָ�룬��.����->
	int n, v;//������������
}Graph, *gLink;

void createGraph(gLink g)
{
	int n, v, data;
	printf("�����붥���������");
	scanf("%d %d", &n, &v);
	g->n = n;
	g->v = v;
	int i;
	for (i = 0; i<n; i++)
	{
		printf("�����붥��%dȨֵ", i);
		scanf("%d", &data);
		g->adj[i].data = data;
		g->adj[i].dis = 1000;
		g->adj[i].first = NULL;
	}
	printf("���������Ϣ");
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
	//��ʼ������·��
	g->adj[0].dis = 0;
	sLink s = g->adj[0].first;
	while (s)
	{
		int v = s->toVertex;
		g->adj[v].dis = s->data;
		s = s->next;
	}
	int i, j;
	int ss[15], u[15], snum = 0, unum = g->n;//s�����µıߣ�u��δ���µı�
											 //ִ���㷨
	g->adj[0].dis = 0;
	for (i = 0; i<unum; i++)
	{
		u[i] = i;
	}
	while (snum<g->n)
	{
		//������ĵ����s������uɾ��
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
		ss[snum++] = v;//����ss
		unum--;
		for (j = index; j<unum; j++)//��u��ɾ��
		{
			u[j] = u[j + 1];
		}
		//���¸�Ȩֵ
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
