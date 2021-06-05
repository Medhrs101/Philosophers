#include "../../philosopher.h"
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int id = fork();
	if (id == 0)
		sleep(1);
	printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
	
	return(0);
}