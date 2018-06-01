#include <iostream>  
#include <vector>  
#include <string>  
#include <io.h> 
#include <list>
#include <algorithm>
#include <time.h>

using namespace std;

typedef struct Node {
	string name;
	string path;
	unsigned long size;
	string extend;
	time_t timeCreate;
	time_t timeAccess;
	time_t timeWrite;
}fileNode;

void scanFile(string path, list<fileNode> &dirpath, vector<string> &extend);
string byteToStr(unsigned long size);
string getFileExtend(string name);
void printDirectory(list<fileNode> dirpath);
void printExtend(vector<string> &extend);
void findFileExtend(list<fileNode> dirpath,string ext);//查找所有特定后缀ext的文件
void findFileExtendSize(list<fileNode> dirpath, string ext,int min,int max);//查找所有大小在min和max之间的特定后缀ext的文件


void scanFile(string path, list<fileNode> &dirpath, vector<string> &extend) {
	struct _finddata_t fileinfo;  
	long ld;
	if ((ld = _findfirst((path + "\\*").c_str(), &fileinfo)) != -1l) {
		do {
			if ((fileinfo.attrib&_A_SUBDIR)) {  //如果是文件夹；
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {  
					scanFile(path + "\\" + fileinfo.name, dirpath, extend);  //递归子文件夹；  
				}
				
			}
			else   //如果是文件；  
			{
				fileNode node;
				node.path = path + "\\" + fileinfo.name;
				node.name = fileinfo.name;
				node.size = fileinfo.size;
				node.extend = getFileExtend(fileinfo.name);
				node.timeCreate = fileinfo.time_create;
				node.timeAccess = fileinfo.time_access;
				node.timeWrite = fileinfo.time_write;
				vector<string>::iterator it = find(extend.begin(), extend.end(), node.extend);
				if (it == extend.end()) { extend.push_back(node.extend); }
				dirpath.push_back(node);
			}
		} while (_findnext(ld, &fileinfo) == 0);
		_findclose(ld);
	}
}

string byteToStr(unsigned long size)
{
	string strSize;
	double temp = (float)size / 1024;
	if (temp <= 1024) {

		strSize =to_string(temp) + "KB";
	}
	else {
		strSize = to_string(temp / 1042) + "MB" + to_string(temp) + "KB";
	}
	return strSize;
}

string getFileExtend(string name)
{
	int index = name.find_first_of(".");
	string str = name.erase(0, index+1);
	return str;
}

void printDirectory(list<fileNode> dirpath)
{
	list<fileNode>::iterator it;
	for (it = dirpath.begin(); it != dirpath.end(); it++)
	{
		cout << (*it).path << endl;
	}

}

void printExtend(vector<string>& extend)
{
	vector<string>::iterator it;
	for (it = extend.begin(); it != extend.end(); it++)
	{
		cout << (*it) << endl;
	}
}

void findFileExtend(list<fileNode> dirpath,string ext)
{
	list<fileNode>::iterator it;
	for (it = dirpath.begin(); it != dirpath.end(); it++)
	{
		if (ext == (*it).extend)
		{
			string str = byteToStr((*it).size);
			cout <<"文件名:"<< (*it).name << endl;
			cout << "目录:" << (*it).path << endl;
			cout << "文件大小:" << str <<"\n"<< endl;
		}
	}
}

void findFileExtendSize(list<fileNode> dirpath, string ext, int min, int max)
{
	list<fileNode>::iterator it;
	
	for (it = dirpath.begin(); it != dirpath.end(); it++)
	{
		if (ext == (*it).extend)
		{
			int temp = (*it).size / 1024;
			if (temp <= max && temp >= min)
			{
				struct tm time1,time2,time3;
				localtime_s(&time1, &((*it).timeCreate));
				localtime_s(&time2, &((*it).timeAccess));
				localtime_s(&time3, &((*it).timeWrite));
				string str = byteToStr((*it).size);
				cout << "文件名:" << (*it).name << endl;
				cout << "目录:" << (*it).path << endl;
				cout << "文件大小:" << str  << endl;
				cout << "创建时间:";
				cout << time1.tm_year + 1900 << "-";
				cout << time1.tm_mon + 1 << "-";
				cout << time1.tm_mday<<" ";
				cout << time1.tm_hour << ":";
				cout << time1.tm_min << ":";
				cout << time1.tm_sec << endl;
				cout << "最后一次访问时间:";
				cout << time2.tm_year + 1900 << "-";
				cout << time2.tm_mon + 1 << "-";
				cout << time2.tm_mday << " ";
				cout << time2.tm_hour << ":";
				cout << time2.tm_min << ":";
				cout << time2.tm_sec << endl;
				cout << "最后修改时间:";
				cout << time3.tm_year + 1900 << "-";
				cout << time3.tm_mon + 1 << "-";
				cout << time3.tm_mday << " ";
				cout << time3.tm_hour << ":";
				cout << time3.tm_min << ":";
				cout << time3.tm_sec <<"\n"<< endl;
			}
			
		}
	}
}



int main() {
	string  path = "F:\\目录";   
	list<fileNode> dirpath;      
	vector<string> extend;
	scanFile(path, dirpath, extend);
	vector<string>::iterator it;
	while (true) {
		int flag = 0,mins=0,maxs=0;
		string ext;
		cout << endl;
		cout << "请输入操作数：\n1.退出\n2.打印目录\n3.打印扩展名\n4.查找扩展名\n5.查找扩展名(指定文件大小区间)\n" << endl;
		cin >> flag;
		switch (flag) {
		case 1:
			return 0;
		case 2:
			printDirectory(dirpath);
			system("pause");
			break;
		case 3:
			printExtend(extend);
			system("pause");
			break;
		case 4:
			
			cout << "请输入拓展名:" << endl;
			cin >> ext;
			findFileExtend(dirpath, ext);
			system("pause");
			break;
		case 5:
			cout << "请输入拓展名:" << endl;
			cin >> ext;
			cout << "请输入上限（单位KB）:" << endl;
			cin >> maxs;
			cout << "请输入下限（单位KB）:" << endl;
			cin >> mins;
			findFileExtendSize(dirpath, ext, mins, maxs);
			system("pause");
			break;
		}
	}
	cout << "退出" << endl;
	system("pause");
	return 0;
}