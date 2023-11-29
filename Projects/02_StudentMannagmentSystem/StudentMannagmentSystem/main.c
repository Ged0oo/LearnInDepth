#include "student.h"

void main(void)
{
	int option;
	ST_FIFO_t queue;
	ST_Student_t students[MAX_STUDENT_NUMER];
	EN_FIFO_RET_t ret = FIFO_Init(&queue, &students, MAX_STUDENT_NUMER);

	while (FIFO_NAK == ret)
	{
		printf("\n[ERROR] FIFO Intializatio Failed\n");
		ret = FIFO_Init(&queue, &students, MAX_STUDENT_NUMER);
	}

	while (1)
	{
		printf("\n\t\t\t\t********************************************\n");
		printf("\t\t\t\t* Choose the Task that you want to Perform *");
		printf("\n\t\t\t\t********************************************\n\n");
			 
		printf(" 1- Add the Student Details Manually\n");
		printf(" 2- Add the Student Details From Text File\n");
		printf(" 3- Find the Student Details by Roll Number\n");
		printf(" 4- Find the Student Details by First Name\n");
		printf(" 5- Find the Student Details by Course id\n");
		printf(" 6- Find the Total Number of Students\n");
		printf(" 7- Delete the Students Details by Roll Number\n");
		printf(" 8- Update the students Details by Roll Number\n");
		printf(" 9- Show All Information\n");
		printf(" 10- Exit\n");

		printf(" \nEnter your Choice to Perform the task : ");
		scanf("%d", &option);
		printf("\n=======================================================\n");

		switch (option)
		{
			case 1: Student_Add_Manually(&queue); break;
			case 2: Student_Add_From_File(&queue); break;
			case 3: Find_StudentFrom_ID(&queue); break;
			case 4:  Find_Student_From_FirstName(&queue); break;
			case 5: Find_Student_From_Course_ID(&queue); break;
			case 6: Print_Student_Count(&queue); break;
			case 7: Delete_Student_With_ID(&queue); break;
			case 8:  Delete_Student_With_ID(&queue); break;
			case 9: Show_Student_Data_Base(&queue); break;
			case 10:  return 1; break;
			default: break;
		}
	}
}