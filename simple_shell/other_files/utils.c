#include "shell.h"

/**
* _path_size - Get envp path size
* @envp: Environment variable
*
* Return: Size of path
*/
int _path_size(char **envp)
{
	int i = 0, j = 5;

	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
			envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			while (envp[i][j++] != '\0')
			;
		}
		i++;
	}

	return (j);
}

/**
* get_env_path - Get the env path
* @envp: Environment variable
* @size: Size of environment path variable
*
* Return: Pointer to path variable
*/

/*char *get_env_path(char **envp, int size)
{
	char *path;
	int i = 0, j = 5, k = 0;

	path = malloc(sizeof(char) * (size + 1));
	path[size] = '\0';
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			while (envp[i][j++] != '\0')
				path[k++] = envp[i][j];
		}
		i++;
	}

	return (path);
}*/

/**
* _concatenate - Concatenate strings
* @dir: Executable directory
* @pathname: Command name
*
* Return: Full path to command path
*/

char *_concatenate(char *dir, char *pathname)
{
	char *full_path;
	int i, j, k;

	full_path = malloc(sizeof(char) * 4096);
	full_path[4095] = '\0';
	if (!full_path)
	{
		perror("Fullpath error");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 4096 && dir[i] != '\0'; i++)
	{
		full_path[i] = dir[i];
	}
	full_path[i] = '/';
	for (j = i + 1, k = 0; j < 4096 && pathname[k] != 0; j++, k++)
	{
		full_path[j] = pathname[k];
	}

	return (full_path);
}

/**
* is_executable - Check if file is executable
* @full_path: Path to check
*
* Return: 1 (success) or 0 (otherwise)
*/

int is_executable(char *full_path)
{
	struct stat sb;

	/* sb.st_mode - holds the exec and search permissions */
	/* S_IXUSR - Macro to  */
	return (stat(full_path, &sb) == 0 && sb.st_mode & S_IXUSR);
}

/**
* find_ext_file - Find external command file
* @pathname: The command to search for
* @envp: Environment variable
* @cmd_count: Count of commands entered in each shell session
*
* Return: Path to command
*/
char *find_ext_file(char *pathname, char **envp, int cmd_count)
{
	char *env_path, *dir, *full_path;
	int path_size;

	full_path = malloc(sizeof(char) * 4096);
	full_path[4095] = '\0';
	shell_path_exec(pathname, full_path);
	path_size = _path_size(envp);
	env_path = malloc(sizeof(char) * (path_size + 1));
	env_path[path_size] = '\0';
	env_path = get_env_path(envp, path_size);
	if (!env_path)
	{
		perror("Envpath error");
		exit(EXIT_FAILURE);
	}
	dir = strtok(env_path, ":");
	while (dir != NULL)
	{
		if (pathname[0] == '/')
			full_path = pathname;
		else
			full_path = _concatenate(dir, pathname);
		if (access(full_path, F_OK) == 0)
		{
			free(env_path);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(env_path);
	if (pathname[0] != '/' && pathname[0] != '.')
	{
		free(full_path);
		fprintf(stderr, "simple_shell: %d: %s: not found\n", cmd_count, pathname);
		return ('\0');
	}
	return (full_path);
}
