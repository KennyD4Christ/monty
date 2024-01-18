#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "monty.h"

/**
 *  * push - pushes an element onto the stack
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void push(stack_t **stack, unsigned int line_number, int mode)
{
stack_t *new_node;
char *arg;
int value;
int i;
arg = strtok(NULL, " \n\t");
if (!arg)
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}
for (i = 0; arg[i] != '\0'; i++)
{
if (i == 0 && (arg[i] == '-' || arg[i] == '+'))
continue;
if (!isdigit((unsigned char)arg[i]))
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}
}
value = atoi(arg);
new_node = malloc(sizeof(stack_t));
if (!new_node)
{
fprintf(stderr, "Error: malloc failed\n");
exit(EXIT_FAILURE);
}
new_node->n = value;
new_node->prev = NULL;
new_node->next = NULL;
if (mode == LIFO)
{
if (*stack)
{
new_node->next = *stack;
(*stack)->prev = new_node;
}
*stack = new_node;
}
else if (mode == FIFO)
{
stack_t *temp = *stack;
while (temp != NULL && temp->next != NULL)
temp = temp->next;
if (temp != NULL)
{
temp->next = new_node;
new_node->prev = temp;
}
else
{
*stack = new_node;
}
}
}

/**
 *  * queue - sets the format of the data to a queue (FIFO)
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void queue(stack_t **stack, unsigned int line_number)
{
(void)line_number;
mode = FIFO;
if (*stack != NULL)
{
stack_t *last = *stack;
while (last->next != NULL)
{
last = last->next;
}
if (last != *stack) /* If there is more than one element in the stack */
{
(*stack)->next->prev = last;
last->next = (*stack)->next;
(*stack)->next = NULL;
(*stack)->prev = NULL;
*stack = last;
}
}
}

/**
 *  * stack - sets the format of the data to a stack (LIFO)
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void stack(stack_t **stack, unsigned int line_number)
{
(void)line_number;
mode = LIFO;
if (*stack != NULL)
{
stack_t *current = *stack;
stack_t *prev = NULL;
stack_t *next = NULL;
while (current != NULL)
{
next = current->prev;
current->prev = prev;
current->next = next;
prev = current;
current = next;
}
*stack = prev; /* Update the stack pointer to the new top */
}
}

/**
 *  * pall - prints all values on the stack
 *   * @stack: pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void pall(stack_t *stack, unsigned int line_number)
{
/* Check if the stack is empty */
if (!stack)
{
fprintf(stderr, "L%u: stack is empty\n", line_number);
exit(EXIT_FAILURE);
}
while (stack)
{
printf("%d\n", stack->n);
stack = stack->next;
}
}

/**
 *  * free_stack - frees the memory allocated for the stack
 *   * @stack: pointer to the head of the stack
 */
void free_stack(stack_t *stack)
{
stack_t *current = stack;
stack_t *next;
while (current != NULL)
{
next = current->next;
free(current);
current = next;
}
}
