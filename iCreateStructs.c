#include "shell.h"

/**
 * execcmd - Create an 'execcmd' structure.
 * This function allocates memory for an 'execcmd' structure, initializes its
 * members, and sets the type to a space character. It returns a pointer to
 * the created 'cmd' structure.
 * Return: the struct after created.
 */
struct cmd *execcmd(void)
{
	struct execcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	_memset(cmd, 0, sizeof(*cmd));
	cmd->type = ' ';
	return ((struct cmd *)cmd);
}

/**
 * redircmd - Create a 'redircmd' structure.
 * @subcmd: Pointer to the command to be redirected.
 * @file: The file to redirect to.
 * @type: The type of redirection (e.g., '<' for input, '>' for output).
 *
 * This function allocates memory for a 'redircmd' structure, initializes its
 * members, and returns a pointer to the created 'cmd' structure. It specifies
 * the redirection type, the command to be redirected, and the file to use.
 * Return: the struct after created.
 */
struct cmd *redircmd(struct cmd *subcmd, char *file, int type)
{
	struct redircmd *cmd;

	cmd = malloc(sizeof(*cmd));
	_memset(cmd, 0, sizeof(*cmd));
	cmd->type = type;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->flags = (type == '<') ? O_RDONLY : O_WRONLY | O_CREAT | O_TRUNC;
	cmd->fd = (type == '<') ? 0 : 1;
	return ((struct cmd *)cmd);
}

/**
 * pipecmd - Create a 'pipecmd' structure.
 * @left: Pointer to the command on the left side of the pipe.
 * @right: Pointer to the command on the right side of the pipe.
 *
 * This function allocates memory for a 'pipecmd' structure, initializes its
 * members, and sets the type to a pipe character '|'. It connects two commands
 * via a pipe. It returns a pointer to the created 'cmd' structure.
 * Return: the struct after created.
 */
struct cmd *pipecmd(struct cmd *left, struct cmd *right)
{
	struct pipecmd *cmd;

	cmd = malloc(sizeof(*cmd));
	_memset(cmd, 0, sizeof(*cmd));
	cmd->type = '|';
	cmd->left = left;
	cmd->right = right;
	return ((struct cmd *)cmd);
}
