#include "shell.h"

/**
 * setPanic - Display an error message and exit the program with an error code.
 * @s: The error message to display.
 * This function writes the provided error message to the standard error stream
 * (STDERR_FILENO) using the `writeLog` function It then exits the program with
 * an error code of -1, indicating a failure or panic situation.
 * Return: NoThing
 */
void setPanic(char *s)
{
	writeLog(STDERR_FILENO, "%s\n", s);
	exit(-1);
}
