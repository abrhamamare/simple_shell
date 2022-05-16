#include "main.h"

/**
 * helpEnv - instructions on how to exit
 * @cart: input cart
 * Return: Always 1
 */
int helpEnv(config *cart)
{
	char str[] = "env: env\n\tPrint the environment.\n";

	(void)cart;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
