#ifndef _SIMPLE_SHELL_
#define _SIMPLE_SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* ERRORS & OTHERS*/
#define TRUE 1
#define FALSE 0
#define BUFSIZE 256
#define ENOSTRING 1106
#define EILLEGAL 227
#define EWSIZE 410
#define ENOBUILTIN 415
#define EBADCD 726

extern char **environ;

/**
 * struct linkedList - linked list data structure
 * @string: environ variable path name
 * @next: pointer to next node
 */
typedef struct linkedList
{
	char *string;
	struct linkedList *next;
} link_l;

/**
 * struct configurations - configuration of cart settings
 * @env: linked list of local env variables
 * @envArr: array of env variables to put into execve
 * @args: array of argument strings
 * @buffer: string buffer of user input
 * @path: array of $PATH locations
 * @fullPath: string of path with correct prepended $PATH
 * @shellName: name of shell (argv[0])
 * @lineCounter: counter of lines users have entered
 * @errorStatus: error status of last child process
 */
typedef struct set_up
{
	link_l *env;
	char **envArr;
	char **args;
	char *buffer;
	char *path;
	char *fullPath;
	char *shellName;
	unsigned int lineCounter;
	int errorStatus;
} config;

/**
 * struct builtInCommands - commands and functions associated with them
 * @command: input command
 * @func: output function
 */
typedef struct builtInCommands
{
	char *command;
	int (*func)(config *cart);
} type_b;

/* main */
config *configInit(config *cart);

/* shell_live */
void shell(config *cart);
void lineCollector(config *cart);
void fork_exec_wait(config *cart);
void commentStripper(char *str);
void convertLLtoArr(config *cart);

/* shell_complement_A */
void insertNull(char *str, unsigned int index);
void displayPrompt(void);
void displayNewLine(void);
void sigintHandler(int sigint);

/* string_complements_A */
int splitString(config *cart);
unsigned int countWords(char *s);
int isSpace(char c);

/* string_complements_B */
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);

/* string_complements_C */
char *_strtok(char *str, char *delim);
int _strcspn(char *string, char *chars);
char *_strchr(char *s, char c);

/* string_complements_D */
int countArgs(char **args);
int _atoi(char *s);

/* linked_list_complement_A*/
link_l *nodeAdd(link_l **head, char *str);
link_l *nodeAppend(link_l **head, char *str);
size_t printList(const link_l *h);
int searchNode(link_l *head, char *str);
size_t list_len(link_l *h);

/* linked_list_complement_B */
int deleteNodeAtIndex(link_l **head, unsigned int index);
link_l *generateLinkedList(char **array);
link_l *addNodeAtIndex(link_l **head, int index, char *str);
char *getNodeAtIndex(link_l *head, unsigned int index);

/* built_ins */
int findBuiltIns(config *cart);
int exitFunc(config *cart);
int historyFunc(config *cart);
int aliasFunc(config *cart);

/* cd */
int cdFunc(config *);
int cdToHome(config *cart);
int cdToPrevious(config *cart);
int cdToCustom(config *cart);
int updateEnviron(config *cart);

/* cd_complement_A */
int updateOld(config *cart);
int updateCur(config *cart, int index);

/* environ_variable_mngmnt */
char *_getenv(char *input, char **array);
int envFunc(config *cart);
int setenvFunc(config *cart);
int unsetenvFunc(config *cart);
int _isalpha(int c);

/* help_0 */
int helpFunc(config *cart);
int displayHelpMenu(void);
int helpExit(config *cart);
int helpEnv(config *cart);
int helpHistory(config *cart);

/* help_1 */
int helpAlias(config *cart);
int helpCd(config *biuld);
int helpSetenv(config *cart);
int helpUnsetenv(config *cart);
int helpHelp(config *cart);

/* error_mngmnt */
void errorHandler(config *cart);
unsigned int countDigits(int num);
char *itoa(unsigned int num);
char *getErrorMessage();

/* check_path */
int checkPath(config *);
int checkEdgeCases(config *cart);

/* welcome */
void welcome_screen_1(void);
void welcome_screen_2(void);

/* mem_mngmnt_realloc */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);

/* mem_mngmnt_free */
void freeMembers(config *cart);
void freeArgsAndBuffer(config *cart);
void freeArgs(char **args);
void freeList(link_l *head);

#endif
