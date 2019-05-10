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

  /**
   * @brief Create a new empty hash table
   * @param Hash table dimension
   * @param hash function
   * @param Function for compare two key
   * @return An empty hash table
   */ 
  hash_table_t hash_table_create(size_t dimension, hasher_t key_hash, comparator_t key_cmp);

  /**
   * @brief Destroy an hash table
   * @param Hash table
   */ 
  void hash_table_destroy(hash_table_t hash_table);
  
  /**
   * @brief Support function for hash_table_destroy
   * @param Hash table
   */ 
  void hash_table_clear(hash_table_t hash_table);

  /**
   * @brief Insert element in the hash table
   * @param Hash table
   * @param The key to insert
   * @param The value associate to the key
   */ 
  void hash_table_put(hash_table_t hash_table, char *key, unsigned int value);
  
  /**
   * @brief Get value of specif key
   * @param Hash table
   * @param The key
   * @return If the key exists return the associate value, 0 otherwise
   */ 
  unsigned int hash_table_get(hash_table_t hash_table, char *key);
  
  /**
   * @brief Delete a key 
   * @param Hash table
   * @param The key to delete
   */ 
  void hash_table_delete(hash_table_t hash_table, char *key);
  
  /**
   * @brief Create a list of hash table keys 
   * @param Hash table
   * @return If the hash table doesn't exist NULL, the keys list oterwise
   */ 
  hash_table_key_list_t hash_table_keys(hash_table_t hash_table);
    
  /**
   * @brief Return the size of the hash table
   * @param Hash table 
   * @return The size if the hash table exist, 0 otherwise
   */ 
  size_t hash_table_size(hash_table_t hash_table);

  int str_compare(const void* a, const void* b);
  size_t hash_table_hash_str(const void* s, size_t h0, size_t a, size_t m);
  size_t hash_table_str_kr2e(const void* s, size_t m);

#endif /* HASH_TABLE_H */
