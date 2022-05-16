#include "main.h"

/**
 * updateOld - updates OLDPWD to current PWD
 * @cart: input cart
 * Return: index in linked list of PWD on success -
 * If PWD or OLDPWD does not exist in environ vars,
 * return -1
 */
int updateOld(config *cart)
{
	register int pwdIndex = 0, index = 0;
	static char old[BUFSIZE];
	char *current = NULL;

	_strcat(old, "OLD");
	pwdIndex = searchNode(cart->env, "PWD");
	if (pwdIndex == -1)
	{
		return (-1);
	}
	current = getNodeAtIndex(cart->env, pwdIndex);
	_strcat(old, current);
	insertNull(old, _strlen(current) + 4);
	free(current);
	index = searchNode(cart->env, "OLDPWD");
	if (index == -1)
	{
		return (-1);
	}
	deleteNodeAtIndex(&cart->env, index);
	addNodeAtIndex(&cart->env, index, old);
	insertNull(old, 0);
	return (pwdIndex);
}

/**
 * updateCur - updates PWD to accurately reflect current directory
 * @cart: input cart
 * @index: index in linked list of where to insert PWD env var
 * Return: TRUE on success, FALSE on failure
 */
int updateCur(config *cart, int index)
{
	static char tmp[BUFSIZE], cwd[BUFSIZE];

	getcwd(tmp, BUFSIZE);
	_strcat(cwd, "PWD=");
	_strcat(cwd, tmp);
	if (index > -1)
	{
		deleteNodeAtIndex(&cart->env, index);
		addNodeAtIndex(&cart->env, index, cwd);
	}
	else
		addNodeAtIndex(&cart->env, 0, cwd);
	insertNull(tmp, 0);
	insertNull(cwd, 0);
	return (TRUE);
}
