#ifndef HASH_TABLE_H

  #define HASH_TABLE_H

  #define HASH_TABLE_CAPACITY 997U
  #include <stddef.h>

  typedef size_t (*hasher_t)(const void*, size_t);
  typedef int (*comparator_t)(const void*, const void*);
  typedef void (*visitor_t)(void*, void*, void*);

  struct hash_table_key_list_node_s {
    char *key;
    struct hash_table_key_list_node_s* next;
  };

  typedef struct hash_table_key_list_node_s hash_table_key_list_node_t;
  typedef hash_table_key_list_node_t* hash_table_key_list_t;
  typedef struct hash_table_s* hash_table_t;

  hash_table_t hash_table_create(size_t dimension, hasher_t key_hash, comparator_t key_cmp);
  void hash_table_destroy(hash_table_t hash_table);
  void hash_table_clear(hash_table_t hash_table);
  unsigned int hash_table_put(hash_table_t hash_table, char *key, unsigned int value);
  unsigned int hash_table_get(hash_table_t hash_table, char *key);
  void upo_ht_sepchain_delete(hash_table_t hash_table, char *key);
  hash_table_key_list_t hash_table_keys(hash_table_t hash_table);
  int hash_table_contains(hash_table_t hash_table, char *key);
  size_t hash_table_size(hash_table_t hash_table);

  int str_compare(const void* a, const void* b);

  size_t hash_table_hash_str(const void* s, size_t h0, size_t a, size_t m);
  size_t hash_table_str_kr2e(const void* s, size_t m);

#endif /* HASH_TABLE_H */
