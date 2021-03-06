#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define SIZE 1009

void Guide();							  //开始界面
void InitContact();						  //初始化联系人数组
void AddFileContact();					  //从文件导入
void ExportContact();					  //导出到文件
bool SearchContact(char *string, int *p); //查找函数
void NewContact();
void DeleteContact(char *string);		 //删除函数
void ShowContact();						 //展示联系人
void CollisionDeal(char *string, int i); //冲突处理
void Modify(char *string);				 //修改联系人
int Hashs(char *string);				 //哈希函数
bool Save();
int turn[1009]; //用来存储由哈希函数获得的地址方便遍历
int Flag = 0;   //该全局变量用来记录当前联系人数量
char names[20]; //用来存储从键盘获取的临时数据

typedef struct contact
{
	char name[20];
	char phone[15];
	char address[50];
} Contact;

Contact contact[SIZE]; //全局数组，电话本容量

int main(void)
{
	InitContact();
	while (1)
	{
		int choice = 0, j = 0;
		Guide();
		scanf("%d", &choice);
		while (choice <= -1 || choice >= 10)
		{
			printf("please input right choice\n");
			scanf("%d", &choice);
		}
		switch (choice)
		{

		case 1:
			ShowContact();
			break;
		case 2:
			AddFileContact();
			break;
		case 3:
			ExportContact();
			break;
		case 4:

			printf("please input name that you want to search:\n");
			scanf("%s", names);
			if (SearchContact(names, &j))
			{
				printf("name:%s\tphonenumber:%s\taddress:%s\t\n", contact[j].name, contact[j].phone, contact[j].address);
				printf("*******************************************************************************\n");
			}
			else
			{
				printf("the contact don't exist\n");
				printf("if you want to add it,please input \"5\"\n");
			}
			break;
		case 5:
			NewContact();
			break;
		case 6:
			printf("please input the name that you want to delete:\n");
			scanf("%s", names);
			DeleteContact(names);
			break;
		case 7:
			printf("please input name that you want to modify:\n");
			scanf("%s", names);
			Modify(names);
			break;
		default:;
		}
		if (choice == 8)
			break;
	}
}

void AddFileContact()
{
	FILE *fp;
	char ch[20];
	if ((fp = fopen("import.txt", "r")) == NULL)
	{
		printf("failed to open this file!\n");
		return;
	}
	while (!feof(fp))
	{
		int j = 0;
		fscanf(fp, "%s", &names);
		if (!SearchContact(names, &j))
		{
			int i = Hashs(names);
			strcpy(contact[i].name, names);
			fscanf(fp, "%s", &contact[i].phone);
			fscanf(fp, "%s", &contact[i].address);
			turn[Flag++] = i;
		}
		else
		{
			fscanf(fp, "%s", &ch);
			fscanf(fp, "%s", &ch);
		}
	}
	fclose(fp);
	printf("success!\n");
}

void ExportContact()
{
	char ch;
	FILE *fp;
	if ((fp = fopen("export.txt", "w")) == NULL)
	{
		printf("failed to open this file!\n");
		return;
	}
	fprintf(fp, "name:               phonenumber:   ddress:\n");
	for (int i = 0; i < Flag; i++)
	{
		int k = turn[i];
		for (int j = 0; j < 20; j++)
		{
			ch = contact[k].name[j];
			putc(ch, fp);
		}
		for (int j = 0; j < 15; j++)
		{
			ch = contact[k].phone[j];
			putc(ch, fp);
		}
		for (int j = 0; j < 50; j++)
		{
			ch = contact[k].address[j];
			putc(ch, fp);
		}
		fprintf(fp, "%s", "\n");
	}
	printf("success!\n");
	fclose(fp);
}

void NewContact()
{
	if (Flag >= 1009)
	{
		printf("it is full\n");
		return;
	}
	Save();
}

void DeleteContact(char *string)
{
	int temp;
	if (SearchContact(string, &temp))
	{
		memset(contact[temp].name, '\0', sizeof(contact[temp].name));
		contact[temp].phone[0] = '#';
		for (int i = 0; i < Flag; i++)
		{
			if (turn[i] == temp)
			{
				for (int k = i; k < Flag; k++)
				{
					turn[k] = turn[k + 1];
					turn[k + 1] = turn[k + 2];
				}
			}
		}
		Flag--;
	}
}

void ShowContact()
{
	if (Flag == 0)
	{
		printf("it is empty!\n");
		return;
	}
	for (int i = 0; i < Flag; i++)
	{
		int j = turn[i];
		if (contact[j].phone[0] != '#')
		{
			printf("name:%s\tphonenumber:%s\taddress:%s\t\n", contact[j].name, contact[j].phone, contact[j].address);
			printf("*******************************************************************************\n");
		}
	}
}

bool SearchContact(char *string, int *p)
{
	int i = 0;
	i = Hashs(string);
	int d = 1;
	while (strcmp(contact[i].name, string) != 0 && d < SIZE)
	{
		i = (i + d) % SIZE;
		d++;
	}
	if (d < SIZE)
	{
		*p = i;
		return true;
	}
	else
	{
		return false;
	}
}

void Guide()
{
	printf("\nwhat do you want to do?\n");
	printf("1.show all contacts\n2.add from file\n3.export to file\n");
	printf("4.search for contact\n5.build a new contact\n");
	printf("6.delete contact\n7.modify contact\n8.exit\n");
}

int Hashs(char *string)
{
	int sum = 0;
	for (int i = 0; i < 20; i++)
	{
		sum += toascii(string[i]);
	}
	return sum % SIZE;
}

void InitContact()
{
	for (int i = 0; i < 1009; i++)
	{
		contact[i].phone[0] = '#';
	}
}

void CollisionDeal(char *string, int i)
{
	i = Hashs(string);
	int d = 1;
	while (strcmp(contact[i].name, string) != 0 && d < SIZE)
	{
		i = (i + d) % SIZE;
		d++;
	}
}

bool Save()
{
	int i = 0, j;
	printf("please input name:\n");
	scanf("%s", names);
	i = Hashs(names);
	if (SearchContact(names, &j))
	{
		printf("this contact has existed!\nyou can input \"7\" to modify it.\n");
		return false;
	}
	//printf("i:%d\n",i);
	else if (contact[i].phone[0] == '#')
	{
		turn[Flag++] = i;
		strcpy(contact[i].name, names);
		printf("please input phone:\n");
		scanf("%s", &contact[i].phone);
		printf("please input address:\n");
		scanf("%s", &contact[i].address);
		printf("success!\n");
		return true;
	}
}

void Modify(char *string)
{
	int temp;

	if (SearchContact(string, &temp))
	{
		char choose;
		printf("the contact has existed,do you want to modify it? Y or N?\n");
		scanf("%s", &choose);
		if (choose == 'N')
			return;
		else if (choose == 'Y')
		{
			DeleteContact(names);
			Save();
		}
	}
}
