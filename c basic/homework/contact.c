#include <stdio.h>
#include <stdlib.h>

void Guide();
void BuildContact();
void AddContact();
void ExportContact();
void SearchContact();
void NewContact();
void ModifyContact();
void DeleteContact();
void ShowContact();

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
			BuildContact();
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
		case 8:
			ShowContact();
			break;
		default:;
		}
		if (choice == 9)
			break;
	}
}

void BuildContact()
{
	;
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
	;
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
	printf("1.build a contact\n2.add from file\n3.export to file\n");
	printf("4.search for contact\n5.build a new contact\n6.modify contact\n");
	printf("7.delete contact\n8.show all contacts\n9.exit\n");
}