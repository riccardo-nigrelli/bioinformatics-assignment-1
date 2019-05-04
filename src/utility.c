#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define NUM_BASE 4
#define KMER_LENGTH_DEFAULT 31
#define READS_LENGTH_DEFAULT 1
#define QUALITY_DEFAULT 50
#define PATH_READS_DEFAULT "data/ngs-reads.fq"

const char base_array[NUM_BASE] = {'A', 'C', 'G', 'T'};

char* substr(const char *string, size_t start, size_t end) {
  
  const char *char_start = &string[start];
  const char *char_end = &string[end];
  
  char *substring = (char *) calloc(1, char_end - char_start + 1);
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

static char *concatenate_char_str(char prefix, const char *str) { 
  
  char *ret = malloc(1 + strlen(str) + 1); 
  ret[0] = prefix; 
  strcpy(ret + 1, str); 
  
  return ret; 
}

char** kmer_prepend(const char *kmer) {

  int i;
  char **edge = malloc(NUM_BASE * sizeof(char *));

  for ( i = 0; i < NUM_BASE; i++ ) {
    edge[i] = malloc((strlen(kmer) + 1) * sizeof(char *));
    edge[i] = concatenate_char_str(base_array[i], kmer);
  }

  return edge;
}

/* Function for check if the graph is correct */
int find_element(char **array, char *string, int num_element) {

  int i, flag = 0;

  for ( i = 0; i < num_element; i++ ) {
    if (!strcmp(array[i], string)){
      flag = 1;
      break;
    }
  }

  return flag;
}

void help_menu() {
  
  printf("Usage: ./app/main [options] | [settings] <value>\n\n");
  printf("Options:\n");
  printf("  --help\t\toutput usage information\n");
  printf("  --default\t\trun the program using default values\n\n");
  printf("Settings:\n");
  printf("  -q, --quality\t\tthe quality value\n");
  printf("  -r, --reads-length\tthe minimum length for the reads\n");
  printf("  -k, --kmer-length\tthe length for the k-mer\n\n");
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
          perror("Unable to allocate memory for a string");
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
          perror("Unable to allocate memory for a string");
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
