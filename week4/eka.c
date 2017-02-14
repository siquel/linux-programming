#include <unistd.h> // fork
#include <stdio.h> // fprintf
#include <stdlib.h> // free
#include <ctype.h> // toupper
#include <string.h> // strlen
int main() 
{
    int parent_pipes[2]; // parent  reads from 0, child writes to 1
    int child_pipes[2]; // child reads from 0, parent writes to 1

    if (pipe(parent_pipes) || pipe(child_pipes))
    {
        fprintf(stderr, "failed to pipe\n");
        return 1;
    }

    int pid = fork();

    if (pid == -1) 
    {
        fprintf(stderr, "failed to fork()");
        return 1;
    }

    // parent
    if (pid != 0)
    {
        int in = parent_pipes[0];
        int out = child_pipes[1];
    
        char* line = NULL;
        size_t size;
        while (getline(&line, &size, stdin) != -1)
        {
            write(out, line, size + 1);
            char buf[256];
            read(in, buf, sizeof(buf));
            printf("PARENT<< %s", buf);
            free(line);
            line = NULL;
        }
    }
    // child
    else
    {
        int out = parent_pipes[1];
        int in = child_pipes[0];

        char buffer[256] = {0};
        while (1)
        {
            read(in, buffer, sizeof(buffer));
            printf("CHILD<< %s", buffer);
            for (char* p = buffer; *p; ++p) *p = toupper(*p);

            write(out, buffer, strlen(buffer) + 1);
        }
    }


    return 0;
}
