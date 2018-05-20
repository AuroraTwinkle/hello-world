#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;



int main()
{
	vector<string>vec;
	vector<string>::iterator it;
	map<string, string> mapStr;
	map<string, string>::reverse_iterator iter;
	vec.push_back("www.uestc.edu.cn");
	vec.push_back("www.codeproject.com");
	vec.push_back("www.cnki.net");
	vec.push_back("www.163.com");
	vec.push_back("www.taobao.com");
	vec.push_back("www.baidu.com");
	for (it = vec.begin(); it != vec.end(); it++)
	{
		int index1, index2;
		string str,keyStr;
		str = *it;
		index1 = str.find_first_of('.', 0);
		index2 = str.find_first_of('.', index1+1);
		keyStr=str.substr(index1 + 1, index2 - index1-1);
		mapStr.insert(pair<string, string>(keyStr, str));
	}
	cout << "提取到的关键记忆字符串：" << endl;
	for (iter = mapStr.rbegin(); iter != mapStr.rend(); iter++)
	{
		cout << iter->first << endl;
	}
	cout << "请输入你要查询关键字(按Q退出查询)：" << endl;
	string s;
	cin >> s;
	while (s !="Q")
	{
		cout << mapStr[s] << endl;
		cin >> s;
	}
	system("pause");
	return 0;
}

