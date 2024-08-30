#include "shell.h"

/**
* home_path_size - Get home path size
* @envp: The environment variable
*
* Return: Size of path
*/

int home_path_size(char **envp)
{
	int i = 0, j = 4;

	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'H' && envp[i][1] == 'O' &&
			envp[i][2] == 'M' && envp[i][3] == 'E')
		{
			while (envp[i][j++] != '\0')
			;
		}
		i++;
	}

	return (j);
}

/**
* get_home_path - Get the home path
* @envp: Environment variable
* @size: Size of environment path variable
*
* Return: Pointer to path variable
*/

char *get_home_path(char **envp, int size)
{
	char *path;
	int i = 0, j = 4, k = 0;

	size = home_path_size(envp);
	path = malloc(sizeof(char) * (size + 1));
	path[size] = '\0';
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'H' && envp[i][1] == 'O'
			&& envp[i][2] == 'M' && envp[i][3] == 'E')
		{
			while (envp[i][j++] != '\0')
				path[k++] = envp[i][j];
		}
		i++;
	}

	return (path);
}
