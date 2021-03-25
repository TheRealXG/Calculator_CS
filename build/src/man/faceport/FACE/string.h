//! @file FACE/string.h
//! @brief Interface for operating on a sequence of characters.

#ifndef _FACE_STRING_H
#define _FACE_STRING_H

#include <FACE/types.h>
#include <limits.h>

/**
 * @brief Interface for operating on a sequence of characters.
 * @details A FACE_string is defined by three characteristics:
 *  - length - the current number of characters (excluding NUL)
 *             in the FACE_string
 *  - bound - the maximum number of characters (excluding NUL)
 *            the FACE_string can ever hold. This bound is logical, and is
 *            independent from the size of any underlying memory.
 *            A FACE_string's bound is fixed throughout the lifetime of the
 *            FACE_string. An "unbounded" FACE_string has an infinite bound,
 *            represented by FACE_STRING_UNBOUNDED_SENTINEL.
 *  - capacity - the number of characters (excluding NUL)
 *               a FACE_string has currently allocated memory for. This may
 *               vary by implementation, but length <= capacity <= bound is
 *               always true.
 *
 * A "managed" FACE_string is responsible for and manages the lifetime of
 * the memory for the data it represents. An "unmanaged" FACE_string
 * essentially wraps a pointer to memory whose lifetime is managed
 * elsewhere.
 *
 * A FACE_string is "initialized" if it is in a state that could have
 * resulted from successful initialization by one of the "_init" functions.
 * Any other state makes the FACE_string "uninitialized".
 *
 * When a memory allocation failure or precondition violation occurs, a
 * FACE_string is put into a known "invalid state". In this invalid state:
 *  - length, capacity, and bound are 0
 *  - FACE_string_buffer() will return NULL
 *  - FACE_string_is_managed() and FACE_string_is_bounded() will return
 *    FALSE
 * The FACE_string_is_valid() function indicates whether or not a
 * FACE_string is in this state.
 *
 * Global preconditions:
 * - In every function, if the @p this_obj parameter is NULL, the function
 *   does nothing and returns FACE_STRING_NULL_THIS.
 * - In every _init function, if this_obj is already initialized,
 *   FACE_STRING_PRECONDITION_VIOLATED is returned and the state of this_obj
 *   is not modified.
 * - In every non _init function, if this_obj has not been initialized,
 *   FACE_STRING_PRECONDITION_VIOLATED is returned and the state of this_obj
 *   is not modified.
 */
typedef struct {
    /* implementation-specific */
    FACE_unsigned_long bound;
    FACE_unsigned_long capacity;
    FACE_unsigned_long length;
    FACE_unsigned_long initialized;
    FACE_boolean is_managed;
    FACE_boolean is_valid;
    char * buffer;
} FACE_string;

/** @brief Return codes used to report certain runtime errors. */
typedef enum FACE_string_return {
  FACE_STRING_NO_ERROR,              /**< No error has occurred. */
  FACE_STRING_INSUFFICIENT_BOUND,    /**< Executing a function would cause a
                                          FACE_string's length to exceed its
                                          bound. */
  FACE_STRING_INSUFFICIENT_MEMORY,   /**< A FACE_string is unable to
                                          allocate enough memory to perform
                                          some function. */
  FACE_STRING_PRECONDITION_VIOLATED, /**< A precondition of some function
                                          has been violated. */
  FACE_STRING_NULL_THIS,             /**< The "this_obj" parameter is a NULL
                                          pointer */
  FACE_STRING_NULL_PARAM,            /**< One or more other parameters is a
                                          NULL pointer */
  FACE_STRING_INVALID_PARAM          /**< A FACE_string parameter is
                                          invalid. */
} FACE_string_return;

/** @brief Value representing the bound of an unbounded FACE_string. */
#define FACE_STRING_UNBOUNDED_SENTINEL ((FACE_unsigned_long) UINT_MAX)

/**
 * @brief Unmanaged initialization
 * @details After initialization, @p this_obj does not manage its own data,
 * but instead serves as a wrapper to the data pointed to by @p src.
 *
 * The caller must ensure @p str is a NULL terminated string
 * If this condition is violated, the result is implementation-defined
 * behavior and may result in an attempt to access restricted memory.
 *
 * The capacity of this string is equal to the length of the NULL
 * terminated string @p str not counting the NULL terminator, because
 * the externally managed memory has a fixed size, which is both a bound
 * and a capacity.
 *
 * After construction the following are true:
 *  - length is the length of the current string not counting the NULL
 *    terminator
 *  - capacity is the capacity which is equal to the length of the
 *    original string not counting the NULL terminator
 *  - bound() is the same as capacity()
 *  - FACE_string_buffer() will return the address specified by @p str
 * @param str pointer to externally managed memory (must be NULL terminated)
 * @retval this_obj
 *
 */
FACE_string *FACE_string_init_unmanaged_bounded(
  FACE_string* this_obj,
  const char * str
);

/**
 * @brief Managed unbounded initialization - initializes empty managed
 * unbounded FACE_string
 * @details No memory is allocated. After initialization,
 *  - length will be 0
 *  - capacity will be 0
 *  - bound will be FACE_STRING_UNBOUNDED_SENTINEL
 *  - FACE_string_buffer() will get the empty string
 *
 * @param this_obj the FACE_string to be initialized.
 *
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is already 
 *         initialized
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_init_managed_unbounded(
  FACE_string* this_obj
);

/**
 * @brief Managed bounded initialization - initializes empty managed
 * FACE_string of specified bound
 * @details Memory may or may not be allocated.
 *
 * Preconditions:
 *  - bound != 0
 *  - bound != FACE_STRING_UNBOUNDED_SENTINEL
 * When calling this function, if any of these preconditions are false,
 *  - FACE_STRING_PRECONDITION_VIOLATED will be returned
 *  - @p this_obj is put into the invalid state
 *
 * While the implementation does not have to allocate memory equal in
 * size to the requested bound, memory allocation may still fail. If no
 * preconditions are violated and memory allocation fails:
 *  - FACE_STRING_INSUFFICIENT_MEMORY will be returned
 *  - @p this_obj is put into the invalid state
 *
 * Otherwise:
 *  - length will be 0
 *  - capacity will be the current capacity
 *  - bound will be the specified bound
 *  - FACE_string_buffer() will get the empty string
 *
 * @param this_obj the FACE_string to be initialized
 * @param bound the specified bound for the @p this_obj to be initialized
 *        with
 *
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is already 
 *         initialized or if any other preconditions are false
 * @retval FACE_STRING_INSUFFICIENT_MEMORY if memory allocation fails
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_init_managed_bounded(
  FACE_string*       this_obj,
  FACE_unsigned_long bound
);

/**
 * @brief Managed copy initialization
 * @details After initialization, @p this_obj manages its own data, which is
 * a copy of @p src's data, and has the same bound as @p src.
 *
 * Preconditions:
 *  - @p src != NULL
 *  - @p src is initialized
 * When calling this function, if any of these preconditions are false,
 *  - FACE_STRING_NULL_PARAM will be returned (if src is NULL) or
 *    FACE_STRING_PRECONDITION_VIOLATED will be returned (if src is not
 *    initialized)
 *  - @p this_obj is put into the invalid state
 *
 * If no preconditions are violated and memory allocation fails:
 *  - FACE_STRING_INSUFFICIENT_MEMORY will be returned
 *  - @p this_obj is put into the invalid state
 *
 * @param this_obj the FACE_string to be initialized
 * @param src the FACE_string to initialize @p this_obj with
 *
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is already 
 *         initialized or if @p src is not initialized
 * @retval FACE_STRING_NULL_PARAM if @p src is null
 * @retval FACE_STRING_INVALID_PARAM if @p src is in the invalid state
 * @retval FACE_STRING_INSUFFICIENT_MEMORY if memory allocation fails
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_init_managed_copy(
  FACE_string* this_obj,
  FACE_string* src
);

/**
 * @brief Managed C-string initialization
 * @details After initialization, @p this_obj manages its own data, which is
 * a copy of @p cstr, and the bound of @p this_obj is equal to @p cstr's
 * length.
 *
 * Preconditions:
 *  - cstr != NULL
 *  - cstr is not empty
 * When calling this function, if any of these preconditions are false,
 *  - FACE_STRING_NULL_PARAM will be returned (if cstr is NULL) or
 *    FACE_STRING_PRECONDITION_VIOLATED will be returned (if cstr is not
 *    empty)
 *  - @p this_obj is put into the invalid state
 *
 * If no preconditions are violated and memory allocation fails:
 *  - FACE_STRING_INSUFFICIENT_MEMORY will be returned
 *  - @p this_obj is put into the invalid state
 *
 * @param this_obj the FACE_string to be initialized
 * @param cstr a NUL-terminated string to initialize @p this_obj's data with
 *
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is already 
 *         initialized or if @p cstr is empty
 * @retval FACE_STRING_NULL_PARAM if @p cstr is null
 * @retval FACE_STRING_INSUFFICIENT_MEMORY if memory allocation fails
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_init_managed_cstring(
  FACE_string* this_obj,
  const char * cstr
);

/**
 * @brief Unmanaged initialization
 * @details After initialization, @p this_obj does not manage its own data,
 * but instead serves as a wrapper to the data pointed to by @p src.
 *
 * The caller must ensure @p bound (plus space for NUL)
 * is not greater than the size of the memory allocated at @p src.
 * If this condition is violated, the result is implementation-defined
 * behavior and may result in an attempt to access restricted memory.
 *
 * The capacity of @p this_obj will be equal to its bound, because the
 * externally managed memory has a fixed size, which is both a bound and a
 * capacity.
 *
 * Preconditions:
 *  - src != NULL
 *  - length <= bound
 *  - bound != 0 (no empty unmanaged strings)
 *  - bound != UNBOUNDED_SENTINEL (no unbounded unmanaged strings)
 * When calling this function, if any of these preconditions are false,
 *  - FACE_STRING_NULL_PARAM will be returned (if src is NULL) or
 *  - FACE_STRING_PRECONDITION_VIOLATED will be returned (if any other
 *    preconditions are violated)
 *  - @p this_obj is put into the invalid state
 *
 * Otherwise:
 *  - FACE_STRING_NO_ERROR will be returned
 *  - length will be the specified length
 *  - capacity will return the specified capacity (bound)
 *  - bound() will return the specified bound
 *  - FACE_string_buffer() will return a pointer to the externally managed
 *    memory
 *
 * @param this_obj a pointer to the FACE_string to be initialized
 * @param src pointer to externally managed memory
 * @param length the number of characters (excluding the NUL character) in
 *        the memory pointed to by @p src
 * @param bound the number of characters (excluding the NUL character)
 *        the externally managed memory can hold. Also serves as a capacity.
 *
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is already 
 *         initialized or any other preconditions are false
 * @retval FACE_STRING_NULL_PARAM if @p src is null
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_init_unmanaged(
  FACE_string*       this_obj,
  char*              src,
  FACE_unsigned_long length,
  FACE_unsigned_long bound
);

/**
 * @brief Frees any data managed by @p this_obj.
 * @details If any preconditions are violated, @p this_obj's state remains
 * unchanged.
 *
 * Preconditions:
 *  - @p this_obj is managed
 *
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not
 *         initialized or any other preconditions are false
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_free(FACE_string* this_obj);

/**
 * @brief Clears @p this_obj's data.
 * @details If any preconditions are violated, @p this_obj's state remains
 * unchanged.
 *
 * Otherwise, all data is cleared, and @p this_obj's length will be set
 * to 0. Memory allocation remains unchanged.
 *
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not
 *         initialized or any other preconditions are false
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_clear(FACE_string* this_obj);

/**
 * @brief Adds a copy of @p src's data to the @p this_obj's data
 * @details This is the only FACE_string function that may reallocate
 * managed memory. If append is successful, the length of this String
 * changes accordingly; capacity may or may not be changed.
 * If append is unsuccessful, @p this_obj's state remains unchanged.
 *
 * Preconditions:
 *  - @p src != NULL
 *  - @p src is initialized
 * When calling this function, if any of these preconditions are false,
 *  - FACE_STRING_NULL_PARAM will be returned (if src is NULL) or
 *    FACE_STRING_PRECONDITION_VIOLATED will be returned (if any other
 *    preconditions are violated)
 * 
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not 
 *         initialized or if @p src is not initialized
 * @retval FACE_STRING_NULL_PARAM if @p src is null
 * @retval FACE_STRING_INSUFFICIENT_BOUND if append would exceed logical
 *         bound
 * @retval FACE_STRING_INSUFFICIENT_MEMORY if append exceeds available
 *         memory
 * @retval FACE_STRING_NO_ERROR otherwise
 */
FACE_string_return FACE_string_append(
  FACE_string*       this_obj,
  const FACE_string* src
);

/**
 * @brief Gets the character at a given index.
 * @details FACE_strings use a zero-based index.
 *
 * @param this_obj a const pointer to the FACE_string being indexed.
 * @param index The index of the element to be retrieved.
 * 
 * @retval NULL if @p this_obj is null or not initialized
 * @retval '\0' if index is out of range
 * @retval a const pointer to the character at the given index otherwise
 */
const char * FACE_string_at(
  const FACE_string* this_obj,
  FACE_unsigned_long index
);

/**
 * @brief Returns C-string representation of @p this_obj's data
 *
 * @retval NULL if @p this_obj is null or not initialized
 * @retval a pointer to a NUL-terminated (C-style) string equivalent
 * to @p this_obj's underlying string data otherwise
 */
const char * FACE_string_buffer(const FACE_string* this_obj);

/**
 * @brief Gets the length of @p this_obj.
 * 
 * @param this_obj a const pointer to the FACE_string to get the length of
 * @param length A pointer where the length will be stored.
 * 
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not
 *         initialized
 * @retval FACE_STRING_NULL_PARAM if @p length is null
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_length(
  const FACE_string*  this_obj,
  FACE_unsigned_long* length
);

/**
 * @brief Gets the capacity of @p this_obj.
 * 
 * @param this_obj a const pointer to the FACE_string to get the capacity of
 * @param capacity A pointer where the capacity will be stored.
 * 
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not
 *         initialized
 * @retval FACE_STRING_NULL_PARAM if @p capacity is null
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_capacity(
  const FACE_string*  this_obj,
  FACE_unsigned_long* capacity
);

/**
 * @brief Gets the bound of @p this_obj.
 * 
 * @param this_obj a const pointer to the FACE_string to get the capacity of
 * @param bound A pointer where the bound will be stored.
 * 
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not
 *         initialized
 * @retval FACE_STRING_NULL_PARAM if @p bound is null
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_bound(
  const FACE_string*  this_obj,
  FACE_unsigned_long* bound
);

/**
 * @brief Gets whether or not @p this_obj is managed.
 * 
 * @param this_obj a const pointer to the FACE_string to check
 * @param is_managed A pointer where the result will be stored.
 * @p is_managed will be 1 if @p this_obj manages its own memory, and 0
 * otherwise.
 * 
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not
 *         initialized
 * @retval FACE_STRING_NULL_PARAM if @p is_managed is null
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_is_managed(
  const FACE_string* this_obj,
  FACE_boolean*      is_managed
);

/**
 * @brief Gets whether or not @p this_obj is bounded.
 * 
 * @param this_obj a const pointer to the FACE_string to check
 * @param is_bounded A pointer where the result will be stored.
 *        @p is_bounded will be 1 if @p this_obj is bounded, and 0
 *        otherwise.
 * 
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not
 *         initialized
 * @retval FACE_STRING_NULL_PARAM if @p is_bounded is null
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_is_bounded(
  const FACE_string* this_obj,
  FACE_boolean*      is_bounded
);

/**
 * @brief Gets whether or not @p this_obj is in the invalid state.
 * @details (see FACE_string details)
 * 
 * @param this_obj a const pointer to the FACE_string to check
 * @param is_valid A pointer where the result will be stored. @p is_valid
 *        will be 0 if @p this_obj is in the invalid state, and 1 otherwise.
 * 
 * @retval FACE_STRING_NULL_THIS if @p this_obj is null
 * @retval FACE_STRING_PRECONDITION_VIOLATED if @p this_obj is not
 *         initialized
 * @retval FACE_STRING_NULL_PARAM if @p is_valid is null
 * @retval FACE_STRING_NO_ERROR otherwise.
 */
FACE_string_return FACE_string_is_valid(
  const FACE_string* this_obj,
  FACE_boolean*      is_valid
);

#endif /* _FACE_STRING_H */
