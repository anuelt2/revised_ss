#include "shell.h"

/**
* env_size - get environ size
* Return: length of environ
*/
int env_size(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	;

	return (i);
}

/**
* get_env_size - get environ size
* @env: environment variable size to measure
* Return: length of env list size
*/
int get_env_size(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	;

	return (i);
}

/**
* copy_environ - create a copy of environ
* Return: pointer to copy of environ
*/
char **copy_environ(void)
{
	char **environ_copy;
	int i, j, env_var_len, environ_size = env_size();

	environ_copy = malloc(sizeof(char *) * (environ_size + 1));
	if (!environ_copy)
		exit(EXIT_FAILURE);
	environ_copy[environ_size] = NULL;
	for (i = 0; environ[i] != NULL; i++)
	{
		env_var_len = _strlen(environ[i]);
		environ_copy[i] = malloc(sizeof(char) * (env_var_len + 1));
		if (!environ_copy[i])
			exit(EXIT_FAILURE);
		for (j = 0; environ[i][j] != '\0'; j++)
			environ_copy[i][j] = environ[i][j];
		environ_copy[i][env_var_len] = '\0';
	}
	return (environ_copy);
}

/**
* env_func_caller - set which env to call
* @args: arrays of args
* Return: 0 - success, 1 - failure
*/
int env_func_caller(char **args)
{
	if (_strcmp(args[0], "env") == 0)
	{
		get_env();
		return (0);
	}
	else if (_strcmp(args[0], "setenv") == 0)
	{
		set_env(args[1], args[2], 1);
		return (0);
	}
	else if (_strcmp(args[0], "unsetenv") == 0)
	{
		unset_env(args[1]);
		return (0);
	}
	return (1);
}
