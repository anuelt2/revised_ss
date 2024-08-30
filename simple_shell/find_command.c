#include "shell.h"

char *find_command(char *pathname, char **envp)
{
	char *path_env = get_env_path(envp, _path_size(envp)), *dir, *full_path = NULL;

	if (!path_env)
		return (NULL);

	for (dir = strtok(path_env, ":"); dir; dir = strtok(NULL, ":"))
	{
		full_path = _concatenate(dir, pathname);
		if (is_executable(full_path))
			break;
		free(full_path);
		full_path = NULL;
	}
	free(path_env);
	return (full_path);
}
