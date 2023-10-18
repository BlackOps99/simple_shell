#ifndef __SHELL__H
#define __SHELL__H


/* Include LIB */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdarg.h>

#define MAXARGS 10

/* GLOBAL VARIABLES */
extern int lineCount;
extern char *shellName;
extern char **my_env;

/**
 * struct cmd - cmd start point
 * @type: int type of the command
 *
 * Description: All commands have at least a type. Have looked at the type,
 * the code typically casts the *cmd to some specific cmd type.
 */
struct cmd
{
	int type;
};

/**
 * struct execcmd - execcmd save args
 * @type: int type of the command
 * @argv: array of char pointer that have the args
 * Description: have the command and arg that will be exec.
 */
struct execcmd
{
	int type;
	char *argv[MAXARGS];
};

/**
 * struct redircmd - redir
 * @type: int type of the command
 * @cmd: struct for cmd
 * @file: the name of the file
 * @flags: flags of the commend
 * @fd: can open or not
 * Description: handle redir command to file
 */
struct redircmd
{
	int type;
	struct cmd *cmd;
	char *file;
	int flags;
	int fd;
};

/**
 * struct pipecmd - pipecmd handle the pip commends
 * @type: int type of the command
 * @left: left pip command
 * @right: right pip command
 * Description: handle all pipe commends
 */
struct pipecmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
};

/* Printing functions */
int writeLog(int status, const char *format, ...);
int _putchar(int status, char c);
int isCharInArray(char searchValue);
int handle_log(const char *to_type, int status, va_list value);
void writeEnv(void);

/* Conversion handlers */
int toChar(int status, va_list value);
int toString(int status, va_list value);
int toInt(int status, va_list value);

/* PARSE PROTOTYPES */
struct cmd *parsecmd(char *);
struct cmd *parseline(char **, char *);
struct cmd *parsepipe(char **, char *);
struct cmd *parseexec(char **, char *);
struct cmd *parseredirs(struct cmd *cmd, char **ps, char *es);

/* HELPER FUNCS */
void setPanic(char *s);
void upSignal(int sig);
int forker(void);
int peek(char **ps, char *es, char *toks);
int status(int r);

/* I Get command */
int getcmd(char *buf, size_t nbuf);

/* I Run command*/
int runcmd(struct cmd *cmd);
int runExec(struct cmd *cmd);
int runPipe(struct cmd *cmd);
void runRedir(struct cmd *cmd);

/* create_structs */
struct cmd *execcmd(void);
struct cmd *redircmd(struct cmd *subcmd, char *file, int type);
struct cmd *pipecmd(struct cmd *left, struct cmd *right);

char *get_env_value(char **envp, const char *name);

/* Memory furnctions handle */
void *_memset(void *__s, int __c, size_t __n);

/* String furnctions handle */
int _strlen(char *s);
char *_strchr(const char *str, int c);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
char *mkcopy(char *s, char *es);

/* Cmd furnctions handle */
int gettoken(char **ps, char *es, char **q, char **eq);


/* Free Structs */
void free_cmd(struct cmd *cmd);
void free_execcmd(struct execcmd *cmd);
void free_pipecmd(struct pipecmd *cmd);
void free_redircmd(struct redircmd *cmd);


#endif
