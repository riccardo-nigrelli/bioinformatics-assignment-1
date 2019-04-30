#ifndef BLOOM_FILTER_H
  #define BLOOM_FILTER_H

  typedef struct bloom_filter_s* bloom_filter_t;
  
  /**
   * @brief 
   * @param 
   * @param 
   * @param 
   * @return 
   */ 
  bloom_filter_t bloom_filter_create(size_t dimension, unsigned int (**hash_function)(char *, unsigned int), int num_hash_function);

  /**
   * @brief 
   * @param 
   * @return 
   */ 
  int bloom_filter_destroy(bloom_filter_t bloom_filter);

  /**
   * @brief 
   * @param 
   * @param 
   * @return 
   */ 
  int bloom_filter_add(bloom_filter_t bloom_filter, char *element);

  /**
   * @brief 
   * @param 
   * @param 
   * @return 
   */ 
  int bloom_filter_get(bloom_filter_t bloom_filter, char *element);

#endif /* BLOOM_FILTER_H */
