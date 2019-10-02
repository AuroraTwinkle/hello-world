#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define MAXSTRINGNUMBER 100


int len(char *str);
void getNext(char *str, int *next);
void KMP(char *str, char *subStr, int *next);
void getStrFromFile(char *str, char *path);
void startKMP(char *str, char *subStr, int *next);

int main()
{
	char motherStr[MAXSTRINGNUMBER];
	char subStr[MAXSTRINGNUMBER];
	int next[MAXSTRINGNUMBER] = { 0 };

	getStrFromFile(motherStr, "E://string.txt");
	printf("ĸ��:%s\n", motherStr);
	startKMP(motherStr, subStr, next);

	system("pause");

	return 0;
}

int len(char *str) {
	return strlen(str);
}

void getNext(char * str, int * next)
{
	int length = len(str);
	int i = 1;
	int j = 0;

	while (i < length)
	{
		if (*(str + i) == *(str + j))
		{
			*(next + i) = ++j;
		}
		else
		{
			if (j != 0)
			{
				j = *(next + j - 1);
				continue;
			}
		}
		i++;
	}
}

void KMP(char * str, char * subStr, int * next)
{
	int length1 = len(str);
	int length2 = len(subStr);
	int i = 0, j = 0;
	const int true = 1;
	const int false = 0;
	int flag = false;

	while (i < length1)
	{
		if (*(str + i) == *(subStr + j))
		{
			j++;
		}
		else
		{
			if (j != 0)
			{
				j = *(next + j - 1);
				continue;
			}
		}
		if (j == length2)
		{
			j = *(next + j - 1);
			flag = true;
			printf("�Ӵ���ĸ���е��±꣺%d��%d\n", i - length2 + 1, i);
		}
		i++;
	}
	if (!flag) {
		printf("δ��ĸ�����ҵ��Ӵ�\n");
	}
}



void getStrFromFile(char *str, char *path) {
	FILE *fp;
	if ((fp = fopen(path, "r")) == NULL) {
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	fgets(str, 1000, fp);
	fclose(fp);
}

void startKMP(char * str, char * subStr, int * next)
{

	int c = 0;
	while (c != 27)
	{
		printf("�������Ӵ�:");
		scanf_s("%s", subStr, MAXSTRINGNUMBER);
		printf("�Ӵ�:%s\n", subStr);
		getNext(subStr, next);
		KMP(str, subStr, next);
		printf("��Esc�˳��㷨,��������������㷨\n");
		c = _getch();
	}
}

