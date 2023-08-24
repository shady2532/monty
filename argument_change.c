#include "monty.h"

/**
 * stackk - changes mode of push to stack
 * @stack: pointer to stack
 * @nline: line number
 *
 * Return: Nothing.
 */
void stackk(stack_t **stack, unsigned int nline)
{
	(void)nline;
	(void)stack;

	arg.flag = 0;
}

/**
 * que - changes mode of push to queue
 * @stack: pointer to stack
 * @nline: line number
 *
 * Return: Nothing.
 */
void que(stack_t **stack, unsigned int nline)
{
	(void)nline;
	(void)stack;

	arg.flag = 1;
}