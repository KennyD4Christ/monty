#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "monty.h"

/**
 *  * nop - doesn't do anything
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void nop(stack_t **stack, unsigned int line_number)
{
(void)stack; /* Avoid unused variable warning */
(void)line_number; /* Avoid unused variable warning */
/* nop doesn't do anything */
}

/**
 *  * sub - subtracts the top element from the second top element of the stack
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void sub(stack_t **stack, unsigned int line_number)
{
stack_t *temp;
/* Check if the stack contains less than two elements */
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
/* Subtract the top element from the second top element of the stack */
(*stack)->next->n -= (*stack)->n;
/* Remove the top element of the stack */
temp = *stack;
*stack = (*stack)->next;
if (*stack != NULL)
(*stack)->prev = NULL;
free(temp);
}
