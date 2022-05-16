#include "main.h"

/**
 * helpFunc - retrieves instruction on how to use builtin
 * @cart: input cart
 * Return: Always 1
 */
int helpFunc(config *cart)
{
	type_b help_arr[] = {
				{"exit", helpExit},
				{"env", helpEnv},
				{"history", helpHistory},
				{"alias", helpAlias},
				{"cd", helpCd},
				{"setenv", helpSetenv},
				{"unsetenv", helpUnsetenv},
				{"help", helpHelp},
				{NULL, NULL}};
	register int i = 0, j = 1, argCount = countArgs(cart->args);
	int foundCommand = FALSE;

	if (argCount == 1)
	{
		return (displayHelpMenu());
		while (j < argCount)
		{
			i = 0;
			while (help_arr[i].command)
			{
				if (_strcmp(cart->args[j], help_arr[i].command) == 0)
				{
					foundCommand = TRUE;
					help_arr[i].func(cart);
					break;
				}
				i++;
			}
			j++;
		}
		if (foundCommand == FALSE)
		{
			errno = ENOBUILTIN;
			errorHandler(cart);
		}
	}
return (1);
}
