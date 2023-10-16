#include "shell.h"

/**
 * gettoken - Tokenizes input string based on whitespace and special symbols.
 * @ps: A pointer to the current position in the input string.
 * @es: A pointer to the end of the input string.
 * @q: Pointer to the start of the token.
 * @eq: Pointer to the end of the token.
 * Return: the type of token encountered.
 */
int gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;
	char whitespace[] = " \t\r\n\v";
	char symbols[] = "<|>";

	s = *ps;

	while (s < es && _strchr(whitespace, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	switch (*s)
	{
	case 0:
		break;
	case '|':
	case '<':
		s++;
		break;
	case '>':
		s++;
		break;
	default:
		ret = 'a';
		while (s < es && !_strchr(whitespace, *s) && !_strchr(symbols, *s))
			s++;
		break;
	}
	if (eq)
		*eq = s;

	while (s < es && _strchr(whitespace, *s))
	{
		*s = ' ';
		s++;
	}

	*ps = s;
	return (ret);
}

/**
 * peek - Checks if the current character is a part of specified tokens.
 * @ps: A pointer to the current position in the input string.
 * @es: A pointer to the end of the input string.
 * @toks: A string containing the tokens to check.
 * Return: 1 if it is, 0 otherwise.
 */
int peek(char **ps, char *es, char *toks)
{
	char whitespace[] = " \t\r\n\v";
	char *s;

	s = *ps;
	while (s < es && _strchr(whitespace, *s))
		s++;
	*ps = s;
	return (*s && _strchr(toks, *s));
}

/**
 * forker - Creates a child process using fork().
 * This function creates a child process using the fork() system call.
 * Return: the child process ID (PID) or -1 if the fork failed.
 */
int forker(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
		perror("fork");

	return (pid);
}

/**
 * upSignal - Custom signal handler for SIGINT (Ctrl+C).
 * @sig: The signal number.
 * This function is a custom signal handler for SIGINT (Ctrl+C) that simply
 * prints a new line and a prompt after catching the signal
 * Return: NoThing
 */
void upSignal(int sig)
{
	(void)sig;
	signal(SIGINT, upSignal);
	writeLog(STDIN_FILENO, "\n$ ");
}

/**
 * writeEnv - Print the environment variables to the standard output.
 * This function iterates through the `my_env` array, which holds environment
 * variables, and prints each variable to the standard output. It is used to
 * display environment information.
 * Return: NoThing
 */
void writeEnv(void)
{
	unsigned int i;

	i = 0;
	while (my_env[i] != NULL)
	{
		writeLog(STDOUT_FILENO, "%s\n", my_env[i]);
		i++;
	}
}
