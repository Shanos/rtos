/*
 * debug.h
 *
 *  Created on: 05.12.2012
 *      Author: roland
 */

#ifndef DEBUG_H_
#define DEBUG_H_

// Debugging definition
#define DEBUGGING_HIGH			2			// Debug output more verbose enabled
#define DEBUGGING				1			// Debug output enabled
#define DEBUGGING_DISABLED		0			// Debug output disabled

// Debugging level
#define DEBUG_LEVEL		DEBUGGING_DISABLED

// Debug output
#define DEBUG_OUTPUT	stdout				// Standard output

// Debugging
#if (DEBUG_LEVEL > DEBUGGING_DISABLED)
#define DEBUG
#define dbg(...)  { (void) fprintf(DEBUG_OUTPUT, __VA_ARGS__); }
#else
#undef DEBUG
#define dbg(...)  ((void) 0)
#endif

// Debugging high
#if (DEBUG_LEVEL > DEBUGGING)
#define DEBUG_HIGH
#define dbg_h(...)  { (void) fprintf(DEBUG_OUTPUT, __VA_ARGS__); }
#else
#undef DEBUG_HIGH
#define dbg_h(...)  ((void) 0)
#endif

#endif /* DEBUG_H_ */
