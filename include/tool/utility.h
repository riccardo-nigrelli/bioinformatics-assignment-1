#ifndef UTILITY_H
  
  #define UTILITY_H

  #include <stdio.h>
  #include <stddef.h>
  #include <adt/hash_table.h>
  #include <pds/bloom_filter.h>

  /** 
   * \brief The type for nodes of list of node for the eulerian path. 
   */
  struct eulerian_path_s {
    int id; /**< position of the element in the key list. */
    struct eulerian_path_s *next; /**< Pointer to the next node in the list. */
  };
  
  /** \brief The type for list of node in the eulerian path. */
  typedef struct eulerian_path_s *eulerian_path_t;

  /** \brief Print the help menu. */
  void help_menu();

  /**
   * \brief Get the value of all flag for a correct usage. 
   * \param argc The number of parameters.
   * \param argv The arrat of string that contain all flag and value.
   * \param quality The reads quality.
   * \param kmer_length The kmer length.
   * \param reads_length The reads length.
   * \return The path of input file that contains.
   */ 
  char* parse_argument(int argc, char **argv, int *quality, int *kmer_length, int *reads_length);

  /**
   * \brief Return the list of adjacent nodo to the given node index.
   * \param bloom_filter The bloom filter.
   * \param index The node index.
   * \param key_list The key list.
   * \retunr The list of adjancent node.
   */ 
  int* array_adj(bloom_filter_t bloom_filter, int index, hash_table_key_list_t key_list);

  /**
   * \brief Check if the given graph rapresent using the bloom filter is eulerian.
   * \param bloom_filter The bloom filter.
   * \param key_list The key list.
   * \param dimension The dimension.
   * \param first_node The first node of the graph.
   * \param last_node The last node of the graph.
   * \return `1` if the graph is eulerian, `0` in the graph is not euleria, `-1` if the bloom filter
   *         or the key list is `NULL` 
   */ 
  int is_eulerian(bloom_filter_t bloom_filter, hash_table_key_list_t key_list, size_t dimension, int *first_node, int *last_node);
  
  /**
   * \brief Build the path from the fist node to the last
   * \param first_node The first node
   * \param stack The array of stack
   * \return A pointer to the list that is stored reversely
   */ 
  eulerian_path_t build_path(const int* const first_node, sstack_t *stack);
  
  /**
   * \brief Build the eulerian cycle
   * \param stack The array of stack
   * \param head The head of the eulerian path
   * \param path The variable where store the eulerian path 
   */ 
  void build_cycle(sstack_t *stack, eulerian_path_t head, int *path);

  /**
   * \brief Write on file the rapresentation of the graph `node -> node1`.
   * \param file The file where write.
   * \param bloom_filter The bloom filter.
   * \param key_list The key list.
   */ 
  void print_graph(FILE *file, bloom_filter_t bloom_filter, hash_table_key_list_t key_list);

  /**
   * \brief Return the string of the genome recostruction. 
   * \param path The path of the eulerian path
   * \param key_list The key list
   * \param dimension The dimension
   * \retunr the string of the genome, `NULL` if the bloom filter or the key list is `NULL` 
   */ 
  char* genome_recostruction(int *path, hash_table_key_list_t key_list, size_t dimension);

#endif /* UTILITY_H */
