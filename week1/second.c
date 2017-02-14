/*How many unique processes are created using the following program?*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("%d\n",getpid());
	fork();
	printf("%d\n",getpid());
	

	fork();
	printf("%d\n",getpid());

	fork();
	printf("%d\n",getpid());

	return 0;
}
