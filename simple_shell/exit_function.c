#include "shell.h"

void exit_function(char *args[])
{
	int status = args[1] ? atoi(args[1]) : 0;

	free_resources(args, NULL);
	exit(status);
}
