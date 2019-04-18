#ifndef ERROR_H
#define ERROR_H


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * \brief Prints the given message to the standard error and abort the program.
 *
 * \param msg The error message
 */
#define throw_error(msg) {\
							assert(msg);\
							fprintf(stderr, "[file: %s, line: %d] %s\n", __FILE__, __LINE__, msg);\
							abort();\
                         }

/**
 * \brief Prints the error message obtained from the current value of the errno
 *  variable, together with the additional given message, to the standard error
 *  and abort the program.
 *
 * \param msg The additional error message
 */
#define throw_sys_error(msg) {\
								const char* errstr = strerror(errno);\
								assert(msg);\
								assert(errstr);\
								fprintf(stderr, "[file: %s, line: %d] %s (%s)\n", __FILE__, __LINE__, msg, errstr);\
								abort();\
							 }


#endif /* ERROR_H */
