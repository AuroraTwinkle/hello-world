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
void findFileExtend(list<fileNode> dirpath,string ext);//���������ض���׺ext���ļ�
void findFileExtendSize(list<fileNode> dirpath, string ext,int min,int max);//�������д�С��min��max֮����ض���׺ext���ļ�


void scanFile(string path, list<fileNode> &dirpath, vector<string> &extend) {
	struct _finddata_t fileinfo;  
	long ld;
	if ((ld = _findfirst((path + "\\*").c_str(), &fileinfo)) != -1l) {
		do {
			if ((fileinfo.attrib&_A_SUBDIR)) {  //������ļ��У�
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {  
					scanFile(path + "\\" + fileinfo.name, dirpath, extend);  //�ݹ����ļ��У�  
				}
				
			}
			else   //������ļ���  
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
			cout <<"�ļ���:"<< (*it).name << endl;
			cout << "Ŀ¼:" << (*it).path << endl;
			cout << "�ļ���С:" << str <<"\n"<< endl;
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
				cout << "�ļ���:" << (*it).name << endl;
				cout << "Ŀ¼:" << (*it).path << endl;
				cout << "�ļ���С:" << str  << endl;
				cout << "����ʱ��:";
				cout << time1.tm_year + 1900 << "-";
				cout << time1.tm_mon + 1 << "-";
				cout << time1.tm_mday<<" ";
				cout << time1.tm_hour << ":";
				cout << time1.tm_min << ":";
				cout << time1.tm_sec << endl;
				cout << "���һ�η���ʱ��:";
				cout << time2.tm_year + 1900 << "-";
				cout << time2.tm_mon + 1 << "-";
				cout << time2.tm_mday << " ";
				cout << time2.tm_hour << ":";
				cout << time2.tm_min << ":";
				cout << time2.tm_sec << endl;
				cout << "����޸�ʱ��:";
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
	string  path = "F:\\Ŀ¼";   
	list<fileNode> dirpath;      
	vector<string> extend;
	scanFile(path, dirpath, extend);
	vector<string>::iterator it;
	while (true) {
		int flag = 0,mins=0,maxs=0;
		string ext;
		cout << endl;
		cout << "�������������\n1.�˳�\n2.��ӡĿ¼\n3.��ӡ��չ��\n4.������չ��\n5.������չ��(ָ���ļ���С����)\n" << endl;
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
			
			cout << "��������չ��:" << endl;
			cin >> ext;
			findFileExtend(dirpath, ext);
			system("pause");
			break;
		case 5:
			cout << "��������չ��:" << endl;
			cin >> ext;
			cout << "���������ޣ���λKB��:" << endl;
			cin >> maxs;
			cout << "���������ޣ���λKB��:" << endl;
			cin >> mins;
			findFileExtendSize(dirpath, ext, mins, maxs);
			system("pause");
			break;
		}
	}
	cout << "�˳�" << endl;
	system("pause");
	return 0;
}