#include "main.h"

/**
 * exitFunc - exits the application
 * @cart: input cart
 * Return: 1 on success, 0 on failure
 */
int exitFunc(config *cart)
{
	register int argCount, exitStatus;

	argCount = countArgs(cart->args);
	if (argCount == 1)
	{
		freeMembers(cart);

		if (cart->errorStatus)
			exit(cart->errorStatus);
		exit(EXIT_SUCCESS);
	}
	else if (argCount > 1)
	{
		exitStatus = _atoi(cart->args[1]);
		if (exitStatus == -1)
		{
			errno = EILLEGAL;
			cart->errorStatus = 2;
			errorHandler(cart);
			return (0);
		}
		freeMembers(cart);
		exit(exitStatus);
	}
	return (1);
}
