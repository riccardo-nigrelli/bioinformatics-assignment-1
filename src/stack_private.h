#ifndef STACK_PRIVATE_H

  #define STACK_PRIVATE_H

  #include <stddef.h>
  #include <adt/stack.h>

  struct stack_node_s {
    char *data;
    struct stack_node_s* next;
  };

  typedef struct stack_node_s stack_node_t;

  struct stack_s {
    stack_node_t* top;
    size_t size;
  };


#endif /* STACK_PRIVATE_H */
