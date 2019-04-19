#include <stdio.h>
#include <stdlib.h>
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

int bloom_filter_get_element(bloom_filter_t bloom_filter, int index) {
	return (bloom_filter != NULL) ? bloom_filter->bit_vector[index] : -1;
}
