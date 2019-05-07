#include <stdio.h>
#include <stdlib.h>
#include "stack_private.h"


sstack_t stack_create() {

  sstack_t stack = malloc(sizeof(struct stack_s));
  if ( stack == NULL ) {
    fprintf(stderr, "Unable to create a stack!\n");
    abort();
  }

  stack->top = NULL;
  stack->size = 0;

  return stack;
}

void stack_destroy(sstack_t stack) {

  if ( stack != NULL ) {
    stack_clear(stack);
    free(stack);
  }
}

void stack_push(sstack_t stack, int data){ 
  
  if( stack != NULL ) {
    stack_node_t *node= malloc(sizeof(stack_node_t));
    node->data = data;
    node->next = stack->top;

    stack->top = node;
    stack->size++;
  }
}

int stack_pop(sstack_t stack) {

  int value = -1;

  if( stack != NULL ) {
    if( stack_is_empty(stack) != 1 ){
      stack_node_t *tmp = stack->top;
      value = stack->top->data;
      /* free(stack->top->data); */
      stack->top = stack->top->next;
      free(tmp);
      stack->size--;
    }
  }

  return value;
}

int stack_top(const sstack_t stack) {

  if( stack != NULL && stack->top != NULL)
    return stack->top->data;
  
  return -1;
}

int stack_is_empty(const sstack_t stack) {

  if ( stack != NULL ) return ( stack->size == 0 ) ? 1 : 0;
  else return -1;
}

size_t stack_size(const sstack_t stack) {
  return ( stack != NULL ) ? stack->size : -1;
}

void stack_clear(sstack_t stack) {

  if( stack!=NULL ) {
    while ( stack->size != 0 ) {
      stack_node_t *tmp = stack->top;

      stack->top = stack->top->next;
      free(tmp);
      stack->size--;
    }
  }
}
