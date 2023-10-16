#include "shell.h"

/**
 * free_cmd - Function to free memory allocated for a 'cmd' structure.
 * @cmd: Pointer to the 'cmd' structure to be freed.
 * This function frees the memory associated with a 'cmd' structure.
 * Return: NoThing
 */
void free_cmd(struct cmd *cmd)
{
	free(cmd);
}

/**
 * free_execcmd - Function to free memory allocated for an 'execcmd' structure.
 * @cmd: Pointer to the 'execcmd' structure to be freed.
 * This function frees the memory associated with an 'execcmd' structure,
 * including the memory allocated for its argument vector.
 * Return: NoThing
 */
void free_execcmd(struct execcmd *cmd)
{
	int i;

	for (i = 0; cmd->argv[i] != 0; i++)
	{
		free(cmd->argv[i]);
	}
}

/**
 * free_pipecmd - Function to free memory allocated for a 'pipecmd' structure.
 * @cmd: Pointer to the 'pipecmd' structure to be freed.
 * This function frees the memory associated with a 'pipecmd' structure,
 * including the memory allocated for its left and right command structures.
 * Return: NoThing
 */
void free_pipecmd(struct pipecmd *cmd)
{
	free(cmd->left);
	free(cmd->right);
}

/**
 * free_redircmd - Function to free memory allocated for a 'redircmd' structure
 * @cmd: Pointer to the 'redircmd' structure to be freed.
 * This function frees the memory associated with a 'redircmd' structure,
 * including the memory allocated for its 'cmd' and 'file' members.
 * Return: NoThing
 */
void free_redircmd(struct redircmd *cmd)
{
	free(cmd->cmd);
	free(cmd->file);
}
