#include <iostream>
#include <stack>
using namespace std;

void insertSort(int data[], int n);
void insertSort_0(int arr[], int length);
void binaryInsertSort(int a[], int l);
void shellSort(int a[], int l);
void bubbleSort_0(int a[], int l);
void bubbleSort_1(int a[], int l);
int Partition(int a[], int first, int end);
void quickSort(int a[], int first, int end);
void quickSort_1(int a[], int n);
void selectSort(int a[], int n);
void Sift(int a[], int k, int m);//筛选法调整堆
void heapSort(int a[], int n);//堆排序
void Merge(int a[], int r[], int s, int m, int n);//一次归并
void mergeSort(int a[], int r[], int s, int t);

int main()
{
	int data[] = { 5,23,45,56,2,4,454,45,65,456,87,78,79 };
	int data1[] = { 0,120,45,56,1};
	int data2[13];
	int l = 16;
	mergeSort(data1,data2,0,4);
	for (int i = 0; i < 13; i++)
	{
		cout << data2[i] << "\t";
	}
	getchar();
	return 0;
}

void insertSort(int data[], int n)
{
	for (int i = 2; i < n; i++)
	{
		int j = 0;
		data[0] = data[i];
		for (j = i - 1; data[j] > data[0]; j--)
		{
			data[j + 1] = data[j];
		}
		data[j + 1] = data[0];
	}
}
void insertSort_0(int arr[], int length)
{
	int i = 0, j = 0;
	for (i = 1; i < length; i++)
	{
		arr[0] = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > arr[0])
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = arr[0];
	}
}

void binaryInsertSort(int a[], int l)
{
	for (int i = 2; i < l; i++)
	{
		a[0] = a[i];
		int low = 1;
		int high = i - 1;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (a[i] > a[mid])
				low = mid + 1;
			else
				high=mid - 1;
		}
		for (int j = i - 1; j >= high + 1; j--)
		{
			a[j + 1] = a[j];
		}
		a[high + 1] = a[0];
	}
}

void shellSort(int a[], int l)
{
	for (int d = l / 2; d >= 1; d /= 2)
	{
		for (int i = d + 1; i < l; i++)
		{
			int j = 0;
			a[0] = a[i];
			for (j = i - d; j > 0 && a[0] < a[j]; j -= d)
			{
				a[j+d] = a[j];
			}
			a[j+d] = a[0];
		}
	}
}

void bubbleSort_0(int a[], int l)
{
	for (int i = 1; i < l; i++)
	{
		int swap = 0;
		for (int j = 1; j < l - i; j++)
		{
			if (a[j] < a[j + 1])
			{
				a[0] = a[j];
				a[j] = a[j + 1];
				a[j + 1] = a[0];
				swap = 1;
			}

		}
		if (swap == 0)
			break;
	}
}

void bubbleSort_1(int a[], int length)
{
	int exchange = length;
	while (exchange)
	{
		int bound = exchange;
		exchange = 0;
		for (int j = 2; j < bound; j++)
		{
			if (a[j] < a[j - 1])
			{
				a[0] = a[j];
				a[j] = a[j - 1];
				a[j - 1] = a[0];
				exchange = j;
			}
		}
	}
}

int Partition(int a[], int first, int end)
{
	int i = first, j = end;
	a[0] = a[i];
	while (i < j)
	{
		
		while (i < j && a[0] < a[j])j--;
		if (i < j)
		{
			a[i] = a[j];
			i++;
		}
		while (i<j && a[i]<a[0])i++;
		if (i < j)
		{
			a[j] = a[i];
			j--;
		}
	}
	a[i] = a[0];
	return i;
}

void quickSort(int a[], int first, int end)
{
	if (first < end)
	{
		int pivot = Partition(a, first, end);
		quickSort(a, first, pivot - 1);
		quickSort(a,pivot+1,end);
	}
}

void quickSort_1(int a[], int n)
{
	stack <int> s;
	int low = 1;
	int high = n;
	if(low<high)
	{
		int mid = Partition(a, low, high);
		if (low < mid)
		{
			s.push(mid - 1);
			s.push(low);
			
		}
		if (mid < high)
		{
			s.push(high);
			s.push(mid + 1);
			
		}
	}
	
	while(!s.empty())
	{
		int first = s.top();
		s.pop();
		int end = s.top();
		s.pop();
		int mid = Partition(a, first, end);
		if (first < mid)
		{
			s.push(mid - 1);
			s.push(first);
		}
		if (mid < end)
		{
			s.push(end);
			s.push(mid + 1);
		}
	}
	
}

void selectSort(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int index = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[index])
				index = j;
		}
		if (index != i)
		{
			a[0] = a[i];
			a[i] = a[index];
			a[index] = a[0];
		}
	}
}

void Sift(int a[], int k, int m)
{
	int i = k;
	int j = 2 * i;
	while (j <= m)
	{
		if (j < m&&a[j] > a[j + 1])
			j++;
		if (a[i] < a[j])
			break;
		else
		{
			a[0] = a[i];
			a[i] = a[j];
			a[j] = a[0];
			i = j;
			j = 2 * i;
		}
	}
}

void heapSort(int a[], int n)
{
	for (int i = n / 2; i >= 1; i--)
	{
		Sift(a, i, n);
	}
	for (int i = 1; i < n; i++)
	{
		a[0] = a[1];
		a[1] = a[n - i + 1];
		a[n - i + 1] = a[0];
		Sift(a, 1, n - i);
	}
}

void Merge(int a[], int r[], int s, int m, int t)
{
	int i = s;
	int j = m + 1;
	int k = s;
	while (i <= m && j <= t)
	{
		if (a[i] <= a[j])
		{
			r[k++] = a[i++];
		}
		else
		{
			r[k++] = r[j++];
		}
	}
	if (i <= m)
	{
		while (i <= m)
		{
			r[k++] = a[i++];
		}
	}
	else
	{
		while (j <= t)
		{
			r[k++] = a[j++];
		}
	}
}

void mergeSort(int a[], int r[], int s, int t)
{
	if (s == t)
		r[s] = a[s];
	else {
		int m = (s + t) / 2;
		mergeSort(a, r, s, m);
		mergeSort(a, r, m + 1, t);
		Merge(a, r, s, m, t);
	}
}
