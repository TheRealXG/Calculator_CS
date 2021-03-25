//! @file FACE/sequence.h
//! @brief Interface for operating on a generic sequence of elements.

#ifndef _FACE_SEQUENCE_H
#define _FACE_SEQUENCE_H

#include <FACE/types.h>
#include <limits.h>
#include <stddef.h>

/**
 * @brief Interface for operating on a generic sequence of elements.
 * @details A FACE_sequence is defined by three characteristics:
 *  - length - the current number of elements in the FACE_sequence
 *  - element size - the size of each element
 *  - bound - the maximum number of elements the FACE_sequence can ever
 *            hold. This bound is logical, and is independent from the size
 *            of any underlying memory. A FACE_sequence's bound is fixed
 *            throughout the lifetime of the FACE_sequence. An "unbounded"
 *            FACE_sequence has an infinite bound, represented by
 *            FACE_SEQUENCE_UNBOUNDED_SENTINEL.
 *  - capacity - the number of elements a FACE_sequence has currently
 *               allocated memory for. This may vary by implementation, but
 *               length <= capacity <= bound is always true.
 *
 * A "managed" FACE_sequence is responsible for and manages the lifetime of
 * the memory for the data it represents. An "unmanaged" FACE_sequence
 * essentially wraps a pointer to memory whose lifetime is managed
 * elsewhere.
 *
 * A FACE_sequence is "initialized" if it is in a state that could have
 * resulted from successful initialization by one of the "_init" functions.
 * Any other state makes the FACE_sequence "uninitialized".
 *
 * When a memory allocation failure or precondition violation occurs, a
 * FACE_sequence is put into a known "invalid state". In this invalid state:
 *  - length, capacity, and bound are 0
 *  - FACE_sequence_buffer() will return NULL
 *  - FACE_sequence_is_managed() and FACE_sequence_is_bounded() will
 *    return FALSE
 * The FACE_sequence_is_valid() function indicates whether or not a
 * FACE_sequence is in this state.
 *
 * Global preconditions:
 * - In every function, if the @p this_obj parameter is NULL, the function
 *   does nothing and returns FACE_SEQUENCE_NULL_THIS.
 * - In every _init function, if this_obj is already initialized,
 *   FACE_SEQUENCE_PRECONDITION_VIOLATED is returned and the state of
 *   this_obj is not modified.
 * - In every non _init function, if this_obj has not been initialized,
 *   FACE_SEQUENCE_PRECONDITION_VIOLATED is returned and the state of
 *   this_obj is not modified.
 */
typedef struct {
    /* implementation-specific */
    size_t sizeof_T;
    FACE_unsigned_long bound;
    FACE_unsigned_long capacity;
    FACE_unsigned_long length;
    FACE_unsigned_long initialized;
    FACE_boolean is_managed;
    FACE_boolean is_valid;
    char * buffer;
} FACE_sequence;

/** @brief Return codes used to report certain runtime errors. */
typedef enum FACE_sequence_return {
 FACE_SEQUENCE_NO_ERROR,              /**< No error has occurred. */
 FACE_SEQUENCE_INSUFFICIENT_BOUND,    /**< Executing a function would cause
                                           a FACE_sequence's length to
                                           exceed its bound. */
 FACE_SEQUENCE_INSUFFICIENT_MEMORY,   /**< A FACE_sequence is unable to
                                           allocate enough memory to perform
                                           some function. */
 FACE_SEQUENCE_PRECONDITION_VIOLATED, /**< A precondition of some function
                                           has been violated. */
 FACE_SEQUENCE_NULL_THIS,             /**< The "this_obj" parameter is a NULL
                                           pointer */
 FACE_SEQUENCE_NULL_PARAM,            /**< One or more other parameters is a
                                           NULL pointer */
 FACE_SEQUENCE_INVALID_PARAM          /**< A FACE_sequence parameter is
                                           invalid. */
} FACE_sequence_return;

/** @brief Value representing the bound of an unbounded FACE_sequence. */
#define FACE_SEQUENCE_UNBOUNDED_SENTINEL ((FACE_unsigned_long) UINT_MAX)

/**
 * @brief Managed unbounded initialization - initializes empty managed
 * unbounded FACE_sequence
 * @details (see #FACE_string_init_managed_unbounded)
 *
 * After initialization, FACE_sequence_buffer() will return NULL.
 *
 * @param this_obj the FACE_sequence to be initialized
 * @param sizeof_T the size of each element in @p this_obj
 */
FACE_sequence_return FACE_sequence_init_managed_unbounded(
  FACE_sequence* this_obj,
  size_t         sizeof_T
);

/**
 * @brief Managed bounded initialization - initializes empty managed 
 * FACE_sequence of specified bound
 * @details (see #FACE_string_init_managed_bounded)
 *
 * If allocation is successful, FACE_sequence_buffer() will return NULL.
 *
 * @param this_obj the FACE_sequence to be initialized
 * @param sizeof_T the size of each element in @p this_obj
 * @param bound the specified bound for @p this_obj to be initialized with
 */
FACE_sequence_return FACE_sequence_init_managed_bounded(
  FACE_sequence*     this_obj,
  size_t             sizeof_T,
  FACE_unsigned_long bound
);

/**
 * @brief Managed copy initialization
 * @details (see #FACE_string_init_managed_copy)
 */
FACE_sequence_return FACE_sequence_init_managed_copy(
  FACE_sequence* this_obj,
  FACE_sequence* src
);

/**
 * @brief Managed array initialization
 * @details After initialization, this FACE_sequence manages its own data,
 * which is a copy of the @p length elements of size @p sizeof_T in the
 * array pointed to by @p arr, and the bound of @p this_obj is equal to
 * @p length.
 *
 * Preconditions:
 *  - arr != NULL
 *  - arr is not empty
 *  - sizeof_T != 0
 *  - length != 0
 * When calling this function, if any of these preconditions are false,
 *  - FACE_SEQUENCE_NULL_PARAM will be returned (if arr is NULL) or
 *    FACE_SEQUENCE_PRECONDITION_VIOLATED will be returned (if any other
 *    precondition is violated)
 *  - @p this_obj is put into the invalid state
 *
 * If no preconditions are violated and memory allocation fails:
 *  - FACE_SEQUENCE_INSUFFICIENT_MEMORY will be returned
 *  - @p this_obj is put into the invalid state
 *
 * The caller must ensure @p length * @p sizeof_T is not greater than the
 * size of the memory allocated at @p arr. If this condition is violated,
 * the result is implementation-defined behavior and may result in an
 * attempt to access restricted memory.
 *
 * @param this_obj the FACE_sequence to be initialized
 * @param arr a pointer to the array
 * @param sizeof_T the size of each element in the array
 * @param length the number of elements in the array
 *
 * @retval FACE_SEQUENCE_NULL_THIS if @p this_obj is null
 * @retval FACE_SEQUENCE_PRECONDITION_VIOLATED if @p this_obj is already 
 *         initialized or any other preconditions are false
 * @retval FACE_SEQUENCE_NULL_PARAM if @p arr is null
 * @retval FACE_SEQUENCE_INSUFFICIENT_MEMORY if memory allocation fails
 * @retval FACE_SEQUENCE_NO_ERROR otherwise.
 */
FACE_sequence_return FACE_sequence_init_managed_data(
  FACE_sequence*     this_obj,
  const void *       arr,
  size_t             sizeof_T,
  FACE_unsigned_long length
);

/**
 * @brief Unmanaged initialization
 * @details (see #FACE_string_init_unmanaged)
 *
 * The caller must ensure @p bound * @p sizeof_T is not greater than the
 * size of the memory allocated at @p src. If this condition is violated,
 * the result is implementation-defined behavior and may result in an
 * attempt to access restricted memory.
 *
 * Preconditions:
 *  - src != NULL
 *  - length <= bound
 *  - bound != 0 (no empty unmanaged sequences)
 *  - bound != UNBOUNDED_SENTINEL (no unbounded unmanaged sequences)
 *  - sizeof_T != 0
 * When calling this function, if any of these preconditions are false,
 *  - FACE_SEQUENCE_NULL_PARAM will be returned (if src is NULL) or
 *  - FACE_SEQUENCE_PRECONDITION_VIOLATED will be returned (if any other
 *    preconditions are violated)
 *  - @p this_obj is put into the invalid state
 *
 * @param this_obj a pointer to the FACE_sequence to be initialized
 * @param src pointer to externally managed memory
 * @param length the number of elements in the memory pointed to by @p src
 * @param sizeof_T the size of each element in the memory pointed to by
 *        @p src
 * @param bound the number of elements the externally managed memory can
 *        hold.
 * Also serves as a capacity.
 */
FACE_sequence_return FACE_sequence_init_unmanaged(
  FACE_sequence*     this_obj,
  void *             src,
  size_t             sizeof_T,
  FACE_unsigned_long length,
  FACE_unsigned_long bound
);

/**
 * @brief Frees any data managed by @p this_obj.
 * @details (see #FACE_string_free)
 */
FACE_sequence_return FACE_sequence_free(FACE_sequence* this_obj);

/**
 * @brief Clears @p this_obj's data.
 * @details (see #FACE_string_clear)
 */
FACE_sequence_return FACE_sequence_clear(FACE_sequence* this_obj);

/**
 * @brief Adds a copy of @p src's data to the @p this_obj's data
 * @details (see #FACE_string_append)
 */
FACE_sequence_return FACE_sequence_append(
  FACE_sequence*       this_obj,
  const FACE_sequence* src
);

/**
 * @brief Gets the element at a given index.
 * @details (see #FACE_sequence_at)
 *
 * @retval NULL if @p this_obj is null, not initialized, or if index is out
 * of range
 * @retval a const pointer to the element at the given index otherwise.
 */
const void * FACE_sequence_at(
  const FACE_sequence* this_obj,
  FACE_unsigned_long   index
);

/**
 * @brief Returns pointer to @p this_obj's underlying data
 * @details To avoid accessing restricted memory, the caller should avoid
 * dereferencing memory beyond buffer + length*(the size of each element).
 *
 * @retval NULL if @p this_obj is null or not initialized
 * @retval a pointer to contiguous memory for @p this_obj's data otherwise
 */
const void * FACE_sequence_buffer(const FACE_sequence* this_obj);

/**
 * @brief Gets the length of @p this_obj.
 * @details (see #FACE_string_length)
 */
FACE_sequence_return FACE_sequence_length(
  const FACE_sequence* this_obj,
  FACE_unsigned_long*  length
);

/**
 * @brief Gets the capacity of @p this_obj.
 * @details (see #FACE_string_capacity)
 */
FACE_sequence_return FACE_sequence_capacity(
  const FACE_sequence* this_obj,
  FACE_unsigned_long*  capacity
);

/**
 * @brief Gets the bound of @p this_obj.
 * @details (see #FACE_string_bound)
 */
FACE_sequence_return FACE_sequence_bound(
  const FACE_sequence* this_obj,
  FACE_unsigned_long*  bound
);

/**
 * @brief Gets whether or not @p this_obj is managed.
 * @details (see #FACE_string_is_managed)
 */
FACE_sequence_return FACE_sequence_is_managed(
  const FACE_sequence* this_obj,
  FACE_boolean*        is_managed
);

/**
 * @brief Gets whether or not @p this_obj is bounded.
 * @details (see #FACE_string_is_bounded)
 */
FACE_sequence_return FACE_sequence_is_bounded(
  const FACE_sequence* this_obj,
  FACE_boolean*        is_bounded
);

/**
 * @brief Gets whether or not @p this_obj is in the invalid state.
 * @details (see #FACE_string_is_valid)
 */
FACE_sequence_return FACE_sequence_is_valid(
  const FACE_sequence* this_obj,
  FACE_boolean*        is_valid
);

#endif /* _FACE_SEQUENCE_H */
