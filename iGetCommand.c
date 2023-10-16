#include "shell.h"

/**
 * getcmd - Read a command from the user or a file into a buffer.
 * @buf: Pointer to the buffer where the command will be stored.
 * @nbuf: The size of the buffer.
 * This function reads a command from the user if the input is a terminal and
 * displays a prompt ('$ '). It initializes the buffer to zero, increments the
 * line count, and then reads a line of input into the buffer from stdin. It
 * Return: 0 if successful, or -1 if an error occurs.
 */
int getcmd(char *buf, size_t nbuf)
{
	if (isatty(fileno(stdin)))
		writeLog(STDOUT_FILENO, "$ ");
	lineCount++;
	if (fgets(buf, nbuf, stdin) == 0)
		return (-1);
	return (0);
}
