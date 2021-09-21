#include "stack.h"
#include <stdlib.h>

/* Create stack
 * int size = capacity of stack
 * char peg = peg name */
Stack *stack_create(int size, char peg) {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->name = peg;
  if (!s) {
    return 0;
  }
  if (size < 1) {
    size = 1;
  }
  s->capacity = size;
  s->top = 0;

  s->items = (int *)malloc(sizeof(int) * size);
  if (!s->items) {
    return 0;
  }
  return s;
}

/* Push to stack
 * int i    = disk number
 * Stack *s = stack to push i to */
void stack_push(Stack *s, int i) {
  if (!s) {
    return;
  }
  if (s->top == s->capacity) {
    s->capacity *= 2;
    s->items = (int *)realloc(s->items, s->capacity * sizeof(int));
  }
  if (s->items) {
    s->items[s->top] = i;
    s->top += 1;
  }
  return;
}

/* Pop out of stack
 * Stack *s = stack to pop from
 * Returns the top item in stack */
int stack_pop(Stack *s) {
  if (s->top > 0) {
    s->top -= 1;
    return s->items[s->top];
  } else {
    return -1;
  }
}

/* Check if stack is empty
 * Returns bool if stack is empty */
bool stack_empty(Stack *s) {
  return s->top == 0;
}

/* Delete stack
 * Stack *s = stack to free */
void stack_delete(Stack *s) {
  free(s->items);
  free(s);
  return;
}
