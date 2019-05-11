#define _GNU_SOURCE
#if defined(unix) || defined(__unix__) || defined(__unix)
  #define _POSIX_C_SOURCE >= 200809L
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <adt/stack.h>
#include <adt/hash_table.h>
#include <pds/bloom_filter.h>
#include "utility_private.h"

#define NUM_BASE 4
#define KMER_LENGTH_DEFAULT 31
#define READS_LENGTH_DEFAULT 1
#define QUALITY_DEFAULT 50
#define PATH_READS_DEFAULT "data/ngs-reads.fq"

const char base_array[NUM_BASE] = {'A', 'C', 'G', 'T'};

char* substr(const char *string, size_t start, size_t end) {
  
  const char *char_start = &string[start];
  const char *char_end = &string[end];
  
  char *substring = (char *) calloc(2, char_end - char_start + 1);
  memcpy(substring, char_start, char_end - char_start + 1);

  return substring;
} 

char** kmer_append(const char *kmer) {

  int i;
  char **edge = malloc(NUM_BASE * sizeof(char *));

  for ( i = 0; i < NUM_BASE; i++ ) {
    edge[i] = (char *) malloc((strlen(kmer) + 1) * sizeof(char *));
    strcpy(edge[i], kmer);
    *((*(edge + i)) + strlen(kmer)) = base_array[i];
    *((*(edge + i)) + strlen(kmer) + 1) = '\0';
  }

  return edge;
}

char** kmer_prepend(const char *kmer) {

  int i;
  char **edge = malloc(NUM_BASE * sizeof(char *));

  for ( i = 0; i < NUM_BASE; i++ ) {
    edge[i] = malloc((strlen(kmer) + 2) * sizeof(char));
    edge[i][0] = base_array[i];
    strcpy((char *)&edge[i][1], kmer);
  }

  return edge;
}

void help_menu() {
  
  printf("Usage: ./app/main [options] | [settings] <value>\n\n");
  printf("Options:\n");
  printf("  --help\t\toutput usage information\n");
  printf("  --default\t\trun the program using default values\n\n");
  printf("Settings:\n");
  printf("  -q, --quality\t\tthe quality value\n");
  printf("  -r, --reads-length\tthe minimum length for the reads\n");
  printf("  -k, --kmer-length\tthe length for the k-mer\n");
  printf("  -f, --reads-file\tabsolute path of FASTQ file\n\n");
}

char* parse_argument(int argc, char **argv, int *quality, int *kmer_length, int *reads_length) {

  char *path_file = NULL;
  int c, option_index = 0;

  while (1) {

    static struct option long_options[] = {
      {"help",     			no_argument,       0, 'h'},
      {"quality",				required_argument, 0, 'q'},
      {"reads-length",  required_argument, 0, 'r'},
      {"kmer-length",  	required_argument, 0, 'k'},
      {"file-reads",  	required_argument, 0, 'f'},
      {"default",  			no_argument,       0, 'd'},
      {0, 0, 0, 0}
    };

    opterr = 0;
    c = getopt_long(argc, argv, "h:q:r:k:f:d:", long_options, &option_index);
    if ( c == -1 ) break;

    switch ( c ) {
      case 0:
        if (long_options[option_index].flag != 0)
          break;
        printf ("option %s", long_options[option_index].name);
        
        if (optarg)
          printf (" with arg %s", optarg);
        
        printf ("\n");
        break;

      case 'h':
        help_menu();
        exit(EXIT_SUCCESS);
        break;

      case 'q':
        *quality = atoi(optarg);
        break;

      case 'r':
        *reads_length = atoi(optarg);
        break;

      case 'k':
        *kmer_length = atoi(optarg);
        break;

      case 'f':
        path_file = malloc(strlen(optarg) + 1 * sizeof(char));
        if ( path_file == NULL ) {
          fprintf(stderr, "Unable to allocate memory for a string");
          abort();
        }
        strcpy(path_file, optarg);
        break;

      case 'd':
        *quality = QUALITY_DEFAULT;
        *reads_length = READS_LENGTH_DEFAULT;
        *kmer_length = KMER_LENGTH_DEFAULT;
        
        path_file = malloc(strlen(PATH_READS_DEFAULT) + 1 * sizeof(char));
        if ( path_file == NULL ) {
          fprintf(stderr, "Unable to allocate memory for a string");
          abort();
        }
        strcpy(path_file, PATH_READS_DEFAULT);
        break;

      case '?':
        printf("Unknown flag.\nSee usage runnig: %s --help\n", argv[0]);
        exit(EXIT_FAILURE);
        break;

      default:
        exit(EXIT_FAILURE);
    }
  }

  return path_file;
}

int index_from_element(hash_table_key_list_t key_list, char *node) {

  if ( key_list != NULL ) {

    int index = 0;

    while ( key_list != NULL ) {

      if ( !strcmp(key_list->key, node) )  break;

      index++;
      key_list = key_list->next;
    }

    return index;
  }

  return -1;
}

char* element_from_index(hash_table_key_list_t key_list, int index, int dimension) {

  /* if ( key_list != NULL ) { */

    int i = 0;
    char *string = malloc((dimension + 2) * sizeof(char));
    if ( string == NULL ) {
      fprintf(stderr, "Unable to create a string");
      abort();
    }

    while (key_list != NULL ) {
      
      if ( i == index ) {
        /* string = strdup(key_list->key); */
        strcpy(string, key_list->key);
        break;
      }

      i++;
      key_list = key_list->next; 
    }

    return string;
  /* }
  
  return NULL; */
}

int* array_adj(bloom_filter_t bloom_filter, int index, hash_table_key_list_t key_list, size_t dimension) { 
  
  size_t i, j;
  char *sub_kmer = NULL, **edge = NULL, *node = NULL;
  int *array = malloc(NUM_BASE * sizeof(int));
  
  if ( array == NULL ) {
    fprintf(stderr, "Unable to create array");
    abort();
  }
  
  node = element_from_index(key_list, index, dimension);
  sub_kmer = substr(node, 1, strlen(node));
  edge = kmer_append(sub_kmer);
   
  j = 0;
  for ( i = 0; i < NUM_BASE; i++ ) {
    if ( bloom_filter_get(bloom_filter, edge[i]) )
      array[j] = index_from_element(key_list, edge[i]);
    else
      array[j] = -2;
    
    j++;
    free(*(edge + i));
  }

  free(node);
  free(edge);
  free(sub_kmer);

  return array;
}

int out_degree(bloom_filter_t bloom_filter, char *node) {

  if ( bloom_filter != NULL ) {
    
    size_t i;
    int grade = 0;
    char *sub_kmer = NULL, **edge = NULL;

    sub_kmer = substr(node, 1, strlen(node));
    edge = kmer_append(sub_kmer);

    for ( i = 0; i < NUM_BASE; i++ ) {
      if ( bloom_filter_get(bloom_filter, edge[i]) )
        grade++;

      free(*(edge + i));
    }

    free(edge);
    free(sub_kmer);

    return grade;
  }

  return -1;  
}

int in_degree(bloom_filter_t bloom_filter, char *node) {

  if ( bloom_filter != NULL ) {
    
    size_t i;
    int grade = 0;
    char *sub_kmer = NULL, **edge = NULL;

    sub_kmer = substr(node, 0, strlen(node) - 2);
    edge = kmer_prepend(sub_kmer);

    for ( i = 0; i < NUM_BASE; i++ ) {
      if ( bloom_filter_get(bloom_filter, edge[i]) )
        grade++;
      
      free(*(edge + i));
    }

    free(edge);
    free(sub_kmer);

    return grade;
  }

  return -1; 
}

int* all_in_degree(bloom_filter_t bloom_filter, hash_table_key_list_t key_list, size_t dimension) {

  if ( bloom_filter != NULL && key_list != NULL ) {

    size_t i = 0;
    int *array = malloc(dimension * sizeof(int));
    if ( array == NULL ) {
      fprintf(stderr, "Unable to create the array");
      abort();
    }

    while ( key_list != NULL ) {
      array[i] = in_degree(bloom_filter, key_list->key);
      i++;
      key_list = key_list->next;
    }

    return array;
  }

  return NULL;
}

int* all_out_degree(bloom_filter_t bloom_filter, hash_table_key_list_t key_list, size_t dimension) {

  if ( bloom_filter != NULL && key_list != NULL ) {

    size_t i = 0;
    int *array = malloc(dimension * sizeof(int));
    if ( array == NULL ) {
      fprintf(stderr, "Unable to create the array");
      abort();
    }

    while ( key_list != NULL ) {
      array[i] = out_degree(bloom_filter, key_list->key);
      i++;
      key_list = key_list->next;
    }

    return array;
  }

  return NULL;
}

int is_eulerian(bloom_filter_t bloom_filter, hash_table_key_list_t key_list, size_t dimension, int *first_node, int *last_node) {

  if ( bloom_filter != NULL && key_list != NULL ) {
    
    size_t i;
    int eulerian = 1;
    int *array_out_degree = NULL, *array_in_degree = NULL;

    *first_node = -1; 
    *last_node = -1;

    array_out_degree = all_out_degree(bloom_filter, key_list, dimension);
    array_in_degree = all_in_degree(bloom_filter, key_list, dimension);
    
    for ( i = 0; i < dimension && eulerian; i++) {
      if ( array_in_degree[i] == array_out_degree[i] )
        continue;

      if ( (array_in_degree[i] > array_out_degree[i] + 1) || (array_out_degree[i] > array_in_degree[i] + 1) ) 
        eulerian = 0;
      
      if (array_in_degree[i] == array_out_degree[i] + 1) {
        if ( *last_node == -1 ) 
          *last_node = i;
        else 
          eulerian = 0;
      }

      if ( array_out_degree[i] == array_in_degree[i] + 1) {
        if ( *first_node == -1 ) 
          *first_node = i;
        else
          eulerian = 0;
      }
    }

    if(*first_node == -1 && *last_node == -1) {
      *first_node = 0;
      *last_node = 0;
    }

    if (*first_node == -1 || *last_node == -1) 
      eulerian = 0;

    free(array_out_degree);
    free(array_in_degree);

    return eulerian;
  }

  return -1;
}

eulerian_path_t build_path(const int* const first_node, sstack_t *stack) {
  
  int current;
  eulerian_path_t head, new_head;
  
  head = malloc(sizeof(struct eulerian_path_s));
  head->id = *first_node;
  head->next = NULL;

  current = *first_node;

  while ( !stack_is_empty(stack[current]) ) {
    current = stack_pop(stack[current]);

    new_head = malloc(sizeof(struct eulerian_path_s));
    new_head->id = current;
    new_head->next = head;
    head = new_head;
  }
  
  return head;
}


void build_cycle(sstack_t *stack, eulerian_path_t head, int *path) {

  int current;
  size_t i = 0;
  eulerian_path_t new_head = NULL;
    
  while ( head != NULL ) {
    
    current = head->id;
    
    if ( !stack_is_empty(stack[current]) ) {
      new_head = malloc(sizeof(eulerian_path_t));
      new_head->id = stack_pop(stack[current]);
      new_head->next = head;
      head = new_head;
    }
    else {
      head = head->next;
      path[i] = current;
      i++;
    }
  }
}

void reverese_array(int arr[], int start, int end) {

  int temp; 

  while ( start < end ) {
    temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;

    start++;
    end--;
  }    
}

void print_graph(FILE *file, bloom_filter_t bloom_filter, hash_table_key_list_t key_list) {

  size_t i;
  char *sub_kmer = NULL, **edge = NULL;
  
  fprintf(file, "digraph G {\n");

  while ( key_list != NULL ) {
    sub_kmer = substr(key_list->key, 1, strlen(key_list->key));
    edge = kmer_append(sub_kmer);

    for ( i = 0; i < NUM_BASE; i++ ) {
      if ( bloom_filter_get(bloom_filter, edge[i]) ) {
        fprintf(file, "  %s ", key_list->key);
        fprintf(file, "-> ");
        fprintf(file, "%s\n", edge[i]);
      }
      free(*(edge + i));
    }

    free(sub_kmer);
    free(edge);

    key_list = key_list->next;
  }

  fprintf(file, "}");
}

char* genome_recostruction(int *path, hash_table_key_list_t key_list, size_t dimension, int kmer_length) {

  size_t i;
  char* genome = NULL, tmp[50], *element = NULL;

  reverese_array(path, 0, dimension - 1);

  for ( i = 0; i < dimension; ++i ) {
    element = element_from_index(key_list, path[i], kmer_length);

    if ( i == 0 ) genome = element;
    else {
      sprintf(tmp, "%c", element[strlen(element) - 1]);
      genome = realloc(genome, strlen(genome) * sizeof(char) + strlen(tmp) * sizeof(char) + 2);
      genome = strcat(genome, tmp);
    }
  }

  free(element);
  return genome;
}
