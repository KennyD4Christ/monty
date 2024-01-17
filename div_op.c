#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "monty.h"

/**
 *  * div_op - divides the second top element of the stack by the top element
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void div_op(stack_t **stack, unsigned int line_number)
{
stack_t *temp;
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
if ((*stack)->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}
temp = (*stack)->next;
if (temp->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}
printf("Before: top=%d, second=%d\n", (*stack)->n, temp->n);
temp->n /= (*stack)->n;
printf("After: top=%d, second=%d\n", (*stack)->n, temp->n);
temp->prev = NULL;
free(*stack);
*stack = temp;
}
