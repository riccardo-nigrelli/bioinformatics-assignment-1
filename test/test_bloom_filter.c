#include <error.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <pds/bloom_filter.h>

#define BIT_VECTOR_DEFAUL_CAPACITY 10

static void test_create_destroy();
static void test_null();

void test_create_destroy() {
	
	bloom_filter_t bloom_filter = NULL;

	bloom_filter = bloom_filter_create(BIT_VECTOR_DEFAUL_CAPACITY);
	assert( bloom_filter != NULL );

	assert( bloom_filter_destroy(bloom_filter) == 1 );

	bloom_filter = bloom_filter_create(BIT_VECTOR_DEFAUL_CAPACITY);
	bloom_filter_destroy(bloom_filter);

	bloom_filter = bloom_filter_create(-1);
	assert( bloom_filter == NULL );
}

void test_null() {

	bloom_filter_t bloom_filter = NULL;
	assert( bloom_filter_destroy(bloom_filter) == -1);
}

int main(void) {

	printf("Test case 'create/destroy' ... ");
	fflush(stdout);
	test_create_destroy();
	printf("OK\n");

	printf("Test case 'null' ... ");
	fflush(stdout);
	test_null();
	printf("OK\n");

	return 0;
}
