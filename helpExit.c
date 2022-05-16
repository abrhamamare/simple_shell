#include "main.h"
/**
 * helpExit - instructions on how to exit
 * @cart: input cart
 * Return: Always 1
 */
int helpExit(config *cart)
{
	char str[82] = "exit: exit [n]\n\tExit the shell.\n\n\t";
	char *str2 = "Exit with a status of n, or if n is omitted, 0.\n";

	(void)cart;
	_strcat(str, str2);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
