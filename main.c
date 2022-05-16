#include "main.h"

/**
 * main - entry point for application
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	config cart;

	(void)ac;
	signal(SIGINT, sigintHandler);
	configInit(&cart);
	/**printf("cart->path: %s\n", cart.path);*/
	cart.shellName = av[0];
	shell(&cart);
	return (0);
}

/**
 * configInit - initialize member values for config struct
 * @cart: input cart
 * Return: cart with initialized members
 */
config *configInit(config *cart)
{
	cart->env = generateLinkedList(environ);
	cart->envArr = NULL;
	cart->args = NULL;
	cart->buffer = NULL;
	cart->path = _getenv("PATH", environ);
	cart->fullPath = NULL;
	cart->lineCounter = 0;
	cart->shellName = NULL;
	cart->errorStatus = 0;
	return (cart);
}
