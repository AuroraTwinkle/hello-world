#include <iostream>  
#include <vector>  
#include <string>  
#include <io.h>  
using namespace std;
void scanFile(string path, vector<string> &dirpath);

void getfileall(string path, vector<string> &dirpath) {
	struct _finddata_t fileinfo;    //_finddata_t��һ���ṹ�壬Ҫ�õ�#include <io.h>ͷ�ļ���  
	long ld;
	if ((ld = _findfirst((path + "\\*").c_str(), &fileinfo)) != -1l) {
		do {
			if ((fileinfo.attrib&_A_SUBDIR)) {  //������ļ��У�  
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {  //����ļ�������.����,,,��ݹ��ȡ���ļ��е��ļ���  
					getfileall(path + "\\" + fileinfo.name, dirpath);  //�ݹ����ļ��У�  
				}
			}
			else   //������ļ���  
			{
				dirpath.push_back(path + "\\" + fileinfo.name);
				cout << path+"\\"+fileinfo.name << endl;  
			}
		} while (_findnext(ld, &fileinfo) == 0);
		_findclose(ld);
	}
}

int main() {
	string  path = "F:\\Ŀ¼";   //����\��ת���ַ�����ʼ�ַ���·����Ҫ��\\��Ҳ����ֻ��һ��/;  
	vector<string> dirpath;     //�����ļ���·����  
	getfileall(path, dirpath);
	getchar();
	return 0;
}