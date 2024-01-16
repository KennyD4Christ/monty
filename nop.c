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
