/** @defgroup Assertions
    @file caffeine_assertions.h
    @brief Defines assertion macros.

    This file defines macros for both parameter and general purpose validation with a friendly message.
    The assertions will be defined only on debug mode
*/

#ifndef CAFFEINE_UTILS_ASSERTIONS
#define CAFFEINE_UTILS_ASSERTIONS
#include <assert.h>
#include <stdio.h>
#include "caffeine_macros.h"


#ifdef NDEBUG

#define cff_assert_msg(EXP, MSG)
#define cff_assert_param_not_null(PARAM)
#define cff_assert_param_not_zero(PARAM)

#define cff_assert_param_equals(PARAM,VALUE)
#define cff_assert_param_greater(PARAM,VALUE)
#define cff_assert_param_greater_eq(PARAM,VALUE)

#define cff_assert_param_less(PARAM,VALUE)
#define cff_assert_param_less_eq(PARAM,VALUE)

#define cff_assert_not_null(PARAM)
#define cff_assert_not_zero(PARAM)

#define cff_assert_equals(PARAM,VALUE)
#define cff_assert_greater(PARAM,VALUE)
#define cff_assert_greater_eq(PARAM,VALUE)

#define cff_assert_less(PARAM,VALUE)
#define cff_assert_less_eq(PARAM,VALUE)

#else

/** 
 * @ingroup Assertions
 * @def cff_assert_msg(EXP,MSG)
    @brief Asserts the expression @a EXP and case it evaluates to false prints the message @a MSG on STDOUT.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_msg(EXP, MSG) for (unsigned char __assertion_flag__ = (EXP); !(__assertion_flag__) ; assert(__assertion_flag__) ) { printf("[%s::%s]@n %s@n@n",CFF_FILENAME,__FUNCTION__,MSG); }

/** 
 * @ingroup Assertions
 * @def cff_assert_param_not_null(PARAM)
    @brief Asserts the value of @a PARAM is not NULL.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_param_not_null(PARAM) cff_assert_msg((void*)(PARAM) != NULL, "Invalid Parameter Value: " #PARAM " couldn't be null" )

/** 
 * @ingroup Assertions
 * @def cff_assert_param_not_zero(PARAM)
    @brief Asserts the value of @a PARAM is not 0.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_param_not_zero(PARAM) cff_assert_msg((PARAM) != 0, "Invalid Parameter Value: " #PARAM " couldn't be 0" )

/** 
 * @ingroup Assertions
 * @def cff_assert_param_equals(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is equals to @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_param_equals(PARAM,VALUE) cff_assert_msg((PARAM) == (VALUE), "Invalid Parameter Value: " #PARAM " shout be equals to " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_param_greater(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is greater than @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_param_greater(PARAM,VALUE) cff_assert_msg((PARAM) > (VALUE), "Invalid Parameter Value: " #PARAM " shout be greater than " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_param_greater_eq(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is greater or equals to @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_param_greater_eq(PARAM,VALUE) cff_assert_msg((PARAM) >= (VALUE), "Invalid Parameter Value: " #PARAM " shout be equal or greater than " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_param_less(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is less than @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_param_less(PARAM,VALUE) cff_assert_msg((PARAM) < (VALUE), "Invalid Parameter Value: " #PARAM " shout be less than " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_param_less_eq(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is less or equals to @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_param_less_eq(PARAM,VALUE) cff_assert_msg((PARAM) <= (VALUE), "Invalid Parameter Value: " #PARAM " shout be equal or less than " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_not_null(PARAM)
    @brief Asserts the value of @a PARAM is not NULL.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_not_null(PARAM) cff_assert_msg((void*)(PARAM) != NULL, "Invalid Value: " #PARAM " couldn't be null" )

/** 
 * @ingroup Assertions
 * @def cff_assert_not_zero(PARAM)
    @brief Asserts the value of @a PARAM is not 0.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_not_zero(PARAM) cff_assert_msg((PARAM) != 0, "Invalid Value: " #PARAM " couldn't be 0" )

/** 
 * @ingroup Assertions
 * @def cff_assert_equals(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is equals to @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_equals(PARAM,VALUE) cff_assert_msg((PARAM) == (VALUE), "Invalid Value: " #PARAM " shout be equals to " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_greater(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is greater than @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_greater(PARAM,VALUE) cff_assert_msg((PARAM) > (VALUE), "Invalid Value: " #PARAM " shout be greater than " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_greater_eq(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is greater or equals to @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_greater_eq(PARAM,VALUE) cff_assert_msg((PARAM) >= (VALUE), "Invalid Value: " #PARAM " shout be equal or greater than " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_less(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is less than @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_less(PARAM,VALUE) cff_assert_msg((PARAM) < (VALUE), "Invalid Value: " #PARAM " shout be less than " #VALUE )

/** 
 * @ingroup Assertions
 * @def cff_assert_less_eq(PARAM,VALUE)
    @brief Asserts the value of @a PARAM is less or equals to @a VALUE.

    @warning Only when NDEBUG is not defined.
*/
#define cff_assert_less_eq(PARAM,VALUE) cff_assert_msg((PARAM) <= (VALUE), "Invalid Value: " #PARAM " shout be equal or less than " #VALUE )

#endif

#endif