#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int		main(int ac, char **av)
{
	int	id1 = fork();
	int id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
		{
			puts("We are in process y\n");
		}
		else
			puts("We are in procdss x\n");
	}
	else
	{
		if (id2 == 0)
			puts("We are in process z\n");
		else
			puts("We are in parent\n");
	}
	while(wait(NULL) != -1 || errno != ECHILD)
	{
		puts("Waited for  a child to finish\n");
	}
	return (0);
}