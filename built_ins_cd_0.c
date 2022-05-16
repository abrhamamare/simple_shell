#include "main.h"

/**
 * cdFunc - execute cd builtin
 * @cart: input cart
 * Return: 1 on success, 0 on failure
 */
int cdFunc(config *cart)
{
	register uint count = 0;
	int ableToChange = FALSE;

	count = countArgs(cart->args);
	if (count == 1)
		ableToChange = cdToHome(cart);
	else if (count == 2 && _strcmp(cart->args[1], "-") == 0)
		ableToChange = cdToPrevious(cart);
	else
		ableToChange = cdToCustom(cart);
	if (ableToChange)
		updateEnviron(cart);
	return (1);
}

/**
 * cdToHome - change directory to home
 * @cart: input cart
 * Return: TRUE on success, FALSE on failure
 */
int cdToHome(config *cart)
{
	register int i;
	char *str, *ptr;

	i = searchNode(cart->env, "HOME");
	if (i == -1)
	{
		return (TRUE);
	}
	str = getNodeAtIndex(cart->env, i);
	ptr = _strchr(str, '=');
	ptr++;
	chdir(ptr);
	free(str);
	return (TRUE);
}

/**
 * cdToPrevious - change directory to previous directory -
 * address is found in OLDPWD env var
 * @cart: input cart
 * Return: TRUE on success, FALSE on failure
 */
int cdToPrevious(config *cart)
{
	register int i;
	char *str, *ptr;
	char *current = NULL;

	current = getcwd(current, 0);
	i = searchNode(cart->env, "OLDPWD");
	if (i == -1)
	{
		chdir(current);
		write(STDOUT_FILENO, current, _strlen(current));
		displayNewLine();
		return (TRUE);
	}
	str = getNodeAtIndex(cart->env, i);
	ptr = _strchr(str, '=');
	ptr++;
	chdir(ptr);
	write(STDOUT_FILENO, ptr, _strlen(ptr));
	displayNewLine();
	free(str);
	return (TRUE);
}

/**
 * cdToCustom - change directory to what user inputs in
 * @cart: input cart
 * Return: TRUE on success, FALSE on failure
 */
int cdToCustom(config *cart)
{
	register int changeStatus;

	changeStatus = chdir(cart->args[1]);
	if (changeStatus == -1)
	{
		errno = EBADCD;
		errorHandler(cart);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * updateEnviron - change environmental variables
 * @cart: input cart
 * Return: TRUE on success FALSE on failure
 */
int updateEnviron(config *cart)
{
	register int i;

	i = updateOld(cart);
	updateCur(cart, i);
	return (TRUE);
}
