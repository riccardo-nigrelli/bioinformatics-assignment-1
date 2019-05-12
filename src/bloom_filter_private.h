#ifndef BLOOM_FILTER_PRIVATE_H
  #define BLOOM_FILTER_PRIVATE_H
  
  #if defined(unix) || defined(__unix__) || defined(__unix)
    #include <stdint.h>
  #endif

  #include <stdio.h>
  #include <pds/bloom_filter.h>

  /** \brief Defines the structure of the bloom filter. */
  struct bloom_filter_s {
    uint64_t *bit_vector; /**< The bit vector. */
    size_t dimension; /**< The dimension of the bit vector. */
    unsigned int (**hash_function)(char *, unsigned int); /**< The array of hash function pointer. */
    size_t num_hash_function; /**< The number of hash function that you want to use */
  };

#endif /* BLOOM_FILTER_PRIVATE_H */
