#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "monty.h"

/**
 *  * rotl - rotates the stack to the top
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void rotl(stack_t **stack, unsigned int line_number)
{
stack_t *first;
stack_t *last;
(void)line_number;
/* Check if the stack is empty or has only one element */
if (!*stack || !(*stack)->next)
return;
first = *stack;
last = *stack;
/* Traverse to the last element of the stack */
while (last->next)
last = last->next;
/* Update pointers to rotate the stack */
*stack = first->next;
(*stack)->prev = NULL;
first->next = NULL;
last->next = first;
first->prev = last;
}
