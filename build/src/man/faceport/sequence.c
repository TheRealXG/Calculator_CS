
#include <FACE/sequence.h>

#include <stdlib.h>
#include <string.h>

#define INITIALIZED 0x12345678

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
) { 
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_sequence));
    this_obj->is_valid = false;
    if (sizeof_T == 0) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    this_obj->buffer = NULL;
    this_obj->sizeof_T = sizeof_T;
    this_obj->bound = FACE_SEQUENCE_UNBOUNDED_SENTINEL;
    this_obj->capacity = 0;
    this_obj->length = 0;
    this_obj->is_managed = true;
    this_obj->is_valid = true;
    this_obj->initialized = INITIALIZED;
    return FACE_SEQUENCE_NO_ERROR;
}

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
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_sequence));
    this_obj->is_valid = false;
    if ((sizeof_T == 0) || (bound == 0) || (bound == FACE_SEQUENCE_UNBOUNDED_SENTINEL)) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    this_obj->buffer = NULL;
    this_obj->sizeof_T = sizeof_T;
    this_obj->bound = bound;
    this_obj->capacity = 0;
    this_obj->length = 0;
    this_obj->is_managed = true;
    this_obj->is_valid = true;
    this_obj->initialized = INITIALIZED;
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Managed copy initialization
 * @details (see #FACE_string_init_managed_copy)
 */
FACE_sequence_return FACE_sequence_init_managed_copy(
  FACE_sequence* this_obj,
  FACE_sequence* src
) {
    size_t bufsize = 0;
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_sequence));
    this_obj->is_valid = false;
    if (src == NULL) return FACE_SEQUENCE_NULL_PARAM;
    if (src->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (!src->is_valid) return FACE_SEQUENCE_INVALID_PARAM;
    bufsize = src->capacity * src->sizeof_T;
    if (bufsize > 0) {
        this_obj->buffer = malloc(bufsize);
        if (this_obj->buffer == NULL) return FACE_SEQUENCE_INSUFFICIENT_MEMORY;
        memcpy(this_obj->buffer, src->buffer, bufsize);
    }
    else {
        this_obj->buffer = NULL;
    }
    this_obj->is_managed = true;
    this_obj->sizeof_T = src->sizeof_T;
    this_obj->bound = src->bound;
    this_obj->capacity = src->capacity;
    this_obj->length = src->length;
    this_obj->initialized = INITIALIZED;
    this_obj->is_valid = true;
    return FACE_SEQUENCE_NO_ERROR;
}

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
) {
    size_t bufsize = 0;
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_sequence));
    this_obj->is_valid = false;
    if (arr == NULL) return FACE_SEQUENCE_NULL_PARAM;
    if ((sizeof_T == 0) || (length == 0)) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    bufsize = length * sizeof_T;
    this_obj->buffer = malloc(bufsize);
    if (this_obj->buffer == NULL) return FACE_SEQUENCE_INSUFFICIENT_MEMORY;
    /* We assume that sizeof_T is well aligned as array element size */
    memcpy(this_obj->buffer, arr, bufsize);
    this_obj->is_managed = true;
    this_obj->sizeof_T = sizeof_T;
    this_obj->bound = length;
    this_obj->capacity = length;
    this_obj->length = length;
    this_obj->initialized = INITIALIZED;
    this_obj->is_valid = true;
    return FACE_SEQUENCE_NO_ERROR;
}

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
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_sequence));
    this_obj->is_valid = false;
    if (src == NULL) return FACE_SEQUENCE_NULL_PARAM;
    if ((sizeof_T == 0) || (bound == 0) || (bound == FACE_SEQUENCE_UNBOUNDED_SENTINEL) || (length > bound)) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    this_obj->is_managed = false;
    this_obj->sizeof_T = sizeof_T;
    this_obj->length = length;
    this_obj->bound = bound;
    this_obj->capacity = bound;
    this_obj->buffer = src;
    this_obj->initialized = INITIALIZED;
    this_obj->is_valid = true;
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Frees any data managed by @p this_obj.
 * @details (see #FACE_string_free)
 */
FACE_sequence_return FACE_sequence_free(FACE_sequence* this_obj) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (!this_obj->is_managed) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (this_obj->buffer != NULL) free(this_obj->buffer);
    this_obj->buffer = NULL;
    this_obj->capacity = 0;
    this_obj->length = 0;
	this_obj->initialized = 0;
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Clears @p this_obj's data.
 * @details (see #FACE_string_clear)
 */
FACE_sequence_return FACE_sequence_clear(FACE_sequence* this_obj) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (this_obj->is_managed && (this_obj->buffer != NULL)) memset(this_obj->buffer, 0, this_obj->capacity * this_obj->sizeof_T);
    this_obj->length = 0;
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Adds a copy of @p src's data to the @p this_obj's data
 * @details (see #FACE_string_append)
 */
FACE_sequence_return FACE_sequence_append(
  FACE_sequence*       this_obj,
  const FACE_sequence* src
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (src == NULL) return FACE_SEQUENCE_NULL_PARAM;
    if (src->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (this_obj->sizeof_T != src->sizeof_T) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (src->length == 0) return FACE_SEQUENCE_NO_ERROR;
    if (src->length > this_obj->bound - this_obj->length) return FACE_SEQUENCE_INSUFFICIENT_BOUND;
    if (src->length > this_obj->capacity - this_obj->length) {
        /* Extend capacity */
        FACE_unsigned_long new_capacity = this_obj->length + src->length;
        size_t bufsize = new_capacity * this_obj->sizeof_T;
        char *new_buffer = malloc(bufsize);
        if (new_buffer == NULL) return FACE_SEQUENCE_INSUFFICIENT_MEMORY;
        memset(new_buffer, 0, bufsize);
        memcpy(new_buffer, this_obj->buffer, this_obj->length * this_obj->sizeof_T);
        if (this_obj->is_managed) free(this_obj->buffer);
        this_obj->buffer = new_buffer;
        this_obj->capacity = new_capacity;
        this_obj->is_managed = true;
    }
    memcpy(this_obj->buffer + (this_obj->length * this_obj->sizeof_T), src->buffer, (src->length * this_obj->sizeof_T));
    this_obj->length += src->length;
    return FACE_SEQUENCE_NO_ERROR;
}

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
) {
    if ((this_obj == NULL) || (this_obj->initialized != INITIALIZED) || (index >= this_obj->length)) return NULL;
    return this_obj->buffer + (index * this_obj->sizeof_T);
}

/**
 * @brief Returns pointer to @p this_obj's underlying data
 * @details To avoid accessing restricted memory, the caller should avoid
 * dereferencing memory beyond buffer + length*(the size of each element).
 *
 * @retval NULL if @p this_obj is null or not initialized
 * @retval a pointer to contiguous memory for @p this_obj's data otherwise
 */
const void * FACE_sequence_buffer(const FACE_sequence* this_obj) {
    if ((this_obj == NULL) || (this_obj->initialized != INITIALIZED)) return NULL;
    return this_obj->buffer;
}

/**
 * @brief Gets the length of @p this_obj.
 * @details (see #FACE_string_length)
 */
FACE_sequence_return FACE_sequence_length(
  const FACE_sequence* this_obj,
  FACE_unsigned_long*  length
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (length == NULL) return FACE_SEQUENCE_NULL_PARAM;
    *length = this_obj->length;
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Gets the capacity of @p this_obj.
 * @details (see #FACE_string_capacity)
 */
FACE_sequence_return FACE_sequence_capacity(
  const FACE_sequence* this_obj,
  FACE_unsigned_long*  capacity
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (capacity == NULL) return FACE_SEQUENCE_NULL_PARAM;
    *capacity = this_obj->capacity;
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Gets the bound of @p this_obj.
 * @details (see #FACE_string_bound)
 */
FACE_sequence_return FACE_sequence_bound(
  const FACE_sequence* this_obj,
  FACE_unsigned_long*  bound
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (bound == NULL) return FACE_SEQUENCE_NULL_PARAM;
    *bound = this_obj->bound;
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Gets whether or not @p this_obj is managed.
 * @details (see #FACE_string_is_managed)
 */
FACE_sequence_return FACE_sequence_is_managed(
  const FACE_sequence* this_obj,
  FACE_boolean*        is_managed
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (is_managed == NULL) return FACE_SEQUENCE_NULL_PARAM;
    *is_managed = this_obj->is_managed;
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Gets whether or not @p this_obj is bounded.
 * @details (see #FACE_string_is_bounded)
 */
FACE_sequence_return FACE_sequence_is_bounded(
  const FACE_sequence* this_obj,
  FACE_boolean*        is_bounded
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (is_bounded == NULL) return FACE_SEQUENCE_NULL_PARAM;
    *is_bounded = (this_obj->bound != FACE_SEQUENCE_UNBOUNDED_SENTINEL);
    return FACE_SEQUENCE_NO_ERROR;
}

/**
 * @brief Gets whether or not @p this_obj is in the invalid state.
 * @details (see #FACE_string_is_valid)
 */
FACE_sequence_return FACE_sequence_is_valid(
  const FACE_sequence* this_obj,
  FACE_boolean*        is_valid
) {
    if (this_obj == NULL) return FACE_SEQUENCE_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_SEQUENCE_PRECONDITION_VIOLATED;
    if (is_valid == NULL) return FACE_SEQUENCE_NULL_PARAM;
    *is_valid = this_obj->is_valid;
    return FACE_SEQUENCE_NO_ERROR;
}
