/*
 * my_errno.c
 *
 *  Created on: 21.12.2012
 *      Author: Roland
 */

#include "headers.h"

void print_error_code(int error) {

	fprintf(stderr, "error: Error code: %d\n", error);
	switch(error) {

		case ENOSPC:
			fprintf(MY_ERROR_OUTPUT, "error: Resource has been exhausted, or the limit has been reached.\n");
			break;

		case EPERM:
			fprintf(MY_ERROR_OUTPUT, "error: Permission failure.\n");
			break;

		case EFAULT:
			fprintf(MY_ERROR_OUTPUT, "error: Outside the accessible address space.\n");
			break;

		case EINTR:
			fprintf(MY_ERROR_OUTPUT, "error: Was interrupted by a signal handler.\n");
			break;

		case EINVAL:
			fprintf(MY_ERROR_OUTPUT, "error: Parameter is not a valid.\n");
			break;

		case EAGAIN:
			fprintf(MY_ERROR_OUTPUT, "error: Operation performed without blocking.\n");
			break;

		case ENOSYS:
			fprintf(MY_ERROR_OUTPUT, "error: Function is not supported by this implementation.\n");
			break;

		case ENOTSUP:
			fprintf(MY_ERROR_OUTPUT, "error: Function is not supported.\n");
			break;

		case EBUSY:
			fprintf(MY_ERROR_OUTPUT, "error: Current processes are blocking.\n");
			break;

		default:
			fprintf(MY_ERROR_OUTPUT, "error: Unknown errno code.\n");
			break;
	}

}


