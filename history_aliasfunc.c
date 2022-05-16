#include "main.h"

/**
 * historyFunc - displays command history
 * @cart: input cart
 * Return: 1 on success, 0 on failure
 */
int historyFunc(config *cart)
{
		char *str = "Currently in development\n";

		(void)cart;
		write(STDOUT_FILENO, str, _strlen(str));
		return (1);
}

/**
 * aliasFunc - displays local aliases
 * @cart: input cart
 * Return: 1 on success, 0 on failure
 */
int aliasFunc(config *cart)
{
		char *str = "Currently in development\n";

		(void)cart;
		write(STDOUT_FILENO, str, _strlen(str));
		return (1);
}
