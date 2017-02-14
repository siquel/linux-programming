#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

static int32_t idx = 0;

typedef struct _Args
{
    char* buffer;
    char letter;
} Args;

void* threadProc(void* a)
{
    Args* args = (Args*)a;
    args->buffer[idx++] = args->letter;
    // xxxxx 
    union { void* p; int32_t i; } cast;
    cast.i = 0;
    return cast.p;
}

static char s_buffer[128];

int main(int argc, char** argv)
{
    pthread_t threads[5];
    
    const char word[] = "kamk";
    Args args[5] = {0};

    for (int i = 0; i < 5; ++i)
    {
        Args* arg = &args[i]; 
        arg->letter = word[i];
        args->buffer = s_buffer;
        if (pthread_create(&threads[i], NULL, threadProc, arg))
        {
            fprintf(stderr, "pthread_create failed\n");
            return 1;
        }
    }

    for (int i = 0; i < 5; ++i)
    {
        union { void* p; int32_t i; } cast;
        pthread_join(threads[i], &cast.p);
        printf("Thread exited with code %d\n", cast.i);
    }

    printf("final word: %s\n", s_buffer);

    return 0;
}
