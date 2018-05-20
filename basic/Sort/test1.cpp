#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include <string>
using namespace std;

int main()
{
	vector<string>vec;
	vector<string>::iterator it;
	vec.push_back("www.uestc.edu.cn");
	vec.push_back("www.codeproject.com");
	vec.push_back("www.cnki.net");
	vec.push_back("www.163.com");
	vec.push_back("www.taobao.com");
	vec.push_back("www.baidu.com");
	cout << "排序前：" << endl;
	for (it = vec.begin(); it != vec.end(); it++)
	{
		cout << *it << endl;
	}
	sort(vec.begin(), vec.end(), less<string>());
	cout << "排序后：" << endl;
	for (it = vec.begin(); it != vec.end(); it++)
	{
		cout<<*it<<endl;
	}
	system("pause");
	return 0;
}