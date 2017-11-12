#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1009

void Guide();
void AddContact();
void ExportContact();
void SearchContact();
void NewContact();
void ModifyContact();
void DeleteContact();
void ShowContact();
int Hash(char *string);

typedef struct contact
{
	char name[20];
	char phone[15];
	char address[50];
}Contact;

Contact contact[SIZE];

int main(void)
{
	while (1)
	{
		int choice = 0;
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
			AddContact();
			break;
		case 3:
			ExportContact();
			break;
		case 4:
			SearchContact();
			break;
		case 5:
			NewContact();
			break;
		case 6:
			ModifyContact();
			break;
		case 7:
			DeleteContact();
			break;
		default:;
		}
		if (choice == 8)
			break;
	}
}

void AddContact()
{
	;
}

void ExportContact()
{
	;
}

void NewContact()
{
	char name[20];
	int i=0;
	printf("please input name:\n");
	scanf("%s",name);
	i = Hash(name);
	strcpy(Contact[i].name,name);
	printf("please input phone:\n");
	scanf("%s", &Contact[i].phone);
	printf("please input address:\n");
	scanf("%s", &Contact[i].address);
}

void DeleteContact()
{
	;
}

void ShowContact()
{
	;
}

void ModifyContact()
{
	;
}

void SearchContact()
{
	;
}

void Guide()
{
	printf("what do you want to do?\n");
	printf("1.show all contacts\n2.add from file\n3.export to file\n");
	printf("4.search for contact\n5.build a new contact\n6.modify contact\n");
	printf("7.delete contact\n8.exit\n");
}

int Hash(char *string)
{
	int sum=0;
	for(int i=0;i<20;i++)
	{
		sum += string[i];
	}
	return sum % SIZE;
}