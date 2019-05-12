#ifndef STACK_H

  #define STACK_H

  #include <stddef.h>

  /** \brief Declares the Stack type. */
  typedef struct stack_s* sstack_t;

  /**
   * \brief Creates a new stack.
   *
   * \return A stack.
   */
  sstack_t stack_create();

  /**
   * \brief Destroys the given stack.
   *
   * \param stack The stack to destroy.
   */
  void stack_destroy(sstack_t stack);

  /**
   * \brief Add an element to the top of the given stack.
   *
   * \param stack The stack to which adding a new element.
   * \param data The new element.
   */
  void stack_push(sstack_t stack, int data);

  /**
   * \brief Remove and return an element from the top of the given stack.
   *
   * \param stack The stack from which removing an element.
   * \retunr The removed element
   */
  int stack_pop(sstack_t stack);
  
  /**
   * \brief Tells if the given stack is empty.
   *
   * \param stack The stack.
   * \return `1` if the stack is empty or `0` otherwise.
   */
  int stack_is_empty(const sstack_t stack);

  /**
   * \brief Removes all elements from the given stack.
   *
   * \param stack The stack.
   */
  void stack_clear(sstack_t stack);

#endif /* STACK_H */
