#include "main.h"

/**
 * findBuiltIns - validates if command is builtin and executes
 * @cart: input cart
 * Return: TRUE if found, FALSE if not
 */
int findBuiltIns(config *cart)
{
		register int i = 0;
		type_b BuiltIns[] = {
						{"exit", exitFunc},
						{"env", envFunc},
						{"history", historyFunc},
						{"alias", aliasFunc},
						{"cd", cdFunc},
						{"setenv", setenvFunc},
						{"unsetenv", unsetenvFunc},
						{"help", helpFunc},
						{NULL, NULL}};

		while (BuiltIns[i].command)
		{
			if (_strcmp(cart->args[0], BuiltIns[i].command) == 0)
			{
				BuiltIns[i].func(cart);
				freeArgsAndBuffer(cart);
				return (TRUE);
			}
			i++;
		}
	return (FALSE);
}
