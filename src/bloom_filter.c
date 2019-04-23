#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <pds/hash_function.h>
#include "bloom_filter_private.h"

bloom_filter_t bloom_filter_create(int const dimension) {

	if ( dimension >= 0) {

		int i;
		bloom_filter_t bloom_filter = malloc(sizeof(struct bloom_filter_s));

		if ( bloom_filter == NULL) {
			perror("Unable to create a bloom filter");
			abort();
		}

		bloom_filter->bit_vector = NULL;

		if ( dimension > 0 ) {

			bloom_filter->bit_vector = (int *) malloc(dimension * sizeof(int));

			if ( bloom_filter->bit_vector == NULL ) {
				perror("Unable to create a bit vector");
				abort();
			}

			for ( i = 0; i < dimension; i++ ) 
				bloom_filter->bit_vector[i] = 0;
		}

		bloom_filter->dimension = dimension;
		return bloom_filter;
	}
	else return NULL;
}

int bloom_filter_destroy(bloom_filter_t bloom_filter) {

	if ( bloom_filter != NULL) {

		free(bloom_filter->bit_vector);
		free(bloom_filter);

		return 1;	
	}

	return -1;
}

int bloom_filter_add(bloom_filter_t bloom_filter, const char *kmer) {

	if ( bloom_filter != NULL ) {
		size_t index_first_hash; //, index_second_hash;

		index_first_hash = murmurhash2(kmer, strlen(kmer), 0x14570c6f) % bloom_filter->dimension;
		// fibonacci_hash_3_bits(sizeof(kmer)); 
		// djb2(kmer, bloom_filter->dimension);
		// index_second_hash = jenkins(kmer, bloom_filter->dimension);

		if ( bloom_filter->bit_vector[index_first_hash] == 1 ) {
			printf("COLLISIONE del kmer '%s' in posizione %zu\n", kmer, index_first_hash);
			return 0;
		}
		// else if ( bloom_filter->bit_vector[index_second_hash] == 1 ) {
		// 	printf("COLLISIONE in posizione %u\n", index_second_hash);
		// 	return 0;
		// }
		else {
			bloom_filter->bit_vector[index_first_hash] = 1;
			// bloom_filter->bit_vector[index_second_hash] = 1;
			return 1;
		}
	}

	return -1;
}

int bloom_filter_get(bloom_filter_t bloom_filter, const char *kmer) {

	if ( bloom_filter != NULL ) {
		size_t index_first_hash; //, index_second_hash;

		index_first_hash = murmurhash2(kmer, strlen(kmer), 0x9747b28c) % bloom_filter->dimension;
		// fibonacci_hash_3_bits(sizeof(kmer)); 
		// djb2(kmer, bloom_filter->dimension);
		// index_second_hash = jenkins(kmer, bloom_filter->dimension);

		if ( bloom_filter->bit_vector[index_first_hash] == 1 ) // && bloom_filter->bit_vector[index_second_hash] == 1
			return index_first_hash;
		else 
			return 0;
	}

	return -1;
}

int bloom_filter_get_element(bloom_filter_t bloom_filter, int index) {
	return (bloom_filter != NULL) ? bloom_filter->bit_vector[index] : -1;
}
