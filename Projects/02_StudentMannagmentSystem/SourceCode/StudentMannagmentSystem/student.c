#include "student.h"


EN_FIFO_RET_t FIFO_Init(ST_FIFO_t* _queue, ST_Student_t* _student, uint32_t _length)
{
	EN_FIFO_RET_t ret = FIFO_NAK;
	if (NULL == _student)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		ret = FIFO_NAK;
	}
	else
	{
		_queue->base = _student;
		_queue->head = _student;
		_queue->tail = _student;
		_queue->lenght = _length;
		_queue->count = 0;
		ret = FIFO_ACK;
	}
	return ret;
}


EN_FIFO_RET_t FIFO_Enqueue(ST_FIFO_t* _queue, ST_Student_t _student)
{
	EN_FIFO_RET_t ret = FIFO_NAK;
	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		ret = FIFO_NAK;
	}
	else if (FIFO_FULL == FIFO_Is_Full(_queue))
	{
		ret = FIFO_FULL;
	}
	else
	{
		*(_queue->head) = _student;
		_queue->count += 1;
		if (_queue->head == (_queue->base) + (_queue->lenght * sizeof(ST_Student_t)))
		{
			_queue->head = _queue->base;
		}
		else
		{
			_queue->head += 1;
		}
		ret = FIFO_ACK;
	}
	return ret;
}


EN_FIFO_RET_t FIFO_Is_Full(ST_FIFO_t* _queue)
{
	EN_FIFO_RET_t ret = FIFO_NAK;
	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		ret = FIFO_NAK;
	}
	else
	{
		if (_queue->count == _queue->lenght)
		{
			printf("\n [ERROR] Enqueue Failde ==> Queue Full\n");
			ret = FIFO_FULL;
		}
		else
		{
			ret = FIFO_ACK;
		}
	}
	return ret;
}


EN_FIFO_RET_t Student_Add_Manually(ST_FIFO_t* _queue)
{
	EN_FIFO_RET_t ret = FIFO_NAK;
	ST_Student_t newStudent;

	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		ret = FIFO_NAK;
	}
	else if (FIFO_FULL == FIFO_Is_Full(_queue))
	{
		ret = FIFO_FULL;
	}
	else
	{
		printf("\nEnter Student Data\n");

		printf("Enter Student roll Number : ");
		int _roll;
		flush;
		scanf("%d", &_roll);
		if (Check_Student_ID(_queue, _roll))
		{
			//error
			printf("\n [ERROR] Roll Number %d is already exist\n", _roll);
			ret = FIFO_NAK;
		}
		else 
		{
			newStudent.rollNumber = _roll;
			printf("Enter Student First Name : ");
			flush;
			scanf("%s",newStudent.firstName);

			printf("Enter Student Last Name : ");
			flush;
			scanf("%s", newStudent.lastName);

			printf("Enter Student GPA : ");
			flush;
			scanf("%f", &newStudent.gpa);

			for (int i = 0; i < COURSES_NUMBER; i++)
			{
				printf("Enter Course ID NO.%d : ", i + 1);
				flush;
				scanf("%d", &newStudent.courseID[i]);
			}

			if (FIFO_ACK == FIFO_Enqueue(_queue, newStudent))
			{
				printf("\n  [INFO] Student Enqueued Successfully\n");
			}
			else
			{
				printf("\n  [ERROR] Student Enqueued Failed\n");
				ret = FIFO_NAK;
			}
			ret = FIFO_ACK;
		}

		
	}
	return ret;
}

/* returns the student if exist and NULL if not exist*/
ST_Student_t * Check_Student_ID(ST_FIFO_t* _queue, int _id)
{
	ST_Student_t *temp = _queue->tail;
	for (int i = 0 ; i < _queue->count ; i++)
	{
		if (temp->rollNumber == _id)
			return temp;
		else
			temp++;
	}
	return NULL;
}


EN_FIFO_RET_t Student_Add_From_File(ST_FIFO_t* _queue)
{
	EN_FIFO_RET_t ret = FIFO_NAK;
	ST_Student_t newStudent;
	FILE* StudentFile;

	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		ret = FIFO_NAK;
	}
	else if (FIFO_FULL == FIFO_Is_Full(_queue))
	{
		ret = FIFO_FULL;
	}
	else
	{
		StudentFile = fopen("Student_DataStructure.txt", "r");
		if (NULL == StudentFile)
		{
			printf("\n [ERROR] File Open ==> Failed\n");
			ret = FIFO_NAK;
		}
		else
		{
			while (!feof(StudentFile))
			{
				fscanf(StudentFile, "%d", &newStudent.rollNumber);
				if (Check_Student_ID(_queue, newStudent.rollNumber))
				{
					printf("\n [ERROR] Roll Number %d already exist\n", newStudent.rollNumber);
					fscanf(StudentFile, "%*[^\n]");
					continue;
				}
				else
				{
					fscanf(StudentFile, "%s", newStudent.firstName);
					fscanf(StudentFile, "%s", newStudent.lastName);
					fscanf(StudentFile, "%f", &newStudent.gpa);

					for (int i = 0; i < COURSES_NUMBER; i++)
					{
						fscanf(StudentFile, "%d", &newStudent.courseID[i]);
					}

					if (FIFO_Enqueue(_queue, newStudent) == FIFO_ACK)
					{
						printf("\n [INFO] Roll Number %d saved Succsesfully\n", newStudent.rollNumber);
					}
					else
					{
						printf("\n [ERROR] Adding Stident From File Failed\n");
					}
				}

			}
			printf("\n [INFO] File Content Saved Successflly\n");
			fclose(StudentFile);
			ret = FIFO_ACK;
		}
	}
	return ret;
}


void Find_StudentFrom_ID(ST_FIFO_t* _queue)
{
	ST_Student_t *_student;
	int id;

	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		return;
	}

	printf("\nEnter Student ID : ");
	flush;
	scanf("%d", &id);

	_student = Check_Student_ID(_queue, id);
	if (NULL == _student)
	{
		printf("\n [ERROR] Can't find Student with ID Number %d\n", id);
	}
	else
	{
		printf("Student with ID:%d found\n");
		Print_Student(_student);
	}
}


void Print_Student(ST_Student_t *_student)
{
	printf("=============================================\n");
	
	printf("Student ID : %d\n", _student->rollNumber);
	printf("Student First Name : %s\n", _student->firstName);
	printf("Student Last NAme : %s\n", _student->lastName);
	printf("Student GPA : %.2f\n", _student->gpa);

	for (int i = 0; i < COURSES_NUMBER; i++)
		printf("Course NO.%d has ID : %d\n", i + 1, _student->courseID[i]);
	
	printf("=============================================\n");
}


void Find_Student_From_FirstName(ST_FIFO_t* _queue)
{
	ST_Student_t *_student = _queue->tail;
	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		return;
	}
	else if (0 == _queue->count)
	{
		printf("\n [ERROR] Student Data Base Empty ==> Failed\n");
		return;
	}

	printf("Enter Student First Name : ");
	char name[MAX_NAME_LENGTH], flag=0;
	scanf("%s", name);

	for (int i = 0; i < _queue->count; i++)
	{
		if (0 == strcmp(name, _student->firstName))
		{
			printf("Student with Name : %s found\n", name);
			flag = 1;
			Print_Student(_student);
			return;
		}
		if ((_student + 1) == (_queue->base + _queue->lenght))
		{
			_student = _queue->base;
		}
		else
		{
			_student++;
		}
	}
	if (0 == flag)
	{
		printf("\n [ERROR] Student with Name : %s Not Fount\n", name);
		return;
	}
}


void Find_Student_From_Course_ID(ST_FIFO_t* _queue)
{
	ST_Student_t* _student = _queue->tail;
	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		return;
	}
	else if (0 == _queue->count)
	{
		printf("\n [ERROR] Student Data Base Empty ==> Failed\n");
		return;
	}

	int courseID, count=0;
	printf("Enter Course ID : ");
	flush;
	scanf("%d", &courseID);

	for (int i = 0; i < _queue->count; i++)
	{
		for (int j = 0; j < COURSES_NUMBER; j++)
		{
			Print_Student(_student);
			count++;
		}
		_student++;
	}

	if (0 == count)
	{
		printf("\n [ERROR] Course ID not found\n");
		return;
	}
	else
	{
		printf("The Course with ID:%d found %n time\n", courseID, count);
	}
}


void Delete_Student_With_ID(ST_FIFO_t* _queue)
{
	ST_Student_t* _student = _queue->tail;
	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		return;
	}
	else if (0 == _queue->count)
	{
		printf("\n [ERROR] Student Data Base Empty ==> Failed\n");
		return;
	}

	int id, flag=0;
	printf("Entere Student ID : ");
	flush;
	scanf("%d", &id);

	for (int i = 0; i < _queue->count; i++)
	{
		if (id == _student->rollNumber)
		{
			flag = 1;
			*_student = *(_queue->tail);
			_queue->count -= 1;

			if ((_queue->base + _queue->lenght) == (_queue->tail + 1))
			{
				_queue->tail = _queue->base;
			}
			else
			{

				_queue->tail += 1;
			}

			break;
		}
		_student++;
	}

	if (0 == flag)
	{
		printf("\n [ERROR] Student with ID:%d not Found\n", id);
	}
	else
	{
		printf("\n [INFO] Student with ID:%d Deleted Successfully\n", id);
	}
}


void Update_Student_With_ID(ST_FIFO_t* _queue)
{
	ST_Student_t* _student = _queue->tail;
	ST_Student_t* studentMod;
	int id, newID, flag=0;

	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		return;
	}
	else if (0 == _queue->count)
	{
		printf("\n [ERROR] Student Data Base Empty ==> Failed\n");
		return;
	}

	printf("Entere Student ID : ");
	flush;
	scanf("%d", &id);

	studentMod = Check_Student_ID(_queue, id);
	if (studentMod)
	{
		printf("Student Found\n");
		Print_Student(_student);
	}
	else
	{
		printf(" [ERROR] Student with ID:%d not Found\n", id);
		return;
	}

	int operation;
	printf("\nAllowed Student Parameters to Change : \n");
	printf("1-Student ID\n");
	printf("2-Student First Name\n");
	printf("3-Student Last Name\n");
	printf("4-Student GPA\n");
	printf("5-Student Course ID\n");
	printf("Enter the Required Operation : ");
	flush;
	scanf("%d", &operation);

	switch (operation)
	{
		case 1:
			printf("Enter New Student ID\n");
			flush;
			scanf("%d", &newID);

			for (int i = 0; i < _queue->count; i++)
			{
				if (newID == _student->rollNumber)
				{
					flag = 1;
					printf("\n [ERROR] Studen with ID Number already Exist\n");
					break;
				}

				if ((_queue->base + _queue->lenght) == (_student + 1))
				{
					_student = _queue->base;
				}
				else
				{
					_student++;
				}
			}

			if (0 == flag)
			{
				studentMod->rollNumber = newID;
				printf("\n [INFO] Student ID Number Updated Successfully\n");
				Print_Student(studentMod);
			}
			break;

		case 2:
			printf("Enter New Student First Name : ");
			scanf("%s", studentMod->firstName);
			printf("\n [INFO] Student First Name Updated Successfully\n");
			Print_Student(studentMod);
			break;

		case 3:
			printf("Enter New Student Last Name : ");
			scanf("%s", studentMod->lastName);
			printf("\n [INFO] Student Last Name Updated Successfully\n");
			Print_Student(studentMod);
			break;

		case 4:
			printf("Enter New Student GPA : ");
			fflush;
			scanf("%f", &studentMod->gpa);
			printf("\n [INFO] Student GPA Updated Successfully\n");
			Print_Student(studentMod);
			break;

		case 5:
			printf("Enter New Course Number to update[1:%d] : ", COURSES_NUMBER);
			int course;
			flush;
			scanf("%d", &course);
			printf("Enter New Course ID : ");
			flush;
			scanf("%d", &studentMod->courseID[course - 1]);
			printf("\n [INFO] Student Course Number Updated Successfully\n");
			Print_Student(studentMod);
			break;

		default:
			printf("\n [ERROR] Unallowed Operation\n");
			break;
	}
}


void Print_Student_Count(ST_FIFO_t* _queue)
{
	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		return;
	}
	else
	{
		printf("\n***********************************************\n");
		printf("* [INFO] The Total Number of Students is %d\n", _queue->count);
		printf("* [INFO] You Can Add up to %d Students\n", MAX_STUDENT_NUMER);
		printf("* [INFO] You Can Add %d more Students\n", MAX_STUDENT_NUMER - _queue->count);
		printf("***********************************************\n");
	}
}


void Show_Student_Data_Base(ST_FIFO_t* _queue)
{
	ST_Student_t* _student = _queue->tail;
	if (NULL == _queue)
	{
		printf("\n [ERROR] Queue Data Base Initialization ==> Failed\n");
		return;
	}
	else if (0 == _queue->count)
	{
		printf("\n [ERROR] Student Data Base Empty ==> Failed\n");
		return;
	}
	else
	{
		for (int i = 0; i < _queue->count; i++)
		{
			Print_Student(_student);
			_student++;
		}
		Print_Student_Count(_queue);
	}
}