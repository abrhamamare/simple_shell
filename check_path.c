#include "main.h"

/**
 * checkPath - searches $PATH for directory of command
 * @cart: input cart
 * Return: False
 */
int checkPath(config *cart)
{
	register int len;
	static char buffer[BUFSIZE];
	struct stat st;
	char *tok, *copy, *delim = ":", *tmp;
	int inLoop = FALSE;

	if (checkEdgeCases(cart))
		return (TRUE);
	copy = _strdup(cart->path);
	tok = _strtok(copy, delim);
	while (tok)
	{
		tmp = inLoop ? tok - 2 : tok;
		if (*tmp == 0 && stat(cart->args[0], &st) == 0)
		{
			cart->fullPath = cart->args[0];
			free(copy);
			return (TRUE);
		}
		len = _strlen(tok) + _strlen(cart->args[0]) + 2;
		_strcat(buffer, tok);
		_strcat(buffer, "/");
		_strcat(buffer, cart->args[0]);
		insertNull(buffer, len - 1);
		if (stat(buffer, &st) == 0)
		{
			free(copy);
			cart->fullPath = buffer;
			return (TRUE);
		}
		insertNull(buffer, 0);
		tok = _strtok(NULL, delim);
		inLoop = TRUE;
	}
	cart->fullPath = cart->args[0];
	free(copy);
	return (FALSE);
}

/**
 * checkEdgeCases - helper func for check path to check edge cases
 * @cart: input cart
 * Return: TRUE if found, FALSE if not
 */
int checkEdgeCases(config *cart)
{
	char *copy;
	struct stat st;

	copy = _strdup(cart->path);
	if (!copy)
	{
		cart->fullPath = cart->args[0];
		free(copy);
		return (TRUE);
	}
	if (*copy == ':' && stat(cart->args[0], &st) == 0)
	{
		cart->fullPath = cart->args[0];
		free(copy);
		return (TRUE);
	}
	free(copy);
	return (FALSE);
}
