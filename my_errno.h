/*
 * mn_errno.h
 *
 *  Created on: 21.12.2012
 *      Author: Roland
 */

#ifndef MN_ERRNO_H_
#define MN_ERRNO_H_

#define MY_ERROR_OUTPUT stderr

__BEGIN_DECLS

/**
 * @brief Print readable error
 * @param error Value of the error code
 * @return void No return value
 *
 * Function prints a readable error of a given error code.
 * Uses the stderr standard I/O stream
 */
void print_error_code(int error);

__END_DECLS

#endif /* MN_ERRNO_H_ */
