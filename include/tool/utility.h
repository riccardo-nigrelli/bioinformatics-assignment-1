#ifndef UTILITY_H
  
  #define UTILITY_H

  #include <stdio.h>
  #include <stddef.h>
  #include <adt/hash_table.h>
  #include <pds/bloom_filter.h>

  typedef struct eulerian_path_s eulerian_path_t;
  /* typedef struct eulerian_path_s* eulerian_path_t; */

  char* substr(const char *string, size_t start, size_t end);
  char** kmer_append(const char *kmer);
  char** kmer_prepend(const char *kmer);
  void help_menu();
  char* parse_argument(int argc, char **argv, int *quality, int *kmer_length, int *reads_length);
  int* array_adj(bloom_filter_t bloom_filter, int index, hash_table_key_list_t key_list, size_t dimension);
  int index_from_element(hash_table_key_list_t key_list, char *node);
  char* element_from_index(hash_table_key_list_t key_list, int index, int dimension);
  int out_degree(bloom_filter_t bloom_filter, char *node);
  int in_degree(bloom_filter_t bloom_filter, char *node);
  int* all_in_degree(bloom_filter_t bloom_filter, hash_table_key_list_t key_list, size_t dimension);
  int* all_out_degree(bloom_filter_t bloom_filter, hash_table_key_list_t key_list, size_t dimension);
  int is_eulerian(bloom_filter_t bloom_filter, hash_table_key_list_t key_list, size_t dimension, int *first_node, int *last_node);
  eulerian_path_t* build_path(const int* const first_node, sstack_t *stack);
  void build_cycle(sstack_t *stack, eulerian_path_t* head, int *path);
  void print_graph(FILE *file, bloom_filter_t bloom_filter, hash_table_key_list_t key_list);
  char* genome_recostruction(int *path, hash_table_key_list_t key_list, size_t dimension, int kmer_length);
  
#endif /* UTILITY_H */
