#include "main.h"

/**
 * helpHistory - instructions on how to exit
 * @cart: input cart
 * Return: Always 1
 */
int helpHistory(config *cart)
{
	char str[] = "history: history\n\tNot supported in this version.\n";

	(void)cart;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
