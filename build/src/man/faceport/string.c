

#include <FACE/string.h>

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 64

#define INITIALIZED 0x12345678

/**
 * @brief Unmanaged initialization
 * @details After initialization, @p this_obj does not manage its own data,
 * but instead serves as a wrapper to the data pointed to by @p src.
 *
 * The caller must ensure @p str is a NULL terminated string
 * If this condition is violated, the result is implementation-defined
 * behavior and may result in an attempt to access restricted memory.
 *
 * The capacity of this string is equal to the length of the NULL terminated string @p str
 * not counting the NULL terminator, because the externally managed memory has a fixed
 * size, which is both a bound and a capacity.
 *
 * After construction the following are true:
 *  - length is the length of the current string not counting the NULL terminator
 *  - capacity is the capacity which is equal to the length of the original string
 *  	not counting the NULL terminator
 *  - bound() is the same as capacity()
 *  - FACE_string_buffer() will return the address specified by @p str
 * @param str pointer to externally managed memory (must be NULL terminated)
 * @retval this_obj
 *
 */
FACE_string *FACE_string_init_unmanaged_bounded(FACE_string* this_obj, const char * str) {
    if (this_obj == NULL) return NULL;
    memset(this_obj, 0, sizeof(FACE_string));
    this_obj->buffer = (char *)str;
    this_obj->length = (str == NULL) ? 0 : (FACE_unsigned_long)strlen(str);
    this_obj->capacity = this_obj->length;
    this_obj->bound = this_obj->length;
    this_obj->is_managed = false;
    this_obj->is_valid = true;
    this_obj->initialized = INITIALIZED;
    return this_obj;
}


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
) {
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_string));
    this_obj->buffer = NULL;
    this_obj->bound = FACE_STRING_UNBOUNDED_SENTINEL;
    this_obj->capacity = 0;
    this_obj->length = 0;
    this_obj->is_managed = true;
    this_obj->is_valid = true;
    this_obj->initialized = INITIALIZED;
    return FACE_STRING_NO_ERROR;
}

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
) { 
    FACE_unsigned_long capacity = 0;
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_string));
    this_obj->is_valid = false;
    if ((bound == 0) || (bound == FACE_STRING_UNBOUNDED_SENTINEL)) return FACE_STRING_PRECONDITION_VIOLATED;
    capacity = (bound < INITIAL_CAPACITY) ? bound : INITIAL_CAPACITY;
    this_obj->buffer = malloc(capacity + 1);
    if (this_obj->buffer == NULL) return FACE_STRING_INSUFFICIENT_MEMORY;
    memset(this_obj->buffer, 0, capacity + 1);
    this_obj->is_managed = true;
    this_obj->bound = bound;
    this_obj->capacity = capacity;
    this_obj->length = 0;
    this_obj->initialized = INITIALIZED;
    this_obj->is_valid = true;
    return FACE_STRING_NO_ERROR;
}

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
) { 
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_string));
    this_obj->is_valid = false;
    if (src == NULL) return FACE_STRING_NULL_PARAM;
    if (src->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (!src->is_valid) return FACE_STRING_INVALID_PARAM;
    this_obj->buffer = malloc(src->capacity + 1);
    if (this_obj->buffer == NULL) return FACE_STRING_INSUFFICIENT_MEMORY;
    memcpy(this_obj->buffer, src->buffer, src->capacity + 1);
    this_obj->is_managed = true;
    this_obj->bound = src->bound;
    this_obj->capacity = src->capacity;    
    this_obj->length = src->length;
    this_obj->initialized = INITIALIZED;
    this_obj->is_valid = true;
    return FACE_STRING_NO_ERROR;
}

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
) { 
    FACE_unsigned_long capacity = 0;
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_string));
    this_obj->is_valid = false;
    if (cstr == NULL) return FACE_STRING_NULL_PARAM;
    if (cstr[0] == '\0') return FACE_STRING_PRECONDITION_VIOLATED;
    capacity = (FACE_unsigned_long)strlen(cstr);
    this_obj->buffer = malloc(capacity + 1);
    if (this_obj->buffer == NULL) return FACE_STRING_INSUFFICIENT_MEMORY;
    memcpy(this_obj->buffer, cstr, capacity + 1);
    this_obj->is_managed = true;
    this_obj->bound = capacity;
    this_obj->capacity = capacity;
    this_obj->length = capacity;
    this_obj->initialized = INITIALIZED;
    this_obj->is_valid = true;
    return FACE_STRING_NO_ERROR;
}

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
) { 
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized == INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    memset(this_obj, 0, sizeof(FACE_string));
    this_obj->is_valid = false;
    if (src == NULL) return FACE_STRING_NULL_PARAM;
    if ((bound == 0) || (bound == FACE_STRING_UNBOUNDED_SENTINEL) || (length > bound)) return FACE_STRING_PRECONDITION_VIOLATED;
    this_obj->is_managed = false;
    this_obj->length = length;
    this_obj->bound = bound;
    this_obj->capacity = bound;
    this_obj->buffer = src;
    this_obj->initialized = INITIALIZED;
    this_obj->is_valid = true;
    return FACE_STRING_NO_ERROR;
}

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
FACE_string_return FACE_string_free(FACE_string* this_obj) { 
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (!this_obj->is_managed) return FACE_STRING_PRECONDITION_VIOLATED;
    if ((this_obj->capacity > 0) && (this_obj->buffer != NULL)) free(this_obj->buffer);
    this_obj->buffer = NULL;
    this_obj->capacity = 0;
    this_obj->length = 0;
    this_obj->initialized = 0;
    return FACE_STRING_NO_ERROR;
}

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
FACE_string_return FACE_string_clear(FACE_string* this_obj) { 
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (this_obj->is_managed && (this_obj->buffer != NULL)) memset(this_obj->buffer, 0, this_obj->capacity + 1);
    this_obj->length = 0;
    return FACE_STRING_NO_ERROR;
}

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
) {
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (src == NULL) return FACE_STRING_NULL_PARAM;
    if (src->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (src->length == 0) return FACE_STRING_NO_ERROR;
    if (src->length > this_obj->bound - this_obj->length) return FACE_STRING_INSUFFICIENT_BOUND;
    if (src->length > this_obj->capacity - this_obj->length) {
        /* Extend capacity */
        char *new_buffer = NULL;
        FACE_unsigned_long new_capacity = INITIAL_CAPACITY * (1 + ((this_obj->length + src->length) / INITIAL_CAPACITY));
        if (new_capacity < this_obj->length + src->length) new_capacity = this_obj->length + src->length;
        if (new_capacity > this_obj->bound) new_capacity = this_obj->bound;
        new_buffer = malloc(new_capacity + 1);
        if (new_buffer == NULL) return FACE_STRING_INSUFFICIENT_MEMORY;
        memset(new_buffer, 0, new_capacity + 1);
        memcpy(new_buffer, this_obj->buffer, this_obj->length);
        if (this_obj->is_managed) free(this_obj->buffer);
        this_obj->buffer = new_buffer;
        this_obj->capacity = new_capacity;
        this_obj->is_managed = true;
    }
    memcpy(this_obj->buffer + this_obj->length, src->buffer, src->length);
    this_obj->length += src->length;
    return FACE_STRING_NO_ERROR;
}

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
) { 
    if ((this_obj == NULL) || (this_obj->initialized != INITIALIZED)) return NULL;
    if (index >= this_obj->length) index = this_obj->length;
    return &this_obj->buffer[index];
}

/**
 * @brief Returns C-string representation of @p this_obj's data
 *
 * @retval NULL if @p this_obj is null or not initialized
 * @retval a pointer to a NUL-terminated (C-style) string equivalent
 * to @p this_obj's underlying string data otherwise
 */
const char * FACE_string_buffer(const FACE_string* this_obj) {
    if ((this_obj == NULL) || (this_obj->initialized != INITIALIZED)) return NULL;
    return this_obj->buffer;
}

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
) { 
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (length == NULL) return FACE_STRING_NULL_PARAM;
    *length = this_obj->length;
    return FACE_STRING_NO_ERROR;
}

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
) { 
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (capacity == NULL) return FACE_STRING_NULL_PARAM;
    *capacity = this_obj->capacity;
    return FACE_STRING_NO_ERROR;
}

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
) {
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (bound == NULL) return FACE_STRING_NULL_PARAM;
    *bound = this_obj->bound;
    return FACE_STRING_NO_ERROR;
}

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
) { 
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (is_managed == NULL) return FACE_STRING_NULL_PARAM;
    *is_managed = this_obj->is_managed;
    return FACE_STRING_NO_ERROR;
}

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
) { 
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (is_bounded == NULL) return FACE_STRING_NULL_PARAM;
    *is_bounded = (this_obj->bound != FACE_STRING_UNBOUNDED_SENTINEL);
    return FACE_STRING_NO_ERROR;
}

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
) {
    if (this_obj == NULL) return FACE_STRING_NULL_THIS;
    if (this_obj->initialized != INITIALIZED) return FACE_STRING_PRECONDITION_VIOLATED;
    if (is_valid == NULL) return FACE_STRING_NULL_PARAM;
    *is_valid = this_obj->is_valid;
    return FACE_STRING_NO_ERROR; 
}
