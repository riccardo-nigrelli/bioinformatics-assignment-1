#ifndef STACK_PRIVATE_H

  #define STACK_PRIVATE_H

  #include <stddef.h>
  #include <adt/stack.h>

  /** \brief Defines the structure of each node of the singly-linked list implementing the stack. */
  struct stack_node_s {
    int data; /**< User-provided data. */
    struct stack_node_s* next; /**< Pointer to the next node in the list. */
  };

  /** \brief Defines the type of a list node. */
  typedef struct stack_node_s stack_node_t;

  /** \brief Defines the structure of the list implementing the stack. */
  struct stack_s {
    stack_node_t* top; /**< The front of the list. */
    size_t size; /**< The size of the list.*/
  };

#endif /* STACK_PRIVATE_H */
