#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "monty.h"


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
*stack = (*stack)->next;
if (*stack != NULL)
(*stack)->prev = NULL;
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
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
/* Add the top two elements of the stack */
(*stack)->next->n += (*stack)->n;
/* Remove the top element of the stack */
temp = *stack;
*stack = (*stack)->next;
if (*stack != NULL)
(*stack)->prev = NULL;
free(temp);
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
unsigned int line_number = 0;
stack_t *stack = NULL;
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
opcode = strtok(line, " \n\t");
if (opcode)
{
if (strcmp(opcode, "push") == 0)
push(&stack, line_number);
else if (strcmp(opcode, "pall") == 0)
pall(stack, line_number);
else if (strcmp(opcode, "pint") == 0)
pint(&stack, line_number);
else if (strcmp(opcode, "pop") == 0)
pop(&stack, line_number);
else if (strcmp(opcode, "swap") == 0)
swap(&stack, line_number);
else if (strcmp(opcode, "add") == 0)
add(&stack, line_number);
else if (strcmp(opcode, "nop") == 0)
nop(&stack, line_number);
else if (strcmp(opcode, "sub") == 0)
sub(&stack, line_number);
}
}
free_stack(stack);
fclose(file);
free(line);
return (0);
}
