#include <iostream>  
#include <vector>  
#include <string>  
#include <io.h> 
#include <list>
#include <algorithm>

using namespace std;

void scanFile(string path, list<string> &dirpath, vector<string> &extend);
string byteToStr(unsigned long size);
string getFileExtend(string name);

typedef struct Node {
	string name;
	string path;
	string size;
	string extend;
}fileNode;

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
				//fileNode node;
				//node.path = path + "\\" + fileinfo.name;
				//node.name = fileinfo.name;
				//node.size = byteToStr(fileinfo.size);
				//node.extend = getFileExtend(fileinfo.name);
				//vector<string>::iterator it = find(extend.begin, extend.cend, node.extend);
				//if (it == extend.cend) { extend.push_back(node.extend); }
				//dirpath.push_back(node);
				cout << path + "\\" + fileinfo.name << endl;

			}
		} while (_findnext(ld, &fileinfo) == 0);
		_findclose(ld);
	}
}

string byteToStr(unsigned long size)
{
	string strSize;
	int temp = size / 1024;
	if (temp <= 1024) {

		strSize = to_string(temp) + "KB";
	}
	else {
		strSize = to_string(temp / 1042) + "MB" + to_string(temp) + "KB";
	}
	return strSize;
}

string getFileExtend(string name)
{
	return string();
}



int main() {
	string  path = "F:\\目录";
	list<string> dirpath;
	vector<string> extend;
	scanFile(path, dirpath, extend);
	getchar();
	return 0;
}