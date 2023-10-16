#include "shell.h"

/**
 * parsecmd - Parse the entire command and return a command structure.
 * @s: The input string to parse.
 * This function parses the entire command by calling the other parsing
 * functions and returns a command structure representing the parsed command.
 * Return: cmd struct
 */
struct cmd *parsecmd(char *s)
{
	char *es;
	struct cmd *cmd;

	es = s + _strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if (s != es)
	{
		writeLog(STDERR_FILENO, "leftovers: %s\n", s);
		exit(-1);
	}

	return (cmd);
}

/**
 * parseline - Parse a command line and return a command structure.
 * @ps: Pointer to the current position in the input string.
 * @es: A pointer to the end of the input string.
 * This function parses a command line and returns a command structure
 * representing the parsed command line.
 * Return: cmd struct
 */
struct cmd *parseline(char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parsepipe(ps, es);

	return (cmd);
}

/**
 * parsepipe - Parse a pipeline and return a command structure.
 * @ps: Pointer to the current position in the input string.
 * @es: A pointer to the end of the input string.
 * This function parses a pipeline (commands separated by '|') and returns
 * a command structure representing the parsed pipeline.
 * Return: cmd struct
 */
struct cmd *parsepipe(char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}

	return (cmd);
}

/**
 * parseredirs - Parse redirections for a command and return command structure
 * @cmd: Pointer to the current command structure.
 * @ps: Pointer to the current position in the input string.
 * @es: A pointer to the end of the input string.
 *
 * function parses redirections (e.g., '<' and '>') for a command and returns
 * a modified command structure with redirections applied.
 * Return: cmd struct
 */
struct cmd *parseredirs(struct cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
		{
			writeLog(STDERR_FILENO, "missing file for redirection\n");
			exit(-1);
		}
		switch (tok)
		{
		case '<':
			cmd = redircmd(cmd, mkcopy(q, eq), '<');
			break;
		case '>':
			cmd = redircmd(cmd, mkcopy(q, eq), '>');
			break;
		}
	}

	return (cmd);
}

/**
 * parseexec - Parse an executable command and return a command structure.
 * @ps: Pointer to the current position in the input string.
 * @es: A pointer to the end of the input string.
 * This function parses an executable command and returns a command structure
 * representing the parsed command with its arguments and redirections.
 * Return: cmd struct
 */
struct cmd *parseexec(char **ps, char *es)
{
	char *q, *eq;
	int tok, argc;
	struct execcmd *cmd;
	struct cmd *ret;

	ret = execcmd();
	cmd = (struct execcmd *)ret;

	argc = 0;
	ret = parseredirs(ret, ps, es);
	while (!peek(ps, es, "|"))
	{
		tok = gettoken(ps, es, &q, &eq);

		if (tok == 0)
			break;

		if (tok != 'a')
		{
			writeLog(STDERR_FILENO, "syntax error\n");
			exit(-1);
		}
		cmd->argv[argc] = mkcopy(q, eq);
		argc++;
		if (argc >= MAXARGS)
		{
			writeLog(STDERR_FILENO, "too many args\n");
			exit(-1);
		}
		ret = parseredirs(ret, ps, es);
	}

	cmd->argv[argc] = 0;
	return (ret);
}
