#include <stdio.h>
#include <stdlib.h>

void main(void) 
{
	int row,column;
	printf("Enter rows and column of matrix: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&row,&column);
	
	int a[row][column],b[column][row];
	printf("Enter elements of matrix:\n");
	for(int i=0; i<row; i++)
	{
		for(j=0; j<column; j++)
		{
			printf("Enter element a%d%d: ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%d",&a[i][j]);
		}
	}
	
	printf("The Entered Matrix:\n");
	for(int i=0; i<row; i++)
	{
		for(j=0; j<column; j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	
	printf("The Transposed of Matrix:\n");
	for(int i=0; i<column; i++)
	{
		for(j=0; j<row; j++)
		{
			b[i][j] = a[j][i];
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
}