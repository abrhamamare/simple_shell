#include "main.h"

/**
 * _getenv - retrieves env variable that matches input string
 * @input: input string
 * @environ: local environmental variables
 * Return: string of env variable
 */
char *_getenv(char *input, char **array)
{
	char *current = NULL;
	register int i = 0;
	char *tok, *right;

	while (array[i])
	{
		current = _strdup(array[i]);
		tok = _strtok(current, "=");
		if (_strcmp(tok, input) == 0)
		{
			right = _strdup(_strtok(NULL, "="));
			free(current);
			return (right);
		}
		i++;
		free(current);
	}
	return (NULL);
}

/**
 * envFunc - prints the environment
 * @cart: input cart
 * Return: Always 1
 */
int envFunc(config *cart)
{
	printList(cart->env);
	return (1);
}

/**
 * setenvFunc - adds env variable if it does not exist;
 * modify env variable if it does
 * @cart: input cart
 * Return: Always 1
 */
int setenvFunc(config *cart)
{
	register int index, len;
	static char buffer[BUFSIZE];

	if (countArgs(cart->args) != 3)
	{
		errno = EWSIZE;
		errorHandler(cart);
		return (1);
	}
	len = _strlen(cart->args[1]) + _strlen(cart->args[2]) + 2;
	_strcat(buffer, cart->args[1]);
	_strcat(buffer, "=");
	_strcat(buffer, cart->args[2]);
	insertNull(buffer, len - 1);
	index = searchNode(cart->env, cart->args[1]);
	if (index == -1)
	{
		nodeAppend(&cart->env, buffer);
		insertNull(buffer, 0);
		return (1);
	}
	deleteNodeAtIndex(&cart->env, index);
	addNodeAtIndex(&cart->env, index, buffer);
	insertNull(buffer, 0);
	return (1);
}

/**
 * unsetenvFunc - deletes env variable if exists;
 * will only accept valid variables names
 * @cart: input cart
 * Return: Always 1
 */
int unsetenvFunc(config *cart)
{
	register int foundVar, i = 1;
	int foundMatch = FALSE;

	while (cart->args[i])
	{
		if (_isalpha(cart->args[i][0]) || cart->args[i][0] == '_')
		{
			foundVar = searchNode(cart->env, cart->args[i]);
			if (foundVar > -1)
			{
				deleteNodeAtIndex(&cart->env, foundVar);
				foundMatch = TRUE;
			}
		}
		i++;
	}
	if (foundMatch == FALSE)
	{
		errno = ENOSTRING;
		errorHandler(cart);
	}
	return (1);
}

/**
 * _isalpha - checks if c is an alphabetic character
 * @c: potential alphabetical value
 * Return: if c is a letter, returns 1. Otherwise, return 0.
 */
int _isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (1);
	else
		return (0);
}
