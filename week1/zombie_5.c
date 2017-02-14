#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
      pid_t pid =0; 
        
      for (int i = 0; i < 5; ++i)
      {
          if ((pid = fork()) == 0) break;
      }

      if (pid > 0)
      {
          printf("parent process %d\n", getpid());

          sleep(60);
      }
      else
      {
          printf("child process %d, parent process %d\n", getpid(), getppid());
          exit(0);
      }
    exit(0);
}
