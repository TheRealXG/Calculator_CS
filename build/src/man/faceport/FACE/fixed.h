//! @file FACE/fixed.h
//! @brief Interface for a generic fixed type

#ifndef _FACE_FIXED_H
#define _FACE_FIXED_H

#include <FACE/types.h>

/** 
 * @brief The maximum number of digits in a fixed-point number
 * (enforced by IDL).
 */
#define FACE_FIXED_DIGITS_MAX ((FACE_short) 31)

/**
 * @brief Data structure representing generic fixed type.
 */
typedef struct {
  /* implementation-specific */
    double data;
} FACE_fixed;

/**
 * @brief Return codes for FACE_fixed functions
 *
 */
typedef enum {
  FACE_FIXED_NO_ERROR,    /**< No error has occurred. */
  FACE_FIXED_NULL_THIS,   /**< The "this_obj" parameter is a NULL pointer */
  FACE_FIXED_NULL_PARAM,  /**< One or more other parameters is a NULL
                                 pointer */
  FACE_FIXED_INVALID_PARAM, /**< One or more fixed-point number parameters
                                 are uninitialized or in an inconsistent
                                 state. */
  FACE_FIXED_TOO_LARGE      /**< A value is too large to fit in a
                                 fixed-point number. */
} FACE_fixed_return;

/**
 * @brief Initializes a fixed-point number with specified digits and scale.
 * @details After initialization, the value of @p this_obj is zero.
 *
 * @param this_obj A pointer to the fixed-point number
 * @param digits Total number of digits
 * @param scale Number of significant fractional digits
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_INVALID_PARAM if any of the conditions in
 *         FACE_fixed_valid are violated
 * @retval FACE_FIXED_NO_ERROR Operation was successful.
 */
FACE_fixed_return FACE_fixed_init(FACE_fixed* this_obj,
                                  FACE_unsigned_short digits,
                                  FACE_unsigned_short scale
);

/**
 * @brief Gets the total number of digits of a fixed-point number.
 *
 * @param this_obj A const pointer to the fixed-point number.
 * @param digits Pointer to digits; is set if call successful.
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p digits is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is invalid.
 * @retval FACE_FIXED_NO_ERROR Operation was successful.
 */
FACE_fixed_return FACE_fixed_digits(FACE_fixed*          this_obj,
                                    FACE_unsigned_short* digits);

/**
 * @brief Gets the scale (number of significant fractional digits) of a
 * fixed-point number.
 *
 * @param this_obj A const pointer to the fixed-point number.
 * @param scale Pointer to scale; is set if call successful.
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p scale is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is invalid.
 * @retval FACE_FIXED_NO_ERROR Operation was successful.
 */
FACE_fixed_return FACE_fixed_scale(FACE_fixed*          this_obj,
                                   FACE_unsigned_short* scale);

/**
 * @brief Checks that the contents of a fixed-point number are consistent.
 * @details A fixed-point number is consistent if:
 *   - digits does not exceed FACE_FIXED_DIGITS_MAX.
 *   - scale does not exceed digits.
 *
 * @param this_obj a pointer to the fixed-point number.
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_INVALID_PARAM if any of the above conditions are
 *         violated.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
FACE_fixed_return FACE_fixed_valid(FACE_fixed* this_obj);
 
/**
 * @brief Makes a copy of a fixed-point number.
 * @param this_obj a pointer to the destination fixed-point number
 * @param src a pointer to the source fixed-point number
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p src is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is an invalid fixed-point 
 *         number.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
FACE_fixed_return FACE_fixed_dup(FACE_fixed*       this_obj,
                                 const FACE_fixed* src
);


/**
 * @name Conversion Initializers
 * @anchor Conversion_Initializers
 * @brief Initializes a fixed-point number by converting from another 
 * representation.
 *
 * @param this_obj a pointer to the fixed-point number
 * @param val the value to convert from
 *
 * @retval FACE_FIXED_NULL_PARAM if this_obj is null.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
///@{
FACE_fixed_return FACE_fixed_init_short(
  FACE_fixed*      this_obj,
  const FACE_short val
);
FACE_fixed_return FACE_fixed_init_long(
  FACE_fixed*     this_obj,
  const FACE_long val
);
FACE_fixed_return FACE_fixed_init_long_long(
  FACE_fixed*          this_obj,
  const FACE_long_long val
);
FACE_fixed_return FACE_fixed_init_unsigned_short(
  FACE_fixed*               this_obj,
  const FACE_unsigned_short val
);
FACE_fixed_return FACE_fixed_init_unsigned_long(
  FACE_fixed*              this_obj,
  const FACE_unsigned_long val
);
FACE_fixed_return FACE_fixed_init_unsigned_long_long(
  FACE_fixed*                   this_obj,
  const FACE_unsigned_long_long val
);
FACE_fixed_return FACE_fixed_init_short(
  FACE_fixed*      this_obj,
  const FACE_short val
);
FACE_fixed_return FACE_fixed_init_float(
  FACE_fixed*      this_obj,
  const FACE_float val
);
FACE_fixed_return FACE_fixed_init_double(
  FACE_fixed*       this_obj,
  const FACE_double val
);
FACE_fixed_return FACE_fixed_init_long_double(
  FACE_fixed*            this_obj,
  const FACE_long_double val
);

/**
 * @brief Initializes a fixed-point number with a string representation of a 
 * fixed-point literal.
 * @details (see \ref Conversion_Initializers)
 * A valid fixed-point literal string contains at least 1 and no more
 * than FACE_FIXED_DIGITS_MAX decimal digits, an optional decimal point, an 
 * optional leading +/-, and an optional trailing d/D. The string must be 
 * non-empty and null-terminated.
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p val is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p val is an invalid fixed-point
 *         literal
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
FACE_fixed_return FACE_fixed_init_str(FACE_fixed*      this_obj,
                                      const FACE_char* val);
///@}


/** @name Conversions */
///@{
/**
 * @brief Converts a fixed-point number to an integer number.
 * @details Digits to the right of the decimal point are truncated.
 *
 * @param this_obj a pointer to the fixed-point number source of the
 * conversion
 * @param dst a pointer to the destination of the conversion
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p dst is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is an invalid fixed-point 
 *         number.
 * @retval FACE_FIXED_TOO_LARGE if the magnitude of the fixed-point value
 *         does not fit in the destination of the conversion.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
FACE_fixed_return FACE_fixed_convert_integer(const FACE_fixed* this_obj,
                                             FACE_long_long*   dst);

/**
 * @brief Converts a fixed-point number to a floating-point number.
 *
 * @param this_obj a pointer to the fixed-point number source of the
 * conversion
 * @param dst a pointer to the destination of the conversion
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p dst is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is an invalid fixed-point 
 *         number.
 * @retval FACE_FIXED_TOO_LARGE if the magnitude of the fixed-point value
 *         does not fit in the destination of the conversion.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
FACE_fixed_return FACE_fixed_convert_floating(const FACE_fixed* this_obj,
                                              FACE_long_double* dst);

/**
 * @brief Converts a fixed-point number to a string representation of a
 * fixed-point literal.
 * @details The string starts with a '-' if negative and nothing if
 * positive, and always ends with a 'd'. Leading zeros are dropped, but
 * trailing fractional zeros are preserved. For example, a fixed-point
 * number with digits=4 and scale=2 with the value 1.1 is converted to
 * “1.10d”.) (See #FACE_fixed_init_str for more details on valid string
 * representations of fixed point literals.)
 *
 * @param this_obj a pointer to the fixed-point number source of the
 * conversion @param dst a pointer to the destination of the conversion
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p dst is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is an invalid fixed-point 
 *         number.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
FACE_fixed_return FACE_fixed_convert_str(const FACE_fixed* this_obj,
                                         FACE_char*        dst);
///@}


/**
 * @name Precision Modifiers
 * @brief Converts a fixed value to a new value with a specified scale.
 * @details If the value currently has more digits on the right than the new 
 * scale, the @p round function rounds away from values halfway or more the
 * to  the next absolute value for the new scale. If the value currently has
 * fewer or equal digits on the right relative to the new scale, both
 * functions return the value unmodified. The truncate function always
 * truncates the value towards zero. For example:
 *
 * f1: 0.1
 *   Round with scale 0 => 0
 *   Trunc with scale 0 => 0
 * f2: 0.05
 *   Round with scale 1 => 0.1
 *   Trunc with scale 1 => 0.0
 * f3: -0.005
 *   Round with scale 1 => -0.01
 *   Trunc with scale 1 =>  0.00
 *
 * @param this_obj a pointer to the source fixed-point number
 * @param result a pointer to the result
 * @param scale the new scale
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p result is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is an invalid fixed-point 
 *         number or if @p scale would cause @p result to be an invalid
 *         fixed-point number.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
///@{
FACE_fixed_return FACE_fixed_round(const FACE_fixed*         this_obj,
                                   FACE_fixed*               result,
                                   const FACE_unsigned_short scale
);
FACE_fixed_return FACE_fixed_truncate(const FACE_fixed*         this_obj,
                                      FACE_fixed*               result,
                                      const FACE_unsigned_short scale
);
///@}


/** 
 * @name Arithmetic Operations (Binary)
 * @brief Performs an arithmetic operation on two fixed-point numbers.
 * @details These functions calculate a result exactly using double
 * precision arithmetic and truncating the result to fit into the smallest
 * valid fixed-point number that can represent the result.
 * 
 * The following table summarizes the type resulting from an operation on
 * two fixed point numbers:
 *  - one with _digits=d1 and _scale=s1 (fixed<d1, s1>)
 *  - another with _digits=d2 and _scale=s2 (fixed<d2, s2>).
 * (s_inf denotes an arbitrary number of decimal places.)
 * 
 * Operation | Result (fixed<d, s>)
 * --------- | ------
 *     +     |  fixed<max(d1-s1,d2-s2) + max(s1,s2) + 1, max(s1,s2)>
 *     -     |  fixed<max(d1-s1,d2-s2) + max(s1,s2) + 1, max(s1,s2)>
 *     *     |  fixed<d1+d2, s1+s2>
 *     /     |  fixed<(d1-s1+s2) + s_inf, s_inf>
 * remainder |  fixed<max(s1,s2), max(s1,s2)>
 *
 * If the actual result is more than FACE_FIXED_DIGITS_MAX significant
 * digits, the result is retained as:
 *  fixed<d,s> => fixed<FACE_FIXED_DIGITS_MAX, FACE_FIXED_DIGITS_MAX-d+s>.
 *
 * Any of the three parameters may be equal (i.e. point to the same
 * fixed-point number in memory); local temporary copies ensure the result
 * is as expected.
 *
 * @param result a pointer the result of the operation.
 * @param operand1 a pointer to the first operand.
 * @param operand2 a pointer to the second operand.
 
 * @retval FACE_FIXED_NULL_PARAM if any parameter is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p operand1 or @p operand2 is an
 *         invalid fixed-point number.
 * @retval FACE_FIXED_TOO_LARGE if the magnitude of the actual result does
 *         not fit in a valid fixed-point number.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
///@{
/** @brief Calculates the sum of two fixed-point numbers. */
FACE_fixed_return FACE_fixed_add(FACE_fixed* result,
                                 const FACE_fixed* operand1,
                                 const FACE_fixed* operand2
);
/** @brief Calculates the difference of two fixed-point numbers. */
FACE_fixed_return FACE_fixed_subtract(FACE_fixed* result,
                                      const FACE_fixed* operand1,
                                      const FACE_fixed* operand2
);
/** @brief Calculates the product of two fixed-point numbers. */
FACE_fixed_return FACE_fixed_multiply(FACE_fixed* result,
                                      const FACE_fixed* operand1,
                                      const FACE_fixed* operand2
);
/** @brief Calculates the quotient of two fixed-point numbers. */
FACE_fixed_return FACE_fixed_divide(FACE_fixed* result,
                                    const FACE_fixed* operand1,
                                    const FACE_fixed* operand2
);
/**
 * @brief Calculates the remainder after division of two fixed-point
 * numbers.
 */
FACE_fixed_return FACE_fixed_remainder(FACE_fixed* result,
                                       const FACE_fixed* operand1,
                                       const FACE_fixed* operand2);
///@}


/** 
 * @name Arithmetic Operations (In-place) 
 * @brief Performs an arithmetic operation on a fixed-point number.
 *
 * @param this_obj a pointer to the fixed-point number.
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is an invalid fixed-point 
 *         number.
 * @retval FACE_FIXED_TOO_LARGE if the magnitude of the operation result
 *         does not fit in a valid fixed-point number.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
///@{
/** @brief Increments a fixed-point number by 1. */
FACE_fixed_return FACE_fixed_inc(FACE_fixed* this_obj);
/** @brief Decrements a fixed-point number by 1. */
FACE_fixed_return FACE_fixed_dec(FACE_fixed* this_obj);
/** @brief Makes a fixed-point number positive. */
FACE_fixed_return FACE_fixed_pos(FACE_fixed* this_obj);
/** @brief Makes a fixed-point number negative. */
FACE_fixed_return FACE_fixed_neg(FACE_fixed* this_obj);
///@}

/**
 * @brief Indicates whether or not a fixed-point value is 0.
 * @details @p result will be set to 0 if the value is 0, and 1 otherwise
 *
 * @param this_obj a pointer to the fixed-point number.
 * @param result a pointer to the result
 *
 * @retval FACE_FIXED_NULL_THIS if @p this_obj is null.
 * @retval FACE_FIXED_NULL_PARAM if @p result is null.
 * @retval FACE_FIXED_INVALID_PARAM if @p this_obj is an invalid fixed-point 
 *         number.
 * @retval FACE_FIXED_NO_ERROR otherwise.
 */
FACE_fixed_return FACE_fixed_not(const FACE_fixed* this_obj,
                                 FACE_boolean*     result);
 
/** @name Comparison Operations
 * @brief Performs comparisons of fixed-point numbers.
 * @details @p return_code will be:
 *  - FACE_FIXED_NULL_PARAM if any parameter is null.
 *  - FACE_FIXED_INVALID_PARAM if @p lhs or @p rhs is an invalid fixed-point 
 *    number.
 *  - FACE_FIXED_NO_ERROR otherwise.
 *
 * @param lhs the left-hand side of the comparison.
 * @param rhs the right-hand side of the comparison.
 * @param return_code pointer to a return code resulting from the function's 
 *        invocation.
 */
///@{
/** @brief Returns 1 if lhs greater than rhs; 0 otherwise. */
FACE_boolean FACE_fixed_gt(const FACE_fixed*  lhs,
                           const FACE_fixed*  rhs,
                           FACE_fixed_return* return_code
);
/** @brief Returns 1 if lhs less than rhs; 0 otherwise. */
FACE_boolean FACE_fixed_lt(const FACE_fixed*  lhs,
                           const FACE_fixed*  rhs,
                           FACE_fixed_return* return_code
);
/** @brief Returns 1 if lhs greater than or equal to rhs; 0 otherwise. */
FACE_boolean FACE_fixed_gteq(const FACE_fixed*  lhs,
                             const FACE_fixed*  rhs,
                             FACE_fixed_return* return_code
);
/** @brief Returns 1 if lhs less than or equal to rhs; 0 otherwise. */
FACE_boolean FACE_fixed_lteq(const FACE_fixed*  lhs,
                             const FACE_fixed*  rhs,
                             FACE_fixed_return* return_code
);
/** @brief Returns 1 if lhs is equal to rhs; 0 otherwise. */
FACE_boolean FACE_fixed_eq(const FACE_fixed*  lhs,
                           const FACE_fixed*  rhs,
                           FACE_fixed_return* return_code
);
/** @brief Returns 1 if lhs is not equal to rhs; 0 otherwise. */
FACE_boolean FACE_fixed_neq(const FACE_fixed*  lhs,
                            const FACE_fixed*  rhs,
                            FACE_fixed_return* return_code);
///@}


#endif /* _FACE_FIXED_H */
