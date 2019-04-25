#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bloom_filter_private.h"

#if defined(unix) || defined(__unix__) || defined(__unix)
	#include <stdint.h>
#endif

#define BITS_PER_UINT64_T 64

bloom_filter_t bloom_filter_create(size_t dimension, unsigned int (**hash_function)(char *, unsigned int), int num_hash_function) {
	if ( dimension >= 0 ) {

		size_t i;
		bloom_filter_t bloom_filter = malloc(sizeof(struct bloom_filter_s));
		if ( bloom_filter == NULL ) {
			perror("Unable to create a bloom filter");
			abort();
		}

    bloom_filter->bit_vector = NULL;

    if ( dimension > 0 ) {
      
      bloom_filter->bit_vector = (uint64_t *) malloc(dimension * sizeof(uint64_t));
      if ( bloom_filter->bit_vector == NULL ) {
				perror("Unable to create a bit vector");
				abort();
      }

      for ( i = 0; i < dimension; i++ ) bloom_filter->bit_vector[i] = 0;
    }

    bloom_filter->dimension = dimension;
    bloom_filter->hash_function = hash_function;
    bloom_filter->num_hash_function = num_hash_function;

    return bloom_filter;
	}
	else return NULL;
}

int bloom_filter_destroy(bloom_filter_t bloom_filter) {
  
  if ( bloom_filter != NULL ) {

    free(bloom_filter->bit_vector);
    free(bloom_filter);
    return 1;
  }

  return -1;
}

static void write_bit_impl(uint64_t* word, size_t bit_index) {
  *word |= ((uint64_t) 1) << bit_index;
}

static void write_bit(uint64_t* array, size_t bit_index) {

  size_t word_index = bit_index / BITS_PER_UINT64_T;
  uint64_t* integer = &array[word_index];
  write_bit_impl(integer, bit_index % BITS_PER_UINT64_T);
}

static int read_bit_impl(uint64_t* word, size_t bit_index) {
  
  size_t i;
  uint64_t integer = 1;

  for (i = 0; i != bit_index; ++i)
    integer <<= 1;

  return ((*word & integer) != 0) ? 1 : 0;
}

int bloom_filter_add(bloom_filter_t bloom_filter, char *element) {

  if ( bloom_filter != NULL ) {

    size_t i, index, total;

    total = bloom_filter->dimension * BITS_PER_UINT64_T;

    for ( i = 0; i != bloom_filter->num_hash_function ; i++ ) {
      index = bloom_filter->hash_function[i](element, strlen(element)) % total;
      write_bit(bloom_filter->bit_vector, index);
    }
  }

  return -1;
}

static int read_bit(uint64_t* array, size_t bit_index) {

  size_t word_index = bit_index / BITS_PER_UINT64_T;
  uint64_t* integer = &array[word_index];
  return read_bit_impl(integer, bit_index % BITS_PER_UINT64_T);
}

int bloom_filter_get(bloom_filter_t bloom_filter, char* element) {

  if ( bloom_filter != NULL ) {
    size_t i, index, total;
    
    total = bloom_filter->dimension * BITS_PER_UINT64_T;

    for ( i = 0; i != bloom_filter->num_hash_function; ++i ) {
      index = bloom_filter->hash_function[i](element, strlen(element)) % total;
      
      if ( !read_bit(bloom_filter->bit_vector, index) ) return 0;
    }

    return 1;
  }
  
  return -1;
}
