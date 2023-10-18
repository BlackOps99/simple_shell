#include "shell.h"

/**
 * get_env_value - Get the value of an environment variable.
 * @envp: A pointer to an array of environment variable strings.
 * @name: The name of the environment variable to retrieve.
 * This function retrieves the value of a specified environment variable from
 * the provided array of environment variable strings
 * it returns a pointer to the value; otherwise, it returns NULL.
 * Return: pointer to the value of the env variable, or NULL if not found.
 */
char *get_env_value(char **envp, const char *name)
{
	int i;

	if (envp == NULL || name == NULL)
	{
		return (NULL);
	}

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], name, strlen(name)) == 0)
		{
			return (envp[i] + strlen(name) + 1);
		}
	}

	return (NULL);
}
