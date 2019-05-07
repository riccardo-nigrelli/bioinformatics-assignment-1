#ifndef HASH_TABLE_PRIVATE_H

  #define HASH_TABLE_PRIVATE_H

  #include <adt/hash_table.h>

  struct hash_table_list_node_s {
    char *key;
    unsigned int value;
    struct hash_table_list_node_s *next;
  };

  typedef struct hash_table_list_node_s hash_table_list_node_t;

  struct hash_table_slot_s {
    hash_table_list_node_t *head;
  };
  
  typedef struct hash_table_slot_s hash_table_slot_t;

  struct hash_table_s {
    hash_table_slot_t* slots;
    size_t capacity;
    size_t size;
    hasher_t key_hash;
    comparator_t key_cmp;
  };

#endif /* HASH_TABLE_PRIVATE_H */
