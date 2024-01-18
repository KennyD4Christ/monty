#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "monty.h"
#include <limits.h>

int mode = LIFO;

/**
 *  * pint - prints the value at the top of the stack
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void pint(stack_t **stack, unsigned int line_number)
{
/* Check if the stack is empty */
if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
exit(EXIT_FAILURE);
}
/* Print the value at the top of the stack */
printf("%d\n", (*stack)->n);
}

/**
 *  * pop - removes the top element of the stack
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void pop(stack_t **stack, unsigned int line_number)
{
stack_t *temp;
/* Check if the stack is empty */
if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
exit(EXIT_FAILURE);
}
/* Remove the top element of the stack */
temp = *stack;
if (mode == LIFO)
{
*stack = (*stack)->next;
if (*stack != NULL)
(*stack)->prev = NULL;
}
else
{
/* Traverse to the end of the queue */
while (temp->next != NULL)
temp = temp->next;
/* Update the top of the stack */
if (temp->prev != NULL)
temp->prev->next = NULL;
else
*stack = NULL;
}
free(temp);
}

/**
 *  * swap - swaps the top two elements of the stack
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void swap(stack_t **stack, unsigned int line_number)
{
stack_t *first;
stack_t *second;
/* Check if the stack contains less than two elements */
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
/* Swap the top two elements of the stack */
first = *stack;
second = first->next;
first->prev = second;
first->next = second->next;
second->prev = NULL;
second->next = first;
*stack = second;
if (first->next)
first->next->prev = first;
}

/**
 *  * add - adds the top two elements of the stack
 *   * @stack: double pointer to the head of the stack
 *    * @line_number: line number in the Monty file
 */
void add(stack_t **stack, unsigned int line_number)
{
stack_t *temp;
/* Check if the stack contains less than two elements */
if (!stack || !*stack || !((*stack)->next))
{
fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
/* Check for integer overflow before adding */
if ((*stack)->n > INT_MAX - (*stack)->next->n)
{
fprintf(stderr, "L%u: integer overflow\n", line_number);
exit(EXIT_FAILURE);
}
if (mode == LIFO)
{
/* Add the top two elements of the stack */
(*stack)->next->n += (*stack)->n;
/* Remove the top element of the stack */
temp = *stack;
*stack = (*stack)->next;
if (*stack != NULL)
(*stack)->prev = NULL;
free(temp);
}
else if (mode == FIFO)
{
/* Add the top two elements of the stack */
(*stack)->next->n += (*stack)->n;
/* Remove the top element of the stack */
temp = (*stack)->next;
if (temp->next != NULL)
{
temp->next->prev = *stack;
(*stack)->next = temp->next;
}
else
{
(*stack)->next = NULL;
}
free(temp);
}
}

/**
 *  * main - entry point of the program
 *   * @argc: number of command-line arguments
 *    * @argv: array of command-line arguments
 *     * Return: 0 on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
FILE *file;
char *line = NULL;
size_t len = 0;
ssize_t read;
char *opcode;
int i;
unsigned int line_number = 0;
stack_t *stack_ptr = NULL;
(void)mode;
/* Check the number of command-line arguments */
if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
file = fopen(argv[1], "r");
if (!file)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}
/* Read the file line by line */
while ((read = getline(&line, &len, file)) != (ssize_t)-1)
{
line_number++;
if (line[0] == '#' || line[0] == '\n')
continue;
opcode = strtok(line, " \n\t");
if (opcode)
{
for (i = 0; opcode[i]; i++)
opcode[i] = tolower(opcode[i]);
if (strcmp(opcode, "push") == 0)
push(&stack_ptr, line_number, mode);
else if (strcmp(opcode, "pall") == 0)
pall(stack_ptr, line_number);
else if (strcmp(opcode, "pint") == 0)
pint(&stack_ptr, line_number);
else if (strcmp(opcode, "pop") == 0)
pop(&stack_ptr, line_number);
else if (strcmp(opcode, "swap") == 0)
swap(&stack_ptr, line_number);
else if (strcmp(opcode, "add") == 0)
add(&stack_ptr, line_number);
else if (strcmp(opcode, "nop") == 0)
nop(&stack_ptr, line_number);
else if (strcmp(opcode, "sub") == 0)
sub(&stack_ptr, line_number);
else if (strcmp(opcode, "div") == 0)
div_op(&stack_ptr, line_number);
else if (strcmp(opcode, "mul") == 0)
mul(&stack_ptr, line_number);
else if (strcmp(opcode, "mod") == 0)
mod(&stack_ptr, line_number);
else if (strcmp(opcode, "pchar") == 0)
pchar(&stack_ptr, line_number);
else if (strcmp(opcode, "pstr") == 0)
pstr(&stack_ptr, line_number);
else if (strcmp(opcode, "rotl") == 0)
rotl(&stack_ptr, line_number);
else if (strcmp(opcode, "rotr") == 0)
rotr(&stack_ptr, line_number);
else if (strcmp(opcode, "stack") == 0)
stack(&stack_ptr, line_number);
else if (strcmp(opcode, "queue") == 0)
queue(&stack_ptr, line_number);
else
{
fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
free_stack(stack_ptr);
fclose(file);
free(line);
exit(EXIT_FAILURE);
}
}
}
return (0);
}
