#ifndef HASH_FUNCTION_H

	#define HASH_FUNCTION_H

	#include <stdio.h>
	
	unsigned int murmurhash2(const void * key, int len, const unsigned int seed);
	
#endif /* HASH_FUNCTION_H */
