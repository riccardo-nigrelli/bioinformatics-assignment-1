#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

typedef struct bloom_filter_s* bloom_filter_t;

bloom_filter_t bloom_filter_create(int const dimension);

int bloom_filter_destroy(bloom_filter_t bloom_filter);

int bloom_filter_get_element(bloom_filter_t bloom_filter, int index);

#endif /* BLOOM_FILTER_H */
