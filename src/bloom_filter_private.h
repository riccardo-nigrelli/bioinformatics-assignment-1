#ifndef BLOOM_FILTER_PRIVATE_H
#define BLOOM_FILTER_PRIVATE_H

#include <pds/bloom_filter.h>

struct bloom_filter_s {
	int *bit_vector;
	int dimension;
};

#endif /* BLOOM_FILTER_PRIVATE_H */
