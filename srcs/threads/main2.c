//What are Race Conditions??

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;

void    *routine(void *c)
{
    int i = 0;
    int *cc = (int *)c;
    *cc = 2;
    // int *cc = (int *)c;
    // printf("%d\n", *cc);
    while(i < 10000)
    {
        // c++;
        i++;
    }
    return (NULL);
}
  
int main()
{
    static int c = 1;
    pthread_t p1, p2;

    if(pthread_create(&p1, NULL, &routine, &c) != 0)
        return (1);
    if (pthread_create(&p2, NULL, &routine, &c) != 0)
        return (2);
    if (pthread_join(p1, NULL) != 0)
        return (3);
    if (pthread_join(p2, NULL) != 0)
        return (4);
    printf ("Number of mails: %d\n", c);
    return (0);
}