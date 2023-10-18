#include "shell.h"

int lineCount;
char *shellName;
char **my_env;

/**
 * main - check the code
 * @argc: number of arguments
 * @argv: pointer to pointers to strings
 * @env: enviromental variables
 * Return: statues
 */
int main(int argc, char *argv[], char **env)
{
	static char buf[1024];
	int r, res = 0, pid = 0;

	(void)argc;
	my_env = env;
	signal(SIGINT, upSignal);

	lineCount = 0;
	shellName = argv[0];
	while (getcmd(buf, sizeof(buf)) >= 0)
	{
		if (_strcmp(buf, "env\n") == 0)
		{
			writeEnv();
			continue;
		}

		if (_strcmp(buf, "exit\n") == 0)
			break;
		if (strncmp(buf, "cd", 2) == 0) {
            builtin_cd(buf);
            continue;
        }
		/*	
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			buf[_strlen(buf) - 1] = 0;
			if (chdir(buf + 3) < 0)
				writeLog(STDERR_FILENO, "%s: %d: cd: can't cd to %s\n",
				shellName, lineCount, buf + 3);
			continue;
		}
		*/
		pid = forker();
		if (pid == 0)
			res = runcmd(parsecmd(buf));
		else
		{
			waitpid(pid, &r, 0);
			if (WIFEXITED(r))
				res = WEXITSTATUS(r);
			else if (WIFSIGNALED(r))
				res = WTERMSIG(r);
		}
	}
	return (res);
}
