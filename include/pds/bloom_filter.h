#ifndef BLOOM_FILTER_H

	#define BLOOM_FILTER_H	

	typedef struct bloom_filter_s* bloom_filter_t;

	bloom_filter_t bloom_filter_create(const int dimension);

	int bloom_filter_destroy(bloom_filter_t bloom_filter);

	int bloom_filter_add(bloom_filter_t bloom_filter, const char *kmer);

	/**
	 * @brief Check if an element is just in the bloom filter
	 * @param A bloom filter
	 * @param The kmer to search
	 * @retunr -1 if the bloom filter is not allocated, 1 if the kmer is present and 0 if the kmer is not present
	 */
	int bloom_filter_get(bloom_filter_t bloom_filter, const char *kmer);

	int bloom_filter_get_element(bloom_filter_t bloom_filter, int index);

#endif /* BLOOM_FILTER_H */
