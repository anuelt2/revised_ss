#include "shell.h"

/**
 * shell_path_exec - Executes path outside of environment
 * @pathname: Path
 * @full_path: Full path to executable
 *
 * Return: Pointer to path
 */

char *shell_path_exec(char *pathname, char *full_path)
{
	if (strchr(pathname, '/') != NULL)
	{
		if (is_executable(pathname))
		{
			full_path = pathname;
			return (full_path);
		}
	}
	free(full_path);
	return ('\0');
}
