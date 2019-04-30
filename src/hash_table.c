#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hash_table_private.h"

hash_table_t hash_table_create(size_t dimension, hasher_t key_hash, comparator_t key_cmp) {

  hash_table_t hash_table = NULL;
  size_t i = 0;    

  hash_table = malloc(sizeof(struct hash_table_s));
  if ( hash_table == NULL ) {
    perror("Unable to allocate memory for Hash Table");
    abort();
  }

  hash_table->slots = malloc(dimension * sizeof(hash_table_slot_t));
  if ( hash_table->slots == NULL ) {
    perror("Unable to allocate memory for slots of the Hash Table");
    abort();
  }

  for ( i = 0; i < dimension; i++ ) 
    hash_table->slots[i].head = NULL;

  hash_table->capacity = dimension;
  hash_table->size = 0;
  hash_table->key_hash = key_hash;
  hash_table->key_cmp = key_cmp;

  return hash_table;
}

void hash_table_destroy(hash_table_t hash_table) {

  if ( hash_table != NULL ) {

    hash_table_clear(hash_table);
    free(hash_table->slots);
    free(hash_table);
  }
}

void hash_table_clear(hash_table_t hash_table) {

  if ( hash_table != NULL && hash_table->slots != NULL ) {

    size_t i = 0;

    for ( i = 0; i < hash_table->capacity; i++ ) {
      hash_table_list_node_t *list = NULL;
      list = hash_table->slots[i].head;

      while ( list != NULL ) {
        hash_table_list_node_t *node = list;
        list = list->next;

        free(node);
      }

      hash_table->slots[i].head = NULL;
    }

    hash_table->size = 0;
  }
}

unsigned int hash_table_put(hash_table_t hash_table, char *key, unsigned int value) {

  unsigned int current_value = 0;

  if ( hash_table != NULL && hash_table->slots != NULL ) {

    size_t hash = hash_table->key_hash(key, hash_table->capacity);
    hash_table_list_node_t *node = hash_table->slots[hash].head;

    while ( node != NULL && key != node->key ) node = node->next;

    if ( node == NULL ) {
      node = malloc(sizeof(hash_table_list_node_t));
      node->key = key;
      node->value = value;
      node->next = hash_table->slots[hash].head;
      hash_table->slots[hash].head = node;
      hash_table->size++;

      return node->value;
    }
    else {
      node->value++;
      return node->value;
    }

  } 

  return current_value;
}

unsigned int hash_table_get(hash_table_t hash_table, char *key) {

  if ( hash_table != NULL && hash_table->slots != NULL ) {
    size_t hash = hash_table->key_hash(key, hash_table->capacity);
    hash_table_list_node_t *node = hash_table->slots[hash].head;

    while ( node != NULL && key != node->key ) node = node->next;

    if ( node != NULL ) return node->value;
  }

  return 0;
}

int hash_table_contains(hash_table_t hash_table, char *key) {
  return ( hash_table_get(hash_table, key) != 0 ) ? 1 : 0;
}

size_t hash_table_size(hash_table_t hash_table) {
  return (hash_table != NULL && hash_table->slots != NULL) ? hash_table->size : 0;
}

hash_table_key_list_t hash_table_keys(hash_table_t hash_table) {
  
  hash_table_key_list_t list, tail, p;
  list = tail = NULL;

  if ( hash_table != NULL && hash_table->slots != NULL ) {

    size_t index = 0;
    while ( index < hash_table->capacity ) {

      hash_table_list_node_t * node = hash_table->slots[index].head;
      while ( node != NULL ) {
        
        p = malloc(sizeof(hash_table_key_list_node_t));
        p->key = node->key;

        if ( node != NULL ) {
          list = tail = p;
        }
        else {
          tail->next = p;
          tail = p;
        }

        node = node->next;
      }

      index++;
    }
  }

  return list;
}

int str_compare(const void* a, const void* b) {

  const char* aa = a;
  const char* bb = b;

  return strcmp(aa, bb);
}

size_t upo_ht_hash_str(const void* x, size_t h0, size_t a, size_t m) {
    
  const char* s = x;
  size_t h = h0; 

  assert( x != NULL );
  assert( m > 0 );
  assert( h0 < m );

  for (; *s; ++s) h = (a*h + *s) % m;

  return h;
}

size_t upo_ht_hash_str_kr2e(const void* x, size_t m) {
  return upo_ht_hash_str(x, 0U, 31U, m);
}
