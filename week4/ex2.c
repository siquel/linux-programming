#include <sys/types.h> // waitpid
#include <sys/wait.h> // waitpid
#include <unistd.h> // fork
#include <stdio.h> // fprintf
#include <sys/time.h> // rusage
#include <sys/resource.h> // rusage
int main(void)
{

    struct rusage before_function_usage;
    getrusage(RUSAGE_SELF, &before_function_usage);

    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Failed to fork()\n");
    }
    else if (pid == 0)
    {
        for (volatile int i = 0; i < 999999999; ++i);
    }

    int status;
    waitpid(-1, &status, 0);

    if (pid != 0)
    {
        struct rusage child_func_usage;
        getrusage(RUSAGE_CHILDREN, &child_func_usage);
        suseconds_t cpu_usage_sec = child_func_usage.ru_stime.tv_sec;
        suseconds_t cpu_usage_msec = child_func_usage.ru_stime.tv_usec;
    
        suseconds_t cpu_user_usage_sec = child_func_usage.ru_utime.tv_sec;
        suseconds_t cpu_user_usage_usec = child_func_usage.ru_utime.tv_usec;

        printf("System CPU time used %d secs %d microsecs\n", cpu_usage_sec, cpu_usage_msec);
        printf("User CPU time used %d secs %d microsecs\n", cpu_user_usage_sec, cpu_user_usage_usec);
    }

    return 0;
}
