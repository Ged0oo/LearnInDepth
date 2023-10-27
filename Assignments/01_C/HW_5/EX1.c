#include <stdio.h>

struct student 
{
	char name[50];
	int roll;
	float marks;
}s;

void get_Data()
{
	printf("Enter name: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",s.name);
	
	printf("Enter roll number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&s.roll);
	
	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&s.marks);
}
void print_Data()
{
	printf("name: %s\nRoll: %d\nMarks: %0.2f",s.name,s.roll,s.marks);
}

void main(void) 
{
	puts("Enter information of students:");
	get_Data();

	puts("Displaying Information");
	print_Data();
}

