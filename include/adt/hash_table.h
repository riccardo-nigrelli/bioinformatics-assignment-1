#ifndef HASH_TABLE_H

  #define HASH_TABLE_H

  #define HASH_TABLE_CAPACITY 997U
  #include <stddef.h>

  /** \brief The type for hash functions.
   *
   * A hash function takes two parameters:
   * - The first parameter is a pointer to the key to hash.
   * - The second parameter is the capacity of the hash table.
   * A hash function returns a nonnegative number which represents a position
   * (index) in the hash table.
   */
  typedef size_t (*hasher_t)(const void*, size_t);

  /**
   * \brief The type for key comparison functions.
   * 
   * A comparison function takes two parameters:
   * - The first parameter is a pointer to the first key to compare.
   * - The second parameter is a pointer to the second key to compare.
   * A comparison function returns a number less than, equal to, or greater than
   * zero if the first key (first argument) is less than, equal to, or greater
   * than the second key (second argument), respectively.
   */
  typedef int (*comparator_t)(const void*, const void*);

  /** 
   * \brief The type for nodes of list of keys. 
   */
  struct hash_table_key_list_node_s {
    char *key; /**< Pointer to the key. */
    struct hash_table_key_list_node_s* next; /**< Pointer to the next node in the list. */
  };

  /** \brief Alias for the type for nodes of list of keys. */
  typedef struct hash_table_key_list_node_s hash_table_key_list_node_t;
  /** \brief The type for list of keys. */
  typedef hash_table_key_list_node_t* hash_table_key_list_t;
  /** \brief Type for hash tables with separate chaining. */
  typedef struct hash_table_s* hash_table_t;

  /**
   * \brief Creates a new empty hash table.
   *
   * \param m The initial capacity of the hash table.
   * \param key_hash A pointer to the function used to hash keys.
   * \param key_cmp A pointer to the function used to compare keys.
   * \return An empty hash table.
   */
  hash_table_t hash_table_create(size_t dimension, hasher_t key_hash, comparator_t key_cmp);

  /**
   * \brief Destroys the given hash table.
   *
   * \param hash_table The hash table to destroy.
   */
  void hash_table_destroy(hash_table_t hash_table);

  /**
   * \brief Removes all key-value pairs from the given hash table.
   *
   * \param hash_table The hash table to clear.
   */
  void hash_table_clear(hash_table_t hash_table);

  /**
   * \brief Insert the given value identified by the provided key in the given
   *  hash table.
   *
   * \param hash_table The hash table.
   * \param key The key.
   * \param value The value.
   */
  void hash_table_put(hash_table_t hash_table, char *key, unsigned int value);

  /**
   * \brief Returns the value identified by the provided key in the given
   *  hash table.
   *
   * \param hash_table The hash table.
   * \param key The key.
   * \return The value associated to \a key, or 0 if the key is not found.
   */
  unsigned int hash_table_get(hash_table_t hash_table, char *key);  

  /**
   * \brief Removes the value identified by the provided key in the given
   *  hash table.
   *
   * \param hash_table The hash table.
   * \param key The key.
   */
  void hash_table_delete(hash_table_t hash_table, char *key);  

  /**
   * \brief Returns the size of the hash table.
   *
   * \param hash_table The hash table.
   * \return The number of keys stored in the hash tables.
   */
  size_t hash_table_size(hash_table_t hash_table);

  /**
   * \brief Returns the keys in the given hash table.
   *
   * \param hash_table The hash table.
   * \return A singly-linked list of keys, or `NULL` if the hash table is empty.
   */
  hash_table_key_list_t hash_table_keys(hash_table_t hash_table);

  /**
   * \brief Destroy the given keys list
   *
   * \param key_list The key list.
   */
  void destroy_key_list(hash_table_key_list_t key_list);

  /**
   * \brief Hash function for strings.
   *
   * \param s The string to be hashed.
   * \param h0 The initial value for the hash value that is usually chosen
   *  randomly from a universal family mapping integer domain
   *  \f$\{0,\ldots,p-1\} \mapsto \{0,\ldots,m-1\}\f$.
   * \param a A multiplicative factor such that \f$a \in \{0,\ldots,p-1\}\f$ which
   *  is usually uniformly random.
   * \param m The number of possible hash values.
   * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
   */
  size_t hash_table_hash_str(const void* s, size_t h0, size_t a, size_t m);

  /**
   * \brief The Kernighan and Ritchie's hash function proposed in the second
   *  edition of their C book.
   */
  size_t hash_table_str_kr2e(const void* s, size_t m);
  
  int str_compare(const void* a, const void* b);

#endif /* HASH_TABLE_H */
