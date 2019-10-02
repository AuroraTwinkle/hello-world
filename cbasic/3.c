#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXNUM 100


typedef  struct
{
	long  int  number;  // 书号
	char  name[50];   // 书名
	char  author[20]; // 作者
	int   price;    // 价格
} bookinfo;

typedef  struct
{
	bookinfo   data[MAXNUM];
	int   num;
} listtype;

listtype list;

void InitList();//初始化
void Print(listtype L); //打印
int InSert(listtype &L, int i, long int x, const char* book,const char* author, int price);//插入数据
int Delete(listtype &L, int i);//删除

int main()
{
	InitList();
	InSert(list, 1, 1, "Basic", "zhang", 15);
	InSert(list, 2, 2, "VB", "Li", 20);
	InSert(list, 3, 3, "C", "Wang", 18);
	InSert(list, 4, 4, "delphi", "Zhao", 23);
	InSert(list, 5, 5, "java", "G", 100);
	Print(list);
	Delete(list, 3);
	printf("删除第三条后:\n");
	Print(list);
	getchar();
	return 0;
}

void InitList()
{
	list.num = 0;
}

int InSert(listtype &L, int i, long int x,const char* book, const char* author, int price)
{
	int j;
	if (i<1 || i>L.num + 1) {
		printf("越界\n");
		return 0;
	}
	for (j = L.num; j > i; j--) {
		L.data[j + 1] = L.data[j];
	}
	L.data[i - 1].number = x;
	strcpy(L.data[i - 1].name, book);
	strcpy(L.data[i - 1].author, author);
	L.data[i - 1].price = price;
	L.num++;
	return 1;
}

int Delete(listtype &L, int i)
{
	int j;
	if (i<1 || i>L.num) {
		printf("越界\n"); return 0;
	}
	for (j = i - 1; j < L.num - 1; j++)
		L.data[j] = L.data[j + 1];
	L.num--;
	return 1;

	return 0;
}

void Print(listtype L)
{
	for (int i = 0; i<L.num; i++)
	{
		printf("%d\t%s\t%s\t%d\n", L.data[i].number, L.data[i].name, L.data[i].author, L.data[i].price);
	}
}
