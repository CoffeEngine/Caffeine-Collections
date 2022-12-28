#include "caffeine_ordered_vector.h"
#include "test_defs.h"
#include <math.h>


static cff_cmp_e int_cmp(const void* const a, const void* const b, uint64_t data_size) {
	int a1 = *(int*)a;
	int b1 = *(int*)b;

	if (a == b) return CFF_EQUALS;
	if (a < b) return CFF_LESS;
	return CFF_GREATER;
}

TESTDEF(ordered_vector_create) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	cff_ordered_vector_create(ordered_vector, DATA_SIZE,compare, INI_LEN, NULL);

	munit_assert_not_null((void*)ordered_vector->buffer);
	munit_assert(ordered_vector->count == 0);
	munit_assert(ordered_vector->lenght == INI_LEN);
	munit_assert(ordered_vector->data_size == DATA_SIZE);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_free) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	cff_ordered_vector_free(ordered_vector, NULL);

	munit_assert_null((void*)ordered_vector->buffer);
	munit_assert(ordered_vector->count == 0);
	munit_assert(ordered_vector->lenght == 0);
	munit_assert(ordered_vector->data_size == 0);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_resize) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	int n_size = (int)INI_LEN * 2;
	cff_ordered_vector_resize(ordered_vector, n_size, NULL);

	munit_assert(ordered_vector->count == 0);
	munit_assert(ordered_vector->lenght == n_size);
	munit_assert(ordered_vector->data_size == DATA_SIZE);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_get) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	vec3 value = data_new();

	*((vec3*)ordered_vector->buffer) = value;
	ordered_vector->count = 1;

	vec3 out = { 0 };
	cff_ordered_vector_get(ordered_vector, 0, (uintptr_t)&out);

	ASSERT_EQUALS(value, out);

	return MUNIT_OK;
}


TESTDEF(ordered_vector_remove) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	vec3 value1 = data_new();
	vec3 value2 = data_new();

	cff_ordered_vector_add(ordered_vector, (uintptr_t)&value1, NULL);
	cff_ordered_vector_add(ordered_vector, (uintptr_t)&value2, NULL);

	cff_ordered_vector_remove(ordered_vector, 0, NULL);

	vec3 out = { 0 };
	cff_ordered_vector_get(ordered_vector, 0, (uintptr_t)&out);
	ASSERT_EQUALS(value1, out);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_copy) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	cff_ordered_vector tmp_vec;
	for (size_t i = 0; i < INI_LEN - 1; i++)
	{
		vec3 value = data_new();

		cff_ordered_vector_add(ordered_vector, (uintptr_t)&value, NULL);
	}

	cff_ordered_vector_create(&tmp_vec, ordered_vector->data_size, compare, INI_LEN / 2, NULL);
	cff_ordered_vector_copy(ordered_vector, &tmp_vec, 0, INI_LEN / 2, NULL);

	for (size_t i = 0; i < INI_LEN / 2; i++)
	{
		vec3 out1 = { 0 }, out2 = { 0 };

		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&out1);
		cff_ordered_vector_get(&tmp_vec, i, (uintptr_t)&out2);

		ASSERT_EQUALS(out1, out2);
	}

	cff_ordered_vector_free(&tmp_vec, NULL);
	return MUNIT_OK;
}

TESTDEF(ordered_vector_clone) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	cff_ordered_vector tmp_vec;
	for (size_t i = 0; i < INI_LEN - 1; i++)
	{
	
		vec3 value = data_new();

		cff_ordered_vector_add(ordered_vector, (uintptr_t)&value, NULL);
	}
	cff_ordered_vector_create(&tmp_vec, ordered_vector->data_size, compare, INI_LEN, NULL);
	cff_ordered_vector_clone(ordered_vector, &tmp_vec, NULL);

	for (size_t i = 0; i < INI_LEN - 1; i++)
	{
		vec3 out1 = { 0 }, out2 = { 0 };

		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&out1);
		cff_ordered_vector_get(&tmp_vec, i, (uintptr_t)&out2);

		ASSERT_EQUALS(out1, out2);
	}

	cff_ordered_vector_free(&tmp_vec, NULL);
	return MUNIT_OK;
}

TESTDEF(ordered_vector_fill) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	vec3 data = data_new();
	cff_ordered_vector_fill(ordered_vector, (uintptr_t)&data);

	for (size_t i = 0; i < ordered_vector->count; i++)
	{
		vec3 out = { 0 };
		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&out);
		ASSERT_EQUALS(data, out);
	}

	return MUNIT_OK;
}

TESTDEF(ordered_vector_join) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	cff_ordered_vector ordered_vector2;
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}
	cff_ordered_vector_create(&ordered_vector2, DATA_SIZE, compare, INI_LEN, NULL);
	for (int i = (int)INI_LEN; i < (int)INI_LEN * 2; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(&ordered_vector2, (uintptr_t)&data, NULL);
	}

	cff_ordered_vector_join(ordered_vector, &ordered_vector2, NULL);

	for (int i = 0; i < (int)INI_LEN * 2; i++)
	{
		vec3 data = { 0 };
		vec3 expected = data_new_at_index(i);
		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&data);
		ASSERT_EQUALS(data, expected);
	}

	cff_ordered_vector_free(&ordered_vector2, NULL);

	return MUNIT_OK;
}


TESTDEF(ordered_vector_filter) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	cff_ordered_vector ordered_vector2;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	cff_ordered_vector_filter(ordered_vector, filter, &ordered_vector2, NULL);

	for (size_t i = 0; i < ordered_vector2.count; i++)
	{
		vec3 out = { 0 };
		cff_ordered_vector_get(&ordered_vector2, i, (uintptr_t)&out);

		munit_assert(validate_filter(out, i));
	}

	if (ordered_vector2.count > 0) cff_ordered_vector_free(&ordered_vector2, NULL);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_add) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	munit_assert(ordered_vector->lenght == INI_LEN * 2);

	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		vec3 out = { 0 };
		vec3 expected = data_new_at_index(i);
		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&out);
		ASSERT_EQUALS(out, expected);
	}

	return MUNIT_OK;
}


TESTDEF(ordered_vector_pop_back) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	munit_assert(ordered_vector->lenght == INI_LEN * 2);

	for (int i = (int)(INI_LEN * 2) - 1; i >= 0; --i)
	{
		vec3 out = { 0 };
		vec3 expected = data_new_at_index(i);
		cff_ordered_vector_pop_back(ordered_vector, (uintptr_t)&out, NULL);
		ASSERT_EQUALS(out, expected);
	}

	return MUNIT_OK;
}

TESTDEF(ordered_vector_pop_front) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	munit_assert(ordered_vector->lenght == INI_LEN * 2);

	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		vec3 out = {0};
		vec3 expected = data_new_at_index(i);
		cff_ordered_vector_pop_front(ordered_vector, (uintptr_t)&out, NULL);
		ASSERT_EQUALS(out, expected);
	}

	return MUNIT_OK;
}

TESTDEF(ordered_vector_map) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	cff_ordered_vector len_ordered_vector;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new();
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	cff_ordered_vector_map(ordered_vector, map, &len_ordered_vector,int_cmp, sizeof(float), NULL);

	for (size_t i = 0; i < INI_LEN; i++) {
		vec3 v = { 0 };
		int l = { 0 };

		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&v);
		cff_ordered_vector_get(&len_ordered_vector, i, (uintptr_t)&l);

		munit_assert(validate_map(v, l, i));
	}

	cff_ordered_vector_free(&len_ordered_vector, NULL);
	return MUNIT_OK;
}

TESTDEF(ordered_vector_foreach) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	cff_ordered_vector_foreach(ordered_vector, foreach);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = { 0 };
		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&data);
		munit_assert(validate_foreach(data, i));
		
	}

	return MUNIT_OK;
}

TESTDEF(ordered_vector_sort) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	cff_ordered_vector_sort(ordered_vector, compare);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = { 0 };
		vec3 expected = data_new_at_index(i);
		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&data);
		ASSERT_EQUALS(data, expected);
	}

	return MUNIT_OK;
}

TESTDEF(ordered_vector_clear) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	cff_ordered_vector_clear(ordered_vector);

	munit_assert(ordered_vector->count == 0);

	for (int i = (int)INI_LEN; i < INI_LEN * 2; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		vec3 data = { 0 };
		cff_ordered_vector_get(ordered_vector, i, (uintptr_t)&data);

		munit_assert(data.x = (int)(i + INI_LEN));
	}

	return MUNIT_OK;
}

TESTDEF(ordered_vector_equal) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	cff_ordered_vector ordered_vector2;

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	cff_ordered_vector_clone(ordered_vector, &ordered_vector2, NULL);

	uint8_t eq = cff_ordered_vector_equal(ordered_vector, &ordered_vector2);

	munit_assert(eq);

	cff_ordered_vector_free(&ordered_vector2, NULL);
	return MUNIT_OK;
}

TESTDEF(ordered_vector_find) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 1; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	vec3 data_ok = data_new_at_index(1);
	uint64_t ok_index = -1;

	vec3 data_nok = data_new_at_index(0);
	uint64_t nok_index = -1;

	uint8_t f_ok = cff_ordered_vector_find(ordered_vector, (uintptr_t)&data_ok, &ok_index);
	uint8_t f_nok = cff_ordered_vector_find(ordered_vector, (uintptr_t)&data_nok, &nok_index);

	munit_assert(f_ok);
	munit_assert(ok_index == 0);

	munit_assert(!f_nok);
	munit_assert(nok_index == -1);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_find_cmp) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 1; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	vec3 data_ok = data_new_at_index(1);
	uint64_t ok_index = -1;

	vec3 data_nok = data_new_at_index(0);
	uint64_t nok_index = -1;

	uint8_t f_ok = cff_ordered_vector_find_cmp(ordered_vector, (uintptr_t)&data_ok, &ok_index, compare);
	uint8_t f_nok = cff_ordered_vector_find_cmp(ordered_vector, (uintptr_t)&data_nok, &nok_index, compare);

	munit_assert(f_ok);
	munit_assert(ok_index == 0);

	munit_assert(!f_nok);
	munit_assert(nok_index == -1);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_count) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i % 2);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	vec3 data = data_new_at_index(0);

	vec3 data2 = data_new_at_index(3);

	uint64_t count = cff_ordered_vector_count(ordered_vector, (uintptr_t)&data);
	uint64_t count2 = cff_ordered_vector_count(ordered_vector, (uintptr_t)&data2);

	munit_assert(count == INI_LEN/2);
	munit_assert(count2 == 0);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_count_cmp) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i % 2);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	vec3 data = data_new_at_index(0);

	vec3 data2 = data_new_at_index(3);

	uint64_t count = cff_ordered_vector_count_cmp(ordered_vector, (uintptr_t)&data, compare);
	uint64_t count2 = cff_ordered_vector_count_cmp(ordered_vector, (uintptr_t)&data2, compare);

	munit_assert(count == INI_LEN/2);
	munit_assert(count2 == 0);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_any) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	vec3 data = data_new_at_index(0);

	uint8_t result = cff_ordered_vector_any(ordered_vector, (uintptr_t)&data);

	munit_assert(result);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_any_cmp) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		vec3 data = data_new_at_index(i);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	vec3 data = data_new_at_index(0);

	uint8_t result = cff_ordered_vector_any_cmp(ordered_vector, (uintptr_t)&data, compare);

	munit_assert(result);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_all) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(5);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	vec3 data = data_new_at_index(5);

	vec3 data2 = data_new_at_index(0);

	uint8_t result1 = cff_ordered_vector_all(ordered_vector, (uintptr_t)&data);
	uint8_t result2 = cff_ordered_vector_all(ordered_vector, (uintptr_t)&data2);

	munit_assert(result1);
	munit_assert(!result2);

	return MUNIT_OK;
}

TESTDEF(ordered_vector_all_cmp) {
	cff_ordered_vector* ordered_vector = (cff_ordered_vector*)munit_data;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = data_new_at_index(5);
		cff_ordered_vector_add(ordered_vector, (uintptr_t)&data, NULL);
	}

	vec3 data = data_new_at_index(5);

	vec3 data2 = data_new_at_index(0);

	uint8_t result1 = cff_ordered_vector_all_cmp(ordered_vector, (uintptr_t)&data, compare);
	uint8_t result2 = cff_ordered_vector_all_cmp(ordered_vector, (uintptr_t)&data2, compare);

	munit_assert(result1);
	munit_assert(!result2);

	return MUNIT_OK;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_ordered_vector* ordered_vector = malloc(sizeof(cff_ordered_vector));
	if (ordered_vector) *ordered_vector = (cff_ordered_vector){ 0 };
	return ordered_vector;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_ordered_vector* ordered_vector = malloc(sizeof(cff_ordered_vector));
	cff_ordered_vector_create(ordered_vector, DATA_SIZE,compare, INI_LEN, NULL);
	return ordered_vector;
}

static void test_tear_down(void* fixture) {
	cff_ordered_vector_free(fixture, NULL);
	free(fixture);
}

int test_ordered_vector(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/ordered_vector_create", test_ordered_vector_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		{ "/ordered_vector_free", test_ordered_vector_free, test_setup, NULL, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(ordered_vector_resize),
		TEST(ordered_vector_get),
		TEST(ordered_vector_remove),
		TEST(ordered_vector_copy),
		TEST(ordered_vector_clone),
		TEST(ordered_vector_fill),
		TEST(ordered_vector_join),
		TEST(ordered_vector_filter),
		TEST(ordered_vector_add),
		TEST(ordered_vector_pop_back),
		TEST(ordered_vector_pop_front),
		TEST(ordered_vector_map),
		TEST(ordered_vector_foreach),
		TEST(ordered_vector_sort),
		TEST(ordered_vector_clear),
		TEST(ordered_vector_find),
		TEST(ordered_vector_find_cmp),
		TEST(ordered_vector_count),
		TEST(ordered_vector_count_cmp),
		TEST(ordered_vector_any),
		TEST(ordered_vector_any_cmp),
		TEST(ordered_vector_all),
		TEST(ordered_vector_all_cmp),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/ordered_vector", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}