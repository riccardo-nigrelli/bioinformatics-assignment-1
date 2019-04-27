#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tool/utility.h>
#include <pds/bloom_filter.h>
#include <pds/hash_function.h>

#if defined(__APPLE__) || defined(__MACH__)
	#include <Python/Python.h>
#elif defined(unix) || defined(__unix__) || defined(__unix)
	#include <Python.h>
	#include <stdint.h>
#endif

#define NUM_BASE 4

int main(int argc, char **argv) {

	// if ( argc > 1 ) {

	// 	if ( !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help") ) {

	// 		printf("Usage: ./app/main [options] [settings]=[value]\n\n");
	// 		printf("Options:\n");
	// 		printf("  -h, --help\toutput usage information\n\n");
	// 		printf("Settings:\n");
	// 		printf("  -q, --quality\toutput usage information\n");
	// 		printf("  -l, --length\toutput usage information\n");
	// 	}
	// 	else {

	// 		printf("DIO SE FUNZIONA\n");

	// 	}
	// }
	// else {
	// 	printf("See usage runnig: %s --help\n", argv[0]);
	// 	exit(1);
	// }
	char line[256];
	FILE *file;
	PyObject *string_module, *module, *function, *result;

	Py_SetProgramName(argv[0]);
	Py_Initialize();
	
	string_module = PyUnicode_FromString((char *) "kmer_counter");
	module = PyImport_Import(string_module);
	function = PyObject_GetAttrString(module, (char *) "counter");
	result = PyObject_CallFunction(function, "i", atoi(argv[1]));

	if ( !result ) {
		fprintf(stderr, "Exception:\n");
		PyErr_PrintEx(0);
		exit(1);
	}
	
	Py_Finalize();

	file = fopen("out/kmer.txt", "r");
	if ( file != NULL ) {
		while ( fgets(line, sizeof(line), file) )	{
			printf("%s", line);
			break;
		}
	}
	else {
		fprintf(stderr, "Unable to open the specified file.\n");
		exit(1);
	}
	


	//if ( argc > 1 ) {

		// char *kmer_length = argv[1];
		// const char *char_to_append[2] = { " ", kmer_length };

		// char *command = "python src/prepros/kmer_counter.py ";
		// strcat(command, kmer_length);

		// printf("%s\n", command);

		// Py_SetProgramName(argv[0]);
    // Py_Initialize();

		// PyObject* myModuleString = PyString_FromString((char *) "../src/prepros/kmer_counter.py");
    // PyObject* myModule = PyImport_Import(myModuleString);
    // PyObject* myFunction = PyObject_GetAttrString(myModule, (char *) "counter");

		// PyObject_Print(myModule, stdout, 0);

    // PyObject *args = PyLong_FromLong(5); // atoi(argv[1])
    // PyObject *myResult = PyObject_CallFunctionObjArgs(myFunction, args, NULL);

		// if (myResult) { 
		// 	fputs("result: ", stderr); 
		// 	PyObject_Print(myResult, stderr, 0); 
		// 	putc('\n', stderr); 
		// }
		// else { 
		// 	fputs("exception:\n", stderr);
		// 	PyErr_PrintEx(0);
		// }

		// Py_Finalize();
		
	//}
	
	// ------------------------------------------------ 

	// size_t i, j, status;
	// char *tmp, **edge;
	// FILE *file;

	// size_t i;

	// unsigned int (*hash_function[])(char *, unsigned int) = {
	// 	RSHash,
	// 	JSHash,
	// 	PJWHash,
	// 	ELFHash,
	// 	BKDRHash,
	// 	SDBMHash,
	// 	DJBHash,
	// 	DEKHash,
	// 	BPHash,
	// 	FNVHash,
	// 	APHash	
	// };

	// const char base_array[NUM_BASE] = {'A', 'C', 'G', 'T'};
	// char *kmer_array[10] = {"GTGAA", "ACGGT", "AACGG", "AGTGA", "TGAAC", "CAGTG", "ACCAG", "CGGTA", "GAACG", "CCAGT"};

	// bloom_filter_t bloom_filter = bloom_filter_create(173, hash_function, 11);

	// for ( i = 0; i < 10; i++ ) bloom_filter_add(bloom_filter, kmer_array[i]);

	// for ( i = 0; i < 10; i++ ) {
	// 	tmp = substr(kmer_array[i], 1, strlen(kmer_array[i]));
	// 	edge = kmer_concat(tmp, base_array);
	// }

	// file = fopen("out/tmp.dot", "w");
	// if ( file == NULL ) {
	// 	perror("Error opening file!\n");
	// 	exit(1);
	// }

	// fprintf(file, "digraph G {\n");

	// printf("\n==============================\n");
	// for( i = 0; i < 10; i++ ) {
		
	// 	printf("Kmer considerato: %s\n", kmer_array[i]);
	// 	tmp = substr(kmer_array[i], 1, strlen(kmer_array[i]));
	// 	printf("Sotto Kmer: %s\n", tmp);
	// 	edge = kmer_concat(tmp, base_array);

	// 	for ( j = 0; j < NUM_BASE; j++ ) {

	// 		printf("Possibile arco: %s; ", edge[j]);
	// 		// if (find_element(kmer_array, edge[j], 10)) {
	// 			status = bloom_filter_get(bloom_filter, edge[j]);
	// 			printf("Status: %zu\n", status);
	// 			if ( status ) {
	// 				fprintf(file, "  %s ", kmer_array[i]);
	// 				fprintf(file, "  -> ");
	// 				fprintf(file, "  %s;\n", edge[j]);
	// 			}
	// 		// }
	// 		else continue;
	// 	}

	// 	printf("\n==============================\n");
	// 	edge = NULL;
	// }

	// fprintf(file, "}");
	// fclose(file);


	// for ( i = 0; i < 10; i++ )
	// 	printf("%s: %d\n", kmer_array[i], bloom_filter_get(bloom_filter, kmer_array[i]));

	// free(edge);
	// free(tmp);
	// bloom_filter_destroy(bloom_filter);

	return 0; 
}
