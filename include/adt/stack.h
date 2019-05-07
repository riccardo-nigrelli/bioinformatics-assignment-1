#ifndef STACK_H

	#define STACK_H

	#include <stddef.h>

	typedef struct stack_s* sstack_t;

	sstack_t stack_create();
	void stack_destroy(sstack_t stack);
	void stack_push(sstack_t stack, int data);
	int stack_pop(sstack_t stack);
	int stack_top(const sstack_t stack);
	int stack_is_empty(const sstack_t stack);
	size_t stack_size(const sstack_t stack);
	void stack_clear(sstack_t stack);

#endif /* STACK_H */
