#include "shell.h"

/**
 * get_input - Gets input from the commandline
 * @lineptr: The pointer to the command string
 * @len: Size of string
 *
 * Return: Void
 */

char *get_input(char *lineptr, size_t len)
{
	ssize_t char_read;

	lineptr = NULL;
	len = 0;
	char_read = getline(&lineptr, &len, stdin);
	if (char_read == -1)
	{
		if (feof(stdin))
		{
			free(lineptr);
		/*	write(STDOUT_FILENO, "\n", 1);	*/
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Getline Error");
			free(lineptr);
			exit(EXIT_FAILURE);
		}
	}

	/*if (char_read > 0 && lineptr[char_read - 1] == '\n')*/
	/*{*/
	/*	lineptr[char_read - 1] = '\0';*/
	/*}*/

	return (lineptr);
}
