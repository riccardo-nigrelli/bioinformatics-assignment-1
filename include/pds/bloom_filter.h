#ifndef BLOOM_FILTER_H
  
  #define BLOOM_FILTER_H
  
  #include <stddef.h>

  /** \brief Declares the bloom filter type. */
  typedef struct bloom_filter_s* bloom_filter_t;
 
  /**
   * \brief Creates a new bloom filter.
   * \param dimension The dimension of the bit vector. 
   * \param hash_function Array of hash function pointer.
   * \param num_hash_function Number of hash function that you want to use.
   * \return A bloom filter
   */ 
  bloom_filter_t bloom_filter_create(size_t dimension, unsigned int (**hash_function)(char *, unsigned int), int num_hash_function);

  /**
   * \brief Destroys the given bloom filter.
   * \param bloom_filter The bloom filter.
   * \return `1` if the bloom filter is destroyed properly  or `0` otherwise.
   */ 
  int bloom_filter_destroy(bloom_filter_t bloom_filter);

  /**
   * \brief Insert the given evelement the given bloom filter.
   * \param bloom_filter The bloom filter.
   * \param element The element.
   * \return -1 if the bloom filter doesn't exist.
   */ 
  int bloom_filter_add(bloom_filter_t bloom_filter, char *element);

  /**
   * \brief Returns a number that tell if the element if present or not.
   * \param bloom_filter The bloom filter.
   * \param element The element.
   * \return `1` if the element is find, `0` otherwise.
   */ 
  int bloom_filter_get(bloom_filter_t bloom_filter, char *element);

#endif /* BLOOM_FILTER_H */
