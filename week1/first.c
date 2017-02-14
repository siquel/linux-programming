/**
 * fork question.
 *
 * What is output at LINE A?
 *
 * What is output at LINE B?
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int value = 5;

int main(int argc, char *argv[])
{
pid_t pid;

	/* fork another process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n");

		return 1;
	}
	else if (pid == 0) { /* child process */
		value += 15;
		printf("I am the child - value = %d\n",value); /* LINE A */
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		wait(NULL);
	
		printf("Child Completed ....\n");	
		printf("I am the parent - value = %d\n",value); /* LINE B */
	}

	return 0;
}
