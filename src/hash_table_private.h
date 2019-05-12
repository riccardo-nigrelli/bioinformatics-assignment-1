#ifndef HASH_TABLE_PRIVATE_H

  #define HASH_TABLE_PRIVATE_H

  #include <adt/hash_table.h>

  /** \brief Type for nodes of the list of collisions. */
  struct hash_table_list_node_s {
    char *key; /**< Pointer to the user-provided key. */
    unsigned int value; /**< Pointer to the value associated to the key. */
    struct hash_table_list_node_s *next; /**< Pointer to the next node in the list. */
  };

  /** \brief Alias for the type for nodes of the list of collisions. */
  typedef struct hash_table_list_node_s hash_table_list_node_t;

  /** \brief Type for slots of hash tables with separate chaining. */
  struct hash_table_slot_s {
    hash_table_list_node_t *head; /**< Pointer to the head of the list of collisions. */
  };
  
  /** \brief Alias for the type for slots of hash tables with separate chaining. */
  typedef struct hash_table_slot_s hash_table_slot_t;

  /** \brief Type for hash tables with separate chaining. */
  struct hash_table_s {
    hash_table_slot_t*  slots;/**< The hash table as array of slots. */
    size_t capacity; /**< The capacity of the hash table. */
    size_t size; /**< The number of elements stored in the hash table. */
    hasher_t key_hash; /**< The key hash function. */
    comparator_t key_cmp; /**< The key comparison function. */
  };

#endif /* HASH_TABLE_PRIVATE_H */
