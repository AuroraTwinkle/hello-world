#include <stdio.h>
#include <stdlib.h>

void selectSort(int data[], int length);//简单选择排序
void insertSort(int data[], int length);//简单插入排序
void bubbleSort(int data[], int length);//冒泡排序
int turnSearch(int data[], int key, int length);//顺序查找
int biarySearch(int data[], int key, int length);//二分查找

int data[] = { 51,38,79,22,91,105,33,52,16,112 };
int l = 10;

int main()
{
	bubbleSort(data, l);
	getchar();
	return 0;
}

void selectSort(int data[], int length)
{
	int temp = 0;
	for (int i = 0; i < length; i++)
	{
		int index = i;
		for (int j = i + 1; j < length; j++)
		{
			if (data[j] < data[index])
				index = j;
		}
		if (index != i)
		{
			temp = data[i];
			data[i] = data[index];
			data[index] = temp;
		}
		printf("第%d趟排序结果:\t", i + 1);
		for (int i = 0; i < length; i++)
		{
			printf("%d\t", data[i]);
		}
		printf("\n");
	}
}

void insertSort(int data[], int length)
{
	for (int i = 1; i < length; i++)
	{
		int j = i;
		while (j>0&&data[j-1]>data[j])
		{
			data[j] = data[j] + data[j - 1];
			data[j - 1] = data[j] - data[j - 1];
			data[j] = data[j] - data[j - 1];
			j--;
		}
		printf("第%d趟排序结果:\t", i);
		for (int i = 0; i < length; i++)
		{
			printf("%d\t", data[i]);
		}
		printf("\n");
	}
}

void bubbleSort(int data[],int length) {
	for (int i = 0; i < length - 1; i++) 
	{
		bool flag = true;
		for (int j = 0; j < length - 1 - i; j++) {
			if (data[j] > data[j + 1]) {
				data[j] = data[j] + data[j + 1];
				data[j + 1] = data[j] - data[j + 1];
				data[j] = data[j] - data[j + 1];
				flag = false;
			}
		}
		if (flag) {
			break;
		}
		printf("第%d趟排序结果:\t", i + 1);
		for (int i = 0; i < length; i++)
		{
			printf("%d\t", data[i]);
		}
		printf("\n");
	}
}

int turnSearch(int data[], int key, int length)
{
	if (length > 0) 
	{
		for (int i = 0; i < length; i++) {
			if (data[i] == key) {
				return i;
			}
		}
	}
	return -1;
}

int biarySearch(int data[], int key, int length)
{
	if (length > 0) {
		int low, high, mid;
		low = 0;
		high = length - 1;
		while (low <= high) {
			mid = (low + high) / 2;  
			if (key < data[mid])
				high = mid - 1;
			else if (key > data[mid])
				low = mid + 1;
			else
				return mid;

		}
	}

	return -1;
}
