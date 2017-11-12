#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1009

void Guide();
void InitContact();
void AddContact();
void ExportContact();
void SearchContact();
void NewContact();
void ModifyContact();
void DeleteContact();
void ShowContact();
int Hash(char *string);
int turn[1009];
int Flag = 0;

typedef struct contact
{
	char name[20];
	char phone[15];
	char address[50];
} Contact;

Contact contact[SIZE];

int main(void)
{
	InitContact();
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
	int i = 0;
	printf("please input name:\n");
	scanf("%s", name);
	i = Hash(name);
	if (contact[i].phone[0] == '#')
	{
		turn[Flag++] = i;
		strcpy(contact[i].name, name);
		printf("please input phone:\n");
		scanf("%s", &contact[i].phone);
		printf("please input address:\n");
		scanf("%s", &contact[i].address);
	}
	else if (strcmp(contact[i].name, name) == 0)
	{
		char choose;
		printf("the contact has existed,do you want to cover it? Y or N?\n");
		scanf("%s", &choose);
		if (choose == 'N')
			return;
		else if (choose == 'Y')
		{
			printf("please input phone:\n");
			scanf("%s", &contact[i].phone);
			printf("please input address:\n");
			scanf("%s", &contact[i].address);
		}
	}
}

void DeleteContact()
{
	;
}

void ShowContact()
{
	for (int i = 0; i < Flag; i++)
	{
		int j = turn[i];
		printf("name:%s\tphonenumber:%s\taddress:%s\t\n", contact[j].name, contact[j].phone, contact[j].address);
		printf("%d\n", j);
		printf("*******************************************************************************\n");
	}
}

void ModifyContact()
{
	;
}

void SearchContact()
{
	char name[20];
	printf("please input name that you want to search:\n");
	scanf(("%s", name));
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
	int sum = 0;
	for (int i = 0; i < 20; i++)
	{
		sum += string[i];
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
1
