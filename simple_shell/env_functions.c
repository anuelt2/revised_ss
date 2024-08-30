#include "shell.h"

/**
* get_env - print env variables
* Return: void
*/
/*void get_env(void)
{
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
		{
			write(STDOUT_FILENO, &environ[i][j], 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}*/

/**
* set_env - Initialise new env var or modify an existing one
* @var: variable name to create or modify
* @val: value to give to pass to var
* @overwrite: instruction to overwrite existing variable
* Return: int
*/
/*int set_env(char *var, char *val, int overwrite)
{
	char **environ_copy = copy_environ(), **temp;
	int i, var_len;
	char *new_var = _concat(var, val);
	int environ_copy_size = get_env_size(environ_copy);

	if (!var && _strcon(var, '=') != 0)
		return (-1);

	var_len = _strlen(var);
	for (i = 0; environ_copy[i] != NULL; i++)
	{
		if (_strncmp(environ_copy[i], var, var_len) == 0 &&
			environ_copy[i][var_len] == '=')
		{
			if (overwrite == 0)
			{
				return (0);
			}
			printf("%d\n", i);
			break;
		}
	}

	if (environ_copy[i] != NULL)
	{
		environ_copy[i] = new_var;
	}
	else
	{
		temp = realloc(environ_copy, sizeof(char *) * (environ_copy_size + 2));
		if (!temp)
			return (-1);
		environ_copy = temp;
		environ_copy[environ_copy_size] = new_var;
		environ_copy[environ_copy_size + 1] = NULL;
		environ_copy_size++;
	}
	environ = environ_copy;

	return (0);
}*/

/**
* unset_env - unset an environment variable
* @var: variable to delete
* Return: 0 (success), -1 (failure)
*/
int unset_env(char *var)
{
	char **environ_copy = copy_environ();
	char *temp;
	int i, var_len, environ_copy_size = get_env_size(environ_copy);

	if (!var && _strcon(var, '=') != 0)
		return (-1);
	var_len = _strlen(var);
	for (i = 0; environ_copy[i] != NULL; i++)
	{
		if (_strncmp(environ_copy[i], var, var_len) == 0 &&
			environ_copy[i][var_len] == '=')
		{
			break;
		}
	}

	while (i <= environ_copy_size)
	{
		temp = environ_copy[i + 1];
		environ_copy[i] = temp;
		environ_copy_size--;
		i++;
	}
	environ = environ_copy;

	return (0);
}
