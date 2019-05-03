#ifndef UTILITY_H
  
  #define UTILITY_H

  #include <stdio.h>

  /**
   * @brief 
   * @param 
   * @param 
   * @param 
   * @return 
   */ 
  char* substr(const char *string, size_t start, size_t end);
  
  char** kmer_append(const char *kmer, const char *base);

  int find_element(char **array, char *string, int num_element);
  
  char** kmer_prepend(const char *kmer, const char *base);

  /**
   * @brief 
   */ 
  void help_menu();
  
  char* parse_argument(int argc, char **argv, int *quality, int *kmer_length, int *reads_length);

#endif /* UTILITY_H */
