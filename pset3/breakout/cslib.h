/*
 * File: cslib.h
 * -------------
 * This interface defines a basic set of definitions that are shared among
 * all interfaces in the package.  These basic definitions include:
 *
 *
 *  Declarations for several new primitive types used
 *      throughout the libraries as fundamental types.
 *
 *  A function for error handling.
 *
 *  A flexible set of functions for memory allocation.
 *
 */

#ifndef _cslib_h
#define _cslib_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/* Section 1 -- Define new "primitive" types */

/*
 * Type: bool
 * ----------
 * This type defines the space of Boolean data using the constants false
 * and true.
 */

#ifdef bool
#  undef bool
#endif

#ifdef false
#  undef false
#endif

#ifdef true
#  undef true
#endif

typedef enum {false, true} bool;

/*
 * Type: string
 * ------------
 * This type is defined to be identical with char *.
 */

typedef char *string;

/*
 * Type: proc
 * ----------
 * This function type represents an arbitrary procedure that can be passed
 * to an abstraction and then called back from the implementation.
 */

typedef void (*proc)();

/* Section 2 -- Memory allocation */

/*
 * General notes
 * -------------
 * These functions provide a common interface for memory allocation.  All
 * functions in the library that allocate memory do so using getBlock and
 * freeBlock.  Even though the ANSI standard defines malloc and free for
 * the same purpose, using getBlock and freeBlock provides greater
 * compatibility with non-ANSI implementations, automatic out-of-memory
 * error detection, limited type checking, and the possibility of
 * installing a garbage-collecting allocator.
 */

/*
 * Function: getBlock
 * Usage: ptr = getBlock(nbytes);
 * ------------------------------
 * Allocates a block of memory of the given size.  If no memory is
 * available, getBlock generates an error.
 */

void *getBlock(size_t nbytes);

/*
 * Private function: getTypedBlock
 * -------------------------------
 * Returns a block with the indicated type marker.  This function is called
 * from the newBlock and newArray macros and should not be invoked by
 * clients.
 */

void *getTypedBlock(size_t nbytes, string type);

/*
 * Function: freeBlock
 * Usage: freeBlock(ptr);
 * ----------------------
 * Frees the memory associated with ptr, which must have been allocated
 * using getBlock, newBlock, or newArray.  If the block appears to be in
 * static memory or allocated by malloc, the call to freeBlock has no
 * effect.
 */

void freeBlock(void *ptr);

/*
 * Function: getBlockType
 * Usage: type = getBlockType(ptr);
 * --------------------------------
 * Returns a string indicating the type of the block.  If the block is
 * created using the newBlock macro, the string is the type argument.  If
 * the block is created using newArray, the string consists of the base
 * type followed by the string "[]".  In all other cases, the type is
 * returned as "?".  This string is constant and should not be freed.
 */

string getBlockType(void *ptr);

/*
 * Function: setBlockData
 * Usage: setBlockData(ptr, value);
 * --------------------------------
 * Sets the data field inside the block to the specified value.
 */

void setBlockData(void *ptr, void *value);

/*
 * Function: getBlockData
 * Usage: value = getBlockData(ptr);
 * ---------------------------------
 * Returns the data field inside the block.
 */

void *getBlockData(void *ptr);

/*
 * Macro: newBlock
 * Usage: ptr = (type) newBlock(type);
 * -----------------------------------
 * Allocates enough space to hold an object of the type to which type
 * points (note that type must be a pointer type).  Note that newBlock is
 * different from the new operator used in C++; the former takes a pointer
 * type and the latter takes the target type.
 */

#define newBlock(type) ((type) getTypedBlock(sizeof *((type) NULL), #type))

/*
 * Macro: newArray
 * Usage: ptr = newArray(n, type);
 * -------------------------------
 * Allocates enough space to hold an array of n values of the specified
 * type.
 */

#define newArray(n, type) \
   ((type *) getTypedBlock((n) * sizeof(type), #type "[]"))

/* Section 3 -- error handling */

/*
 * Function: error
 * Usage: error(msg, . . .);
 * -------------------------
 * Generates an error string, expanding % constructions appearing in the
 * error message string just as printf does.  The behavior depends on
 * whether the call is compiled in C or C++.
 *
 * In C, calling error first checks to see if there is a handler for
 * ErrorException.  If so, calling error throws an ErrorException exception
 * with the expanded error string as argument.  If there is no
 * ErrorException handler, the program prints the message to the standard
 * error channel and exits with a status code indicating failure (as given
 * by the constant ERROR_EXIT_STATUS).
 *
 * In C++, calling error throws an exception with the expanded error string
 * (defined as a C++ string) as its value.
 */

   void error(string msg, ...);

/* Section 4 -- Redefine main */

#define main main_

#endif