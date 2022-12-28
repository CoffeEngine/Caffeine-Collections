#ifndef CAFFEINE_TEST_DATA_H
#define CAFFEINE_TEST_DATA_H

#include <stdint.h>
#include "caffeine_memory.h"
#include "caffeine_core.h"
#include <math.h>
#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

#define USE_VEC3


#ifdef USE_VEC3

typedef struct
{
	int x, y, z;
}vec3;


typedef vec3 test_data;

#endif // USE_INT

#ifdef USE_INT

typedef int test_data;

#endif // USE_INT


extern const uint64_t INI_LEN;
extern const uint64_t DATA_SIZE;

#pragma region DATA FUNCTIONS

test_data data_new();
test_data data_new_at_index(uint64_t i);
void data_delete(test_data* ptr);
void data_print(test_data data);
bool data_equals(test_data a, test_data b);


#pragma endregion

#pragma region DATA CALLBACKS

bool filter(const void* const data, uint64_t index, uint64_t data_size);
void map(const void* const data, void* out, uint64_t index);
void foreach(void* in, uint64_t index);
cff_cmp_e compare(const void* const a, const void* const b, uint64_t data_size);
cff_cmp_e compare_reverse(const void* const a, const void* const b, uint64_t data_size);

bool validate_filter(test_data data, uint64_t index);
bool validate_map(test_data data_from, int data_to, uint64_t index);
bool validate_foreach(test_data data, uint64_t index);

#pragma endregion

#pragma region UTILS

#define ASSERT_EQUALS(a,b) munit_assert((data_equals(a,b) == true))
#define ASSERT_LESS(a,b) munit_assert((data_compare(a,b) == CFF_LESS))
#define ASSERT_GREATER(a,b) munit_assert((data_equals(a,b) == CFF_GREATER))
#define ASSERT_LESS_EQ(a,b) { cff_cmp_e ___assert_less_eq_result = data_compare(a, b); munit_assert( ___assert_less_eq_result == CFF_LESS ||  ___assert_less_eq_result == CFF_EQUALS );}
#define ASSERT_GREATER_EQ(a,b) { cff_cmp_e ___assert_less_eq_result = data_compare(a, b); munit_assert( ___assert_less_eq_result == CFF_GREATER ||  ___assert_less_eq_result == CFF_EQUALS );}

#define TEST(FUNC) { "/"#FUNC, test_##FUNC, test_setup, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL }
#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], void* munit_data)
#define SKIP_ON_ERR(EXP) {cff_err_e err = (EXP); if (err != CFF_NONE_ERR) { return MUNIT_ERROR; }}


#pragma endregion



#endif // !CAFFEINE_TEST_VEC3_H
