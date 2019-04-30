#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 4

char* substr(const char *string, size_t start, size_t end) {
	
  const char *char_start = &string[start];
  const char *char_end = &string[end];
  
  char *substring = (char *) calloc(1, char_end - char_start + 1);
  memcpy(substring, char_start, char_end - char_start + 1);

	return substring;
} 

char** kmer_append(const char *kmer, const char *base) {

	int i;
	char **edge = malloc(BASE * sizeof(char *));

	for ( i = 0; i < BASE; i++ ) {
		edge[i] = (char *) malloc((strlen(kmer) + 1) * sizeof(char *));
		strcpy(edge[i], kmer);
		*((*(edge + i)) + strlen(kmer)) = base[i];
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

char** kmer_prepend(const char *kmer, const char *base) {

	int i;
	char **edge = malloc(BASE * sizeof(char *));

	for ( i = 0; i < BASE; i++ ) {
		edge[i] = malloc((strlen(kmer) + 1) * sizeof(char *));
		edge[i] = concatenate_char_str(base[i], kmer);
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
