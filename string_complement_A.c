#include "main.h"

/**
 * splitString - splits string into an array of strings
 * separated by spaces
 * @cart: input cart
 * Return: TRUE if able to split, FALSE if not
 */
int splitString(config *cart)
{
	register unsigned int i = 0;
	char *tok, *cpy;

	if (countWords(cart->buffer) == 0)
	{
		cart->args = NULL;
		free(cart->buffer);
		return (FALSE);
	}
	cart->args = malloc((countWords(cart->buffer) + 1) * sizeof(char *));
	cpy = _strdup(cart->buffer);
	tok = _strtok(cpy, " ");
	while (tok)
	{
		cart->args[i] = _strdup(tok);
		tok = _strtok(NULL, " ");
		i++;
	}
	cart->args[i] = NULL;
	free(cpy);
	return (TRUE);
}

/**
 * countWords - count number of words in a string
 * @str: input string
 * Return: number of words
 */
unsigned int countWords(char *str)
{
	register int words = 0;
	/* int wordOn = FALSE;*/

	while (*str)
	{
		if (*str != ' ' && (!*(str + 1) || (*(str + 1) == ' ')))
			words++;
		str++;
	}

	/*
	 *	{
	 *		if (isSpace(*str) && wordOn)
	 *			wordOn = FALSE;
	 *		else if (!isSpace(*str) && !wordOn)
	 *		{
	 *			wordOn = TRUE;
	 *			words++;
	 *		}
	 *		str++;
	 *	}
	*/
	return (words);
}

/**
 * isSpace - determines if char is a space
 * @c: input char
 * Return: TRUE or FALSE
 */
int isSpace(char c)
{
	return (c == ' ');
}
