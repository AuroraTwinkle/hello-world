#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#define filename "passage.txt"
#define decodename "decode.txt"
#define size 256
#define maxsize 256+256-1
#define human_size 25

typedef struct node
{
	int weight, number;//权重和编号
	int judge;//存放单个的编码
	int x[human_size];//编码存放
	struct node *father, *lchild, *rchild;//父亲左右孩子
}Node, *p_Node;

Node list[maxsize];
int read_num = 0, write_num = 0;
int huffman_head = 0;

void init_list()
{
	int i = 0, j = 0;
	for (i = 0; i<maxsize; i++)
	{
		list[i].weight = 0;
		list[i].judge = -1;
		list[i].number = i;
		list[i].father = NULL;
		list[i].rchild = NULL;
		list[i].lchild = NULL;
		for (j = 0; j<human_size; j++)
			list[i].x[j] = -1;

	}
}
void compress_read_we()
{
	FILE *fp;
	unsigned char ch[4];
	fp = fopen(filename, "rb");
	if (fp == NULL)
		printf("打开文件失败");
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%c", ch);
			// printf("%c",ch[0]);
			list[ch[0]].weight++;
			read_num++;
		}
	}
	list[ch[0]].weight--;
	read_num--;
	fclose(fp);
}
void change()
{
	int i = 0, j = 0, k = 0;
	int x[human_size];
	p_Node p;
	for (i = 0; i<size; i++)
	{
		j = 0;
		k = 0;
		if (list[i].weight != 0)
		{
			p = &list[i];
			while (p->judge >= 0)
			{
				x[j++] = p->judge;
				p = p->father;
			}
			j--;
			for (j; j >= 0; j--)
				list[i].x[k++] = x[j];//将反的编码变正
		}
	}
}
void huffman()
{
	int n = read_num;
	int x1 = 0, y1 = 0;
	int i = 0, j = size - 1;
	while (list[j].weight != read_num)
	{
		x1 = 0;
		y1 = 0;
		n = read_num;
		for (i = 0; i<maxsize; i++)
		{
			if (list[i].judge<0 && list[i].weight>0) {
				if (n >= list[i].weight) {
					n = list[i].weight;
					x1 = i;
				}
			}
		}
		list[x1].judge = 0;
		n = read_num;
		for (i = 0; i<maxsize; i++)
		{
			if (list[i].judge<0 && list[i].weight>0) {
				if (n >= list[i].weight) {
					n = list[i].weight;
					y1 = i;
				}
			}
		}
		//printf("%d %d\n",x1,y1);
		j++;
		list[x1].father = &list[j];
		list[y1].father = &list[j];
		list[x1].judge = 0;
		list[y1].judge = 1;
		list[j].lchild = &list[x1];
		list[j].rchild = &list[y1];
		list[j].weight = list[x1].weight + list[y1].weight;
	}
	huffman_head = j;
	change();
}
void compress_set()
{
	FILE *fp;
	int i = 0;
	fp = fopen("code.txt", "ab");
	if (fp == NULL)
		printf("编码失败");
	else
	{
		for (i = 0; i<size; i++)
			if (list[i].weight != 0)
			{
				fprintf(fp, "%d ", i);
				fprintf(fp, "%d\n", list[i].weight);
			}
	}
	fclose(fp);
}
void write(int x)
{
	FILE *fp;
	fp = fopen("compress.txt", "ab");
	if (fp == NULL)
		printf("压缩失败\n");
	//printf("%d ",x);
	fprintf(fp, "%c", x);
	fclose(fp);
}
void compress_write()
{
	FILE *fp;
	unsigned char ch[10];
	int x[8] = { 0 };
	int n = 0, j = 0, z = 0, num = 0;
	fp = fopen(filename, "rb");
	if (fp == NULL)
		printf("压缩失败");
	while (num<read_num)
	{
		j = 0;
		fscanf(fp, "%c", ch);
		num++;
		//printf("%d ",ch[0]);
		while (list[ch[0]].x[j] != -1)
		{
			x[n] = list[ch[0]].x[j];
			j++;
			n++;
			if (n == 8)
			{
				z = 0;
				for (int i = 0; i<8; i++)
					z += x[i] * pow(2.0, double(7 - i));
				n = 0;
				write(z);
				write_num++;
			}
		}
	}
	z = 0;
	for (int i = 0; i<n; i++)
		z += x[i] * pow(2.0, double(7 - i));
	write(z);
	write_num++;
	fclose(fp);

}
void compress()
{
	init_list();
	compress_read_we();
	huffman();
	remove("code.txt");
	compress_set();
	remove("compress.txt");
	compress_write();
	//printf("%d",write_num);
}
void free_read_we()
{

	FILE *fp;
	int x = 0, y = 0;
	int i = 0;
	fp = fopen("code.txt", "r");
	if (fp == NULL)
		printf("open error\n");
	while (!feof(fp))
	{
		fscanf(fp, "%d", &x);
		fscanf(fp, "%d", &y);
		list[x].weight = y;
		read_num += y;
	}
	read_num -= y;
	fclose(fp);
}
void ten_two(int x) {
	FILE *fp1;
	fp1 = fopen("temp.txt", "a");
	if (fp1 == NULL)
		printf("erroer");
	//printf("%d ",x);
	int i, c = 0, a[8], b[8] = { 0 };
	int j = 0;
	while (x != 0)
	{
		i = x % 2;
		a[c] = i;
		c++;
		x = x / 2;
	}
	c--;
	for (; c >= 0; c--)
		b[j + 7 - c] = a[c];
	for (i = 0; i<8; i++)
		fprintf(fp1, "%d\n", b[i]);
	fclose(fp1);
}
void free_translate()
{
	FILE *fp;
	unsigned char ch[10];
	fp = fopen("compress.txt", "rb");
	if (fp == NULL)
		printf("open error\n");
	while (!feof(fp))
	{
		fscanf(fp, "%c", ch);
		write_num++;
	}
	write_num--;
	fclose(fp);
	int n = 0;
	fp = fopen("compress.txt", "rb");
	if (fp == NULL)
		printf("open error\n");
	while (n<write_num)
	{
		fscanf(fp, "%c", ch);
		//printf("%c",ch[0]);
		ten_two(ch[0]);
		n++;
	}

}
void free_write()
{
	FILE *fp, *fp1;
	int Head = huffman_head, i = -1, n = 0;
	fp = fopen("temp.txt", "rb");
	fp1 = fopen(decodename, "ab");
	int x;
	if (fp == NULL || fp1 == NULL)
		printf("open error\n");
	while (n<read_num)
	{
		fscanf(fp, "%d", &x);
		//printf("%d",x);
		{
			if (x == 1)
			{
				Head = list[Head].rchild->number;
				if (list[Head].number<256)
				{
					fprintf(fp1, "%c", list[Head].number);
					Head = huffman_head;
					n++;
				}
			}
			if (x == 0)
			{
				Head = list[Head].lchild->number;
				if (list[Head].number<256)
				{
					fprintf(fp1, "%c", list[Head].number);
					Head = huffman_head;
					n++;
				}
			}
		}

	}
	fclose(fp);
	fclose(fp1);
}
void free()
{
	init_list();
	free_read_we();
	huffman();
	free_translate();
	remove("decode.txt");
	free_write();
	remove("temp.txt");
}
int main()
{
	while(1)
	{
		int choice = 0;
		printf("1.按1进行文本压缩\n");
		printf("2.按2进行文本解压\n");
		printf("3.按3进行图片压缩\n");
		printf("4.按4进行图片解压\n");
		printf("5.按5退出程序\n");
		scanf("%d",&choice);
		switch (choice)
		{
		case 1:
			compress();
			break;
		case 2:
			free();
			break;
		}
	}
	
	return 0;
}