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

/**
 *  * mul - multiplies the second top element of the stack with the top element
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void mul(stack_t **stack, unsigned int line_number)
{
/* Check if the stack contains less than two elements */
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
/* Multiply the top two elements of the stack */
(*stack)->next->n *= (*stack)->n;
/* Remove the top element of the stack */
pop(stack, line_number);
}

/**
 *  * mod - computes the rest of the division of the second top element
 *   *       of the stack by the top element
 *    * @stack: double pointer to the head of the stack
 *     * @line_number: line number in the Monty file
 */
void mod(stack_t **stack, unsigned int line_number)
{
/* Check if the stack contains less than two elements */
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
/* Check if the top element of the stack is 0 */
if ((*stack)->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}
/* Compute the rest of the division */
(*stack)->next->n %= (*stack)->n;
/* Remove the top element of the stack */
pop(stack, line_number);
}

/**
 *  * pchar - prints the char at the top of the stack, followed by a new line
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void pchar(stack_t **stack, unsigned int line_number)
{
int ascii_value;
/* Check if the stack is empty */
if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
exit(EXIT_FAILURE);
}
/* Get the ASCII value from the top of the stack */
ascii_value = (*stack)->n;
/* Check if the value is in the ASCII table range */
if (ascii_value < 0 || ascii_value > 127)
{
fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
exit(EXIT_FAILURE);
}
/* Print the character and a new line */
putchar(ascii_value);
putchar('\n');
}
