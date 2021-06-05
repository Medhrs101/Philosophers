// #include "../../philosopher.h"
#include <stdio.h>
#include <unistd.h>
int main(void)
{
	int id = fork();
	id = fork();
	// id = fork();
	// id = fork();
	printf("Hello World from id = %d\n", id);
	return (0);
}