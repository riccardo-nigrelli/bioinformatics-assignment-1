#ifndef BLOOM_FILTER_PRIVATE_H
  #define BLOOM_FILTER_PRIVATE_H
  
  #if defined(unix) || defined(__unix__) || defined(__unix)
    #include <stdint.h>
  #endif

  #include <stdio.h>
  #include <pds/bloom_filter.h>

  struct bloom_filter_s {
    uint64_t *bit_vector;
    size_t dimension;
    unsigned int (**hash_function)(char *, unsigned int);
    size_t num_hash_function;
  };

#endif /* BLOOM_FILTER_PRIVATE_H */
