#include "main.h"

/**
 * shell - simple shell
 * @cart: input cart
 */
void shell(config *cart)
{

	while (TRUE)
	{
		lineCollector(cart);
		if (splitString(cart) == FALSE)
			continue;
		if (findBuiltIns(cart) == TRUE)
			continue;
		checkPath(cart);
		fork_exec_wait(cart);
	}
}

/**
 * lineCollector - check stdin and retrieves next line; handles
 * prompt display
 * @cart: input cart
 */
void lineCollector(config *cart)
{
	register int len;
	size_t bufferSize = 0;
	char *ptr, *ptr2;

	cart->args = NULL;
	cart->envArr = NULL;
	cart->lineCounter++;
	if (isatty(STDIN_FILENO))
		displayPrompt();
	len = getline(&cart->buffer, &bufferSize, stdin);
	if (len == EOF)
	{
		freeMembers(cart);
		if (isatty(STDIN_FILENO))
			displayNewLine();
		if (cart->errorStatus)
			exit(cart->errorStatus);
		exit(EXIT_SUCCESS);
	}
	ptr = _strchr(cart->buffer, '\n');
	ptr2 = _strchr(cart->buffer, '\t');
	if (ptr || ptr2)
		insertNull(cart->buffer, len - 1);
	commentStripper(cart->buffer);
}

/**
 * commentStripper - remove comments from input string
 * @str: input string
 * Return: length of remaining string
 */
void commentStripper(char *str)
{
	register int i = 0;
	int notFirst = FALSE;

	while (str[i])
	{
		if (i == 0 && str[i] == '#')
		{
			insertNull(str, i);
			return;
		}
		if (notFirst)
		{
			if (str[i] == '#' && str[i - 1] == ' ')
			{
				insertNull(str, i);
				return;
			}
		}
		i++;
		notFirst = TRUE;
	}
}

/**
 * fork_exec_wait - fork current cart and execute processes
 * @cart: input cart
 */
void fork_exec_wait(config *cart)
{
	int status;
	pid_t f1 = fork();

	convertLLtoArr(cart);
	if (f1 == -1)
	{
		perror("error\n");
		freeMembers(cart);
		freeArgs(cart->envArr);
		exit(1);
	}
	if (f1 == 0)
	{
		if (execve(cart->fullPath, cart->args, cart->envArr) == -1)
		{
			errorHandler(cart);
			freeMembers(cart);
			freeArgs(cart->envArr);
			if (errno == ENOENT)
				exit(127);
			if (errno == EACCES)
				exit(126);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			cart->errorStatus = WEXITSTATUS(status);
		freeArgsAndBuffer(cart);
		freeArgs(cart->envArr);
	}
}

/**
 * convertLLtoArr - convert linked list to array
 * @cart: input cart
 */
void convertLLtoArr(config *cart)
{
	register int i = 0;
	size_t count = 0;
	char **envArr = NULL;
	link_l *tmp = cart->env;

	count = list_len(cart->env);
	envArr = malloc(sizeof(char *) * (count + 1));
	if (!envArr)
	{
		perror("Malloc failed\n");
		exit(1);
	}
	while (tmp)
	{
		envArr[i] = _strdup(tmp->string);
		tmp = tmp->next;
		i++;
	}
	envArr[i] = NULL;
	cart->envArr = envArr;
}
