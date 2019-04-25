#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 4

char* substr(const char *string, size_t start, size_t end) {
	
  const char *char_start = &string[start];
  const char *char_end = &string[end];
  
  char *substr = (char *) calloc(1, char_end - char_start + 1);
  memcpy(substr, char_start, char_end - char_start + 1);

	return substr;
} 

char** kmer_concat(const char *kmer, const char *base) {

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
