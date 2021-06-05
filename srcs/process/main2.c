#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int id = fork();
    int n;
    if (id == 0)
        n = 1;
    else
        n = 6;
    if (id != 0)
        wait(NULL);

    int i;
    for(i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        fflush(stdout);
    }
    puts("\n");
    return(0);
}

// The main process wait the child process to finsh his work, then main process continue his work
// I think when we use fork, the compilation splited to two parts
// and I think the fork id is very important to 