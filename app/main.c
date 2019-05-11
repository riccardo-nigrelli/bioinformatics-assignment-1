#define _GNU_SOURCE
#if defined(unix) || defined(__unix__) || defined(__unix)
  #define _POSIX_C_SOURCE >= 200809L
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <adt/stack.h>
#include <tool/memory.h>
#include <tool/utility.h>
#include <adt/hash_table.h>
#include <pds/bloom_filter.h>
#include <pds/hash_function.h>
#include <time.h>

#if defined(unix) || defined(__unix__) || defined(__unix)
  #include <sys/types.h>
#endif

#define NUM_BASE 4

void destroy_key_list(hash_table_key_list_t key_list) {

  hash_table_key_list_node_t *current = NULL;

  if ( key_list == NULL ) return;

  while ( key_list != NULL ) {
    current = key_list; 
    key_list = key_list->next; 
    free(current->key);
    free(current);      
  }

  key_list = NULL;
}

unsigned int (*hash_function[])(char *, unsigned int) = {
  RSHash, JSHash, PJWHash, ELFHash, BKDRHash, SDBMHash, DJBHash, DEKHash, BPHash, FNVHash, APHash	
};

int main(int argc, char **argv) {
  
  FILE *file;
  ssize_t read;
  size_t i, j, len = 0, memory_start = 0, memory_end = 0;
  int *adj = NULL, *path = NULL, cnt = 0;
  int quality, kmer_length, reads_length, eulerian, first = 0, last = 0;
  char *line = NULL, *path_file = NULL, *genome = NULL, command[512], buffer[256];
  clock_t begin, end;

  sstack_t *stack = NULL;
  eulerian_path_t *head = NULL;
  hash_table_t hash_table = NULL;
  bloom_filter_t bloom_filter = NULL;
  hash_table_key_list_t key_list = NULL; 
  
  if (argc == 1) {
    printf("See usage runnig: %s --help\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  memory_start = getCurrentRSS();
  begin = clock();

  path_file = parse_argument(argc, argv, &quality, &kmer_length, &reads_length);

  system("clear");
  
  printf("Cleaning reads with quality %d ... ", quality);

  strcpy(command, "python3 src/prepros/reads_cleaner.py ");
  sprintf(buffer, "%d %d %s", quality, reads_length, path_file);
  strcat(command, buffer);

  system(command);

  printf("OK\n"); 

  strcpy(command, "python3 src/prepros/kmer_extrapolator.py ");
  sprintf(buffer, "%d", kmer_length);
  strcat(command, buffer); 

  if ( system(command) != 0 ) exit(EXIT_FAILURE);
  printf("Generating all %d-mer from the reads... ", kmer_length);  
  printf("OK\n");

  file = fopen("out/kmer.txt", "r");
  if ( file == NULL ) {
    perror("File not found!\n");
    exit(EXIT_FAILURE);
  }

  hash_table = hash_table_create(HASH_TABLE_CAPACITY, hash_table_str_kr2e, str_compare);

  printf("Inserting the %d-mer in Hash Table... ", kmer_length);

  while ( (read = getline(&line, &len, file)) != -1 ) {
    *(line + strlen(line) - 1) = '\0';
    hash_table_put(hash_table, line, 1);
  }

  fclose(file);

  printf("OK\n");
  printf("Hash Table filled correctly, final size: %lu\n", hash_table_size(hash_table)); 
   
  printf("Remove all %d-mer with value equal to one... ", kmer_length);
/*  
  key_list = hash_table_keys(hash_table);
  while ( key_list != NULL ) {
    if ( hash_table_get(hash_table, key_list->key) == 1) {
      hash_table_delete(hash_table, key_list->key);
    }
    key_list = key_list->next;
  } */
 
  printf("OK\n");
  printf("Hash Table size after removing of %d-mer with value one: %lu\n", kmer_length, hash_table_size(hash_table));

  printf("Creation of the De Bruijn Graph via Bloom Filter... ");

  bloom_filter = bloom_filter_create(120, hash_function, 11);
  key_list = hash_table_keys(hash_table);
  
  while ( key_list != NULL ) {
    bloom_filter_add(bloom_filter, key_list->key);
    key_list = key_list->next;
  }

  printf("OK\n");

  key_list = hash_table_keys(hash_table);
  eulerian = is_eulerian(bloom_filter, key_list, hash_table_size(hash_table), &first, &last);

  if ( eulerian ) {
    
    printf("Printing the resulting graph... ");

    file = fopen("out/graph.dot", "w");
    if ( file == NULL ) {
      fprintf(stderr, "Error opening file");
      abort();
    }

    print_graph(file, bloom_filter, key_list);
    
    fclose(file);
    printf("OK\n");
    /*
    system("dot -Tpdf out/graph.dot > out/graph.pdf");
    #if defined(__APPLE__) || defined(__MACH__)
      system("open out/graph.pdf");
    #elif defined(unix) || defined(__unix__) || defined(__unix)
      system("xdg-open out/graph.pdf");
    #endif */
  
    stack = malloc(hash_table_size(hash_table) * sizeof(sstack_t *));
    if ( stack == NULL ) {
      fprintf(stderr, "Unable to create a stack");
      abort();
    }

    for ( i = 0; i < hash_table_size(hash_table); ++i ) {
      stack[i] = stack_create();
      adj = array_adj(bloom_filter, i, key_list, hash_table_size(hash_table));
      
      for (j = 0; j < NUM_BASE; ++j ) {
        if ( adj[j] != -2 )
          stack_push(stack[i], adj[j]);
      }
      
      free(adj);
    }
    
    head = build_path(&first, stack);
    /*
    path = malloc(hash_table_size(hash_table) * sizeof(int));
    if ( path == NULL ) {
      fprintf(stderr, "Unable to allocate an array");
      abort();
    }

    build_cycle(stack, head, path);

    printf("\nGenome reconstruction:\n");
    genome = genome_recostruction(path, key_list, hash_table_size(hash_table), kmer_length);
    
    i = 0;
    while ( genome[i] != '\0' ) {
      printf("%c", genome[i]);
      ++cnt;

      if ( cnt % 60 == 0) printf("\n");

      i++;
    } */

    for ( i = 0; i < hash_table_size(hash_table); i++ )
      stack_destroy(stack[i]);
    free(stack);

    memory_end = getCurrentRSS();
    end = clock();
    
    printf("\n\n============================================================\n");
    printf("Time elapse for computing the genome: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("Total memory used for computing the genoma is: ~%.2f KB\n", (double)((memory_end - memory_start) / 1024));

    free(path);
    free(line);
    free(head);
    free(path_file);
    destroy_key_list(key_list);
    hash_table_destroy(hash_table);
    bloom_filter_destroy(bloom_filter);
  }
  else {
    fprintf(stderr, "ERROR: The graph is not eulerian");

    free(path);
    free(line);
    free(path_file);
    destroy_key_list(key_list);
    hash_table_destroy(hash_table);
    bloom_filter_destroy(bloom_filter);

    exit(EXIT_FAILURE);
  }

  return 0; 
}
