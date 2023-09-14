#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>



int main(int argc, char *argv[])
{
	if(argc<3)
	{
		printf("Wrong Parameters\n");
		return 0;
	}
	char *var1;
	var1= argv[1];
	int x = atoi(var1); //converted integral number as an int value
	
	char *var2;
	var2 = argv[2];
	int y = atoi(var2);
	
	
	int list[x][y],i,j;
	srand(time(NULL));
	
	for(i=0; i<x; i++)
	{
		for(j=0;j<y;j++)
		{
			list[i][j] = (rand() % (20 - 1 + 1 )) +1;
		}
	}
	
	int fd1[x][2],fd2[x][2];
	int client,total_sum=0;
	for(i=0; i<x; i++)
	{
		pipe(fd1[i]);
		pipe(fd2[i]);
		client = fork();
		if(client == 0) //client
		{
			int row;
			read(fd1[i][0], &row,sizeof(int));
			close(fd1[i][1]);
			close(fd1[i][0]);
			int sum=0;
			for(j=0; j<y; j++)
			{
				sum = sum + list[row][j];
			}
			close(fd2[i][0]);
			write(fd2[i][1], &sum, sizeof(int));
			close(fd2[i][1]);
			exit(1);
		}
		else //server
		{
			int row;
			close(fd1[i][0]);
			write(fd1[i][1], &i, sizeof(int));
			close(fd1[i][1]);
			
			
			read(fd2[i][0], &row, sizeof(int));
			close(fd2[i][1]);
			close(fd2[i][0]);
			total_sum = total_sum +row;
			wait(NULL);
			
		}
	}
	printf("Total Sum: %d\n",total_sum);
	return 0;
}
//
