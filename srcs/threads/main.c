//Differnce  eween processes and threads
#include <pthread.h>  
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

// int main()
// {
//     int pid = fork();
//     if (pid == -1)
//         return (1);
//     puts("Hello from processes\n");
//     if (pid != 0)
//         wait(NULL);
//     return (0);
// }

int x = 3;
void    *routine()
{
    x += 3;
    sleep(2);
    printf("hello from threadsx:%d\n", x);
    return (NULL);
}

void    *routine2()
{
    sleep (2);
    printf("Hello from threads x:%d\n", x);
    return (NULL);
}

int main(int ac, char **av)
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL))
        return (1);
    if (pthread_create(&t2, NULL, &routine2, NULL))
        return 1;
    if (pthread_join(t1, NULL))
        return 2;
    if (pthread_join(t2, NULL))
        return 2;
}
