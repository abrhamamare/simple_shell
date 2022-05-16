#include "main.h"

/**
 * freeMembers - frees cart config members
 * @cart: input cart
 */
void freeMembers(config *cart)
{
	if (cart->env)
		freeList(cart->env);
	if (cart->args)
		freeArgs(cart->args);
	if (cart->buffer)
		free(cart->buffer);
}

/**
 * freeArgsAndBuffer - frees args and buffer
 * @cart: input cart
 */
void freeArgsAndBuffer(config *cart)
{
	freeArgs(cart->args);
	free(cart->buffer);
}

/**
 * freeList - frees a linked list
 * @head: double pointer to head of list
 */
void freeList(link_l *head)
{
	link_l *current;
	link_l *tmp;

	if (!head)
		return;
	current = head;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		free(tmp->string);
		free(tmp);
	}
	head = NULL;
}

/**
 * freeArgs - helper func that frees double pointer arg
 * @args: array of char pointers
 */
void freeArgs(char **args)
{
	register uint i = 0;

	while (args[i])
		free(args[i++]);
	free(args);
}
