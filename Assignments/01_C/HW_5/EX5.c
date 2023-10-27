#include <stdio.h>

typedef struct
{

	char* name;
	int ID;
}employee;

void main(void)
{
	employee emp[3] = { {"Mohamed",20012409},{"Nagy",20012410},{"Mabrock",20012411} };
	employee* arr[3] = { &emp[0],&emp[1],&emp[2] };
	employee* (*ptr)[3] = &arr;

	printf("Employee Name: %s\n", (*(*ptr + 1))->name);
	printf("Employee ID : %d", (*(*ptr + 1))->ID);
}