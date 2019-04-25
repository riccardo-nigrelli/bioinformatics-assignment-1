#ifndef UTILITY_H
	
	#define UTILITY_H

	#include <stdio.h>

	char* substr(const char *string, size_t start, size_t end);
	char** kmer_concat(const char *kmer, const char *base);
	int find_element(char **array, char *string, int num_element);

#endif
