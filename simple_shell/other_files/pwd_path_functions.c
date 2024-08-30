#include "shell.h"

/**
* pwd_path_size - Get pwd path size
* @envp: Environment variable
*
* Return: Size of path
*/

int pwd_path_size(char **envp)
{
	int i = 0, j = 3;

	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W' &&
				envp[i][2] == 'D')
		{
			while (envp[i][j++] != '\0')
				;
		}
		i++;
	}

	return (j);
}

/**
* get_pwd_path - Get the pwd path
* @envp: Environment variable
* @size: Size of environment path variable
*
* Return: Pointer to path variable
*/

char *get_pwd_path(char **envp, int size)
{
	char *path;
	int i = 0, j = 3, k = 0;

	size = pwd_path_size(envp);
	path = malloc(sizeof(char) * (size + 1));
	path[size] = '\0';
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W'
				&& envp[i][2] == 'D')
		{
			while (envp[i][j++] != '\0')
				path[k++] = envp[i][j];
		}
		i++;
	}

	return (path);
}

/**
* oldpwd_path_size - Get home path size
* @envp: Environment variable
*
* Return: Size of path
*/

int oldpwd_path_size(char **envp)
{
	int i = 0, j = 6;

	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'O' && envp[i][1] == 'L' &&
				envp[i][2] == 'D' && envp[i][3] == 'P' &&
				envp[i][4] == 'W' && envp[i][5] == 'D')
		{
			while (envp[i][j++] != '\0')
				;
		}
		i++;
	}

	return (j);
}

/**
* get_oldpwd_path - Get the home path
* @envp: Environment variable
* @size: Size of environment path variable
*
* Return: Pointer to path variable
*/

char *get_oldpwd_path(char **envp, int size)
{
	char *path;
	int i = 0, j = 6, k = 0;

	size = oldpwd_path_size(envp);
	path = malloc(sizeof(char) * (size + 1));
	path[size] = '\0';
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'O' && envp[i][1] == 'L'
				&& envp[i][2] == 'D' && envp[i][3] == 'P' &&
				envp[i][4] == 'W' && envp[i][5] == 'D')
		{
			while (envp[i][j++] != '\0')
				path[k++] = envp[i][j];
		}
		i++;
	}

	return (path);
}
