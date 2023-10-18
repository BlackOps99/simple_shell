#include "shell.h"

/**
 * runcmd - Execute a command structure.
 * @cmd: A pointer to the command structure to execute.
 * This function determines the type of command and dispatches it to the
 * appropriate handler. If the command is of type ' ', it executes an
 * executable command. If it's of type '>' or '<', it handles redirections.
 * If it's of type '|', it handles pipeline execution. If the command is not
 * recognized, it exits with an error message.
 * Return: the status
 */
int runcmd(struct cmd *cmd)
{
	if (cmd == 0)
	{
		free_cmd(cmd);
		_exit(0);
	}

	switch (cmd->type)
	{
	default:
		writeLog(STDERR_FILENO, "unknown runcmd\n");
		_exit(-1);

	case ' ':
		return (runExec(cmd));

	case '>':
	case '<':
		runRedir(cmd);
		return (0);

	case '|':

		return (runPipe(cmd));
	}
	free(cmd);
	_exit(0);
}

/**
 * find_in_path - Search for an executable in PATH directories.
 * @command: The executable file to search for.
 * Searches for the given executable in the directories listed in the PATH
 * environment variable. Returns a dynamically allocated full path if found
 * and executable; otherwise, returns NULL.
 * Return: dynamically allocated string with full path or NULL if not found
 */
char *find_in_path(const char *command)
{
	char full_path[1024];
	char *path_copy;
	char *path = get_env_value(my_env, "PATH");
	char *token;

	if (path == NULL)
	{
		return (NULL);
	}

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}

		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * runExec - Execute an executable command.
 * @cmd: A pointer to the executable command structure.
 * This function attempts to execute an executable command by invoking execvp.
 * If the command execution fails, it writes an error message and returns the
 * exit status. It also frees the associated memory before returning.
 * Return: the status
 */
int runExec(struct cmd *cmd)
{
	int r = 0;
	char *path = NULL;
	struct execcmd *ecmd;

	ecmd = (struct execcmd *)cmd;
	if (ecmd->argv[0] == 0)
	{
		free_execcmd(ecmd);
		free_cmd(cmd);
		_exit(0);
	}
	if (ecmd->argv[0][0] != '/')
	{
		path = find_in_path(ecmd->argv[0]);
	}

	if (path == NULL)
	{
		path = ecmd->argv[0];
	}

	if (execve(path, ecmd->argv, my_env) == -1)
	{
		r = 127;
	}

	writeLog(STDERR_FILENO, "%s: %d: %s: not found\n",
		shellName, lineCount, ecmd->argv[0]);

	free_execcmd(ecmd);
	free_cmd(cmd);
	return (r);
}

/**
 * runPipe - Execute a pipeline of commands.
 * @cmd: A pointer to the pipeline command structure.
 *
 * This function sets up and executes a pipeline of commands. It creates a pipe
 * forks two child processes, and connects them via the pipe. It then waits for
 * the child processes to complete and frees the associated memory.
 * Return: the status
 */
int runPipe(struct cmd *cmd)
{
	int pipefd[2];
	struct pipecmd *pcmd;

	pcmd = (struct pipecmd *)cmd;
	if (pipe(pipefd) < 0)
		setPanic("pipe");

	if (forker() == 0)
	{
		close(pipefd[0]);
		close(1);
		dup(pipefd[1]);
		close(pipefd[1]);
		_exit(0);
	}
	else
	{
		close(pipefd[1]);
	}
	if (forker() == 0)
	{
		close(pipefd[1]);
		close(0);
		dup(pipefd[0]);
		close(pipefd[0]);
		runcmd(pcmd->right);
		_exit(0);
	}
	close(pipefd[0]);
	wait(0);
	wait(0);
	free_pipecmd(pcmd);
	return (0);
}

/**
 * runRedir - Handle redirections (not implemented).
 * @cmd: A pointer to the redirection command structure.
 *
 * This function is a placeholder for handling redirections, but it is not
 * currently implemented. It writes an error message and invokes runcmd on
 * the subcommand. The associated memory is freed after execution.
 * Return: NoThing
 */
void runRedir(struct cmd *cmd)
{
	struct redircmd *rcmd;

	rcmd = (struct redircmd *)cmd;
	writeLog(STDERR_FILENO, "redir not implemented\n");
	runcmd(rcmd->cmd);
	free_redircmd(rcmd);
}
