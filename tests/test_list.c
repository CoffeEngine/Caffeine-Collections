#include <stdio.h>
#include "caffeine_list.h"
#include "caffeine_memory.h"

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

typedef struct
{
	int x, y, z;
}vec3;

static const uint64_t INI_LEN = 13;
static const uint64_t DATA_SIZE = sizeof(vec3);

#define TEST(FUNC) { "/"#FUNC, test_##FUNC, test_setup, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL }

#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], cff_list* list)

#define SKIP_ON_ERR(EXP) {cff_err_e err = (EXP); if (err != CFF_NONE_ERR) { return MUNIT_SKIP; }}


static void print_vec3(void* data, uint64_t i) {
	vec3* vec = (vec3*)data;
	printf("{ %d %d %d }, ", vec->x, vec->y, vec->z);
}

static void assert_vec3(vec3 a, vec3 b) {
	munit_assert(a.x == b.x && a.y == b.y && a.z == b.z);
}

static void print_list(cff_list* list) {
	cff_list_foreach(list, print_vec3);
	printf("\n");
}

static void list_arange(cff_list* list, int start, int end) {
	for (int i = start; i < end; i++)
	{
		vec3 data = { .x = i,.y = i,.z = i };
		cff_list_add(list, (uintptr_t)(&data), NULL);
	}
}

#pragma region CALLBACKS

static cff_cmp_e vec_cmp(void* ptr_a, void* ptr_b, uint64_t data_size) {
	vec3* a = (vec3*)ptr_a;
	vec3* b = (vec3*)ptr_b;

	if (a->x == b->x && a->y == b->y && a->z == b->z) {
		return CFF_EQUALS;
	}

	if (a->x < b->x) return CFF_LESS;
	if (a->x > b->x) return CFF_GREATER;

	return CFF_NOT_EQUAL;
}

static bool filter_even(void* data, uint64_t index, uint64_t data_size) {
	vec3* vec = (vec3*)data;
	if (vec->x % 2 == 0) return true;
	return false;
}

static void foreach_func(void* data, uint64_t i) {
	vec3 vec = *(vec3*)data;
	vec3 other = { .x = (int)i * 3,.y = (int)i * 5,.z = (int)i * 7 };
	assert_vec3(vec, other);
}

static void map_vec(vec3* from_ptr, int* to_ptr, uint64_t index) {
	vec3* from = (vec3*)from_ptr;
	int* to = (int*)to_ptr;

	*to = from->x + from->y + from->z;
}

#pragma endregion

TESTDEF(list_create) {
	cff_list_create(list, DATA_SIZE);

	munit_assert_int64(list->data_size, == , DATA_SIZE);
	return MUNIT_OK;
}

TESTDEF(list_add) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}

	caffeine_list_bucket* bucket = list->list_start;

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		vec3 found = *((vec3*)bucket->data_ptr);
		assert_vec3(data, found);
		bucket = bucket->next_bucket;
	}

	return MUNIT_OK;
}

TESTDEF(list_set) {
	list_arange(list, 0, INI_LEN);

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		cff_list_set(list, i, (uintptr_t)(&data), NULL);
	}

	caffeine_list_bucket* bucket = list->list_start;
	int cc = 0;
	while (bucket != NULL)
	{
		vec3 data = { .x = cc * 3,.y = cc * 5,.z = cc * 7 };
		vec3 found = *((vec3*)bucket->data_ptr);
		assert_vec3(data, found);
		bucket = bucket->next_bucket;
		cc++;
	}

	return MUNIT_OK;
}

TESTDEF(list_insert_front) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		SKIP_ON_ERR(cff_list_insert(list, 0, (uintptr_t)(&data), NULL));
	}

	caffeine_list_bucket* bucket = list->list_start;

	for (int i = INI_LEN - 1; i >= 0; i--)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		vec3 found = *((vec3*)bucket->data_ptr);
		assert_vec3(data, found);
		bucket = bucket->next_bucket;
	}

	return MUNIT_OK;
}

TESTDEF(list_insert_mid) {
	list_arange(list, 0, 5);

	int index_offset = 3;
	for (size_t i = 0; i < 5; i++)
	{
		vec3 data = { .x = 0,.y = 0,.z = 0 };
		SKIP_ON_ERR(cff_list_insert(list, index_offset + i, (uintptr_t)(&data), NULL));
	}

	caffeine_list_bucket* bucket = list->list_start;

	for (int i = 0; i < list->count; i++)
	{
		if (i >= index_offset && i < index_offset + 5) {
			vec3 data = { .x = 0,.y = 0,.z = 0 };
			vec3 found = *((vec3*)bucket->data_ptr);
			assert_vec3(data, found);
		}

		bucket = bucket->next_bucket;
	}

	return MUNIT_OK;
}

TESTDEF(list_insert_back) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		SKIP_ON_ERR(cff_list_insert(list, i, (uintptr_t)(&data), NULL));
	}

	caffeine_list_bucket* bucket = list->list_start;

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		vec3 found = *((vec3*)bucket->data_ptr);
		assert_vec3(data, found);
		bucket = bucket->next_bucket;
	}

	return MUNIT_OK;
}

TESTDEF(list_get) {
	list_arange(list, 0, INI_LEN);

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i,.y = i,.z = i };
		vec3 found;
		cff_list_get(list, i, &found);
		assert_vec3(data, found);
	}

	return MUNIT_OK;
}

TESTDEF(list_first) {
	list_arange(list, 5, INI_LEN);
	int idx = 5;
	vec3 data = { .x = idx,.y = idx ,.z = idx };
	vec3 found;
	cff_list_first(list, &found);
	assert_vec3(data, found);

	return MUNIT_OK;
}

TESTDEF(list_last) {
	list_arange(list, 0, INI_LEN);
	int idx = INI_LEN - 1;
	vec3 data = { .x = idx,.y = idx,.z = idx };
	vec3 found;
	cff_list_last(list, &found);
	assert_vec3(data, found);

	return MUNIT_OK;
}

TESTDEF(list_remove) {
	list_arange(list, 0, INI_LEN);

	cff_list_remove(list, 1, NULL);

	vec3 out;

	cff_list_get(list, 1, &out);

	munit_assert(out.x == 2);

	return MUNIT_OK;
}

TESTDEF(list_clear) {
	list_arange(list, 0, INI_LEN);

	cff_list_clear(list, NULL);

	munit_assert(list->count == 0);
	munit_assert(list->list_start == NULL);
	munit_assert(list->list_end == NULL);

	return MUNIT_OK;
}

TESTDEF(list_join) {
	cff_list aux_list;

	cff_list_create(&aux_list, DATA_SIZE);

	list_arange(list, 0, INI_LEN / 2);
	list_arange(&aux_list, INI_LEN / 2, INI_LEN);

	cff_list_join(list, &aux_list);

	caffeine_list_bucket* bucket = list->list_start;
	int cc = 0;
	while (bucket != NULL)
	{
		vec3 data = { .x = cc ,.y = cc ,.z = cc };
		vec3 found = *((vec3*)bucket->data_ptr);
		assert_vec3(data, found);
		bucket = bucket->next_bucket;
		cc++;
	}

	munit_assert(aux_list.count == 0);
	munit_assert(aux_list.data_size == 0);
	munit_assert(aux_list.list_start == NULL);
	munit_assert(aux_list.list_end == NULL);

	return MUNIT_OK;
}

TESTDEF(list_foreach) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		cff_list_add(list, (uintptr_t)(&data), NULL);
	}

	cff_list_foreach(list, foreach_func);

	return MUNIT_OK;
}

TESTDEF(list_copy) {
	cff_list aux_list;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_copy(list, &aux_list, INI_LEN / 2, INI_LEN/2, NULL));

	for (size_t i = 0; i < INI_LEN / 2; i++)
	{
		vec3 a, b;

		cff_list_get(list, i + (INI_LEN / 2), &a);
		cff_list_get(&aux_list, i, &b);

		assert_vec3(a, b);
	}

	cff_list_clear(&aux_list, NULL);
	return MUNIT_OK;
}

TESTDEF(list_clone) {
	cff_list aux_list;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 a, b;

		cff_list_get(list, i, &a);
		cff_list_get(&aux_list, i, &b);

		assert_vec3(a, b);
	}

	cff_list_clear(&aux_list, NULL);
	return MUNIT_OK;
}

TESTDEF(list_filter) {
	cff_list aux_list;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_filter(list, filter_even, &aux_list, NULL));

	for (size_t i = 0; i < aux_list.count; i++)
	{
		vec3 out;
		cff_list_get(&aux_list, i, &out);

		munit_assert(out.x % 2 == 0);
	}

	cff_list_clear(&aux_list, NULL);

	return MUNIT_OK;
}

TESTDEF(list_map) {
	cff_list aux_list;
	int out;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, sizeof(int));

	SKIP_ON_ERR(cff_list_map(list, map_vec, &aux_list, sizeof(int), NULL));



	for (size_t i = 0; i < INI_LEN; i++)
	{
		cff_list_get(&aux_list, i, &out);
		munit_assert(out == i * 3);
	}

	cff_list_clear(&aux_list, NULL);

	return MUNIT_OK;
}

TESTDEF(list_equal_true) {
	cff_list aux_list;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));

	uint8_t eq = cff_list_equal(list, &aux_list);

	cff_list_clear(&aux_list, NULL);

	munit_assert(eq);

	return MUNIT_OK;
}

TESTDEF(list_equal_false) {
	cff_list aux_list;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));
	vec3 s = { 0 };
	cff_list_set(&aux_list, 2, &s);

	uint8_t eq = cff_list_equal(list, &aux_list);

	cff_list_clear(&aux_list, NULL);

	munit_assert(!eq);

	return MUNIT_OK;
}

TESTDEF(list_equal_cpm_true) {
	cff_list aux_list;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));

	uint8_t eq = cff_list_equal_cmp(list, &aux_list, vec_cmp);

	cff_list_clear(&aux_list, NULL);

	munit_assert(eq);

	return MUNIT_OK;
}

TESTDEF(list_equal_cmp_false) {
	cff_list aux_list;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));
	vec3 s = { 0 };
	cff_list_set(&aux_list, 2, &s);

	uint8_t eq = cff_list_equal_cmp(list, &aux_list, vec_cmp);

	cff_list_clear(&aux_list, NULL);

	munit_assert(!eq);

	return MUNIT_OK;
}

TESTDEF(list_find) {
	list_arange(list, 0, INI_LEN);

	vec3 s = { .x = 3, .y = 3, .z = 3 };
	vec3 out;
	uint64_t idx;
	cff_list_find(list, &s, &idx, &out);

	munit_assert(idx = 3);
	assert_vec3(s, out);

	return MUNIT_OK;
}

TESTDEF(list_find_cmp) {
	list_arange(list, 0, INI_LEN);

	vec3 s = { .x = 3, .y = 3, .z = 3 };
	vec3 out;
	uint64_t idx;
	cff_list_find_cmp(list, &s, &idx, &out, vec_cmp);

	munit_assert(idx = 3);
	assert_vec3(s, out);

	return MUNIT_OK;
}

TESTDEF(list_count) {
	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cc += i % 2;
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint64_t count = cff_list_count(list, (uintptr_t)(&data));
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(list_count_cmp) {
	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cc += i % 2;
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint64_t count = cff_list_count_cmp(list, (uintptr_t)(&data), vec_cmp);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(list_any_true) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_list_any(list, (uintptr_t)(&data));
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(list_any_cmp_true) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_list_any_cmp(list, (uintptr_t)(&data), vec_cmp);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(list_all_false) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_list_all(list, (uintptr_t)(&data));
	munit_assert(!exist);
	return MUNIT_OK;
}

TESTDEF(list_all_cmp_false) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_list_all_cmp(list, (uintptr_t)(&data), vec_cmp);
	munit_assert(!exist);
	return MUNIT_OK;
}

TESTDEF(list_any_false) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = 2,.y = 2,.z = 2 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_list_any(list, (uintptr_t)(&data));
	munit_assert(!exist);
	return MUNIT_OK;
}

TESTDEF(list_any_cmp_false) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = 2,.y = 2,.z = 2 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_list_any_cmp(list, (uintptr_t)(&data), vec_cmp);
	munit_assert(!exist);
	return MUNIT_OK;
}

TESTDEF(list_all_true) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = 1,.y = 1,.z = 1 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_list_all(list, (uintptr_t)(&data));
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(list_all_cmp_true) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = 1,.y = 1,.z = 1 };
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_list_all_cmp(list, (uintptr_t)(&data), vec_cmp);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(list_reverse) {
	list_arange(list, 0, INI_LEN);

	cff_list_reverse(list);


	for (int i = INI_LEN - 1, j = 0; i >= 0; i--, j++)
	{
		vec3 data = { .x = i,.y = i,.z = i };
		vec3 out;
		cff_list_get(list, j, &out);
		assert_vec3(data, out);
	}

	return MUNIT_OK;
}

TESTDEF(list_sort) {
	cff_list aux_list;

	list_arange(list, 0, INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));

	cff_list_reverse(&aux_list);

	cff_list_sort(&aux_list, vec_cmp);

	uint8_t eq = cff_list_equal(list, &aux_list);

	cff_list_clear(&aux_list, NULL);

	munit_assert(eq);

	return MUNIT_OK;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_list* list = malloc(sizeof(cff_list));
	return list;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_list* list = malloc(sizeof(cff_list));
	cff_list_create(list, DATA_SIZE);
	return list;
}

static void test_tear_down(void* fixture) {
	cff_list_clear(fixture, NULL);
	free(fixture);
}


int test_list(int argc, const char* argv[]) {

	MunitTest tests[] = {
		{ "/test_create", test_list_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(list_add),
		TEST(list_set),
		TEST(list_insert_front),
		TEST(list_insert_mid),
		TEST(list_insert_back),
		TEST(list_get),
		TEST(list_first),
		TEST(list_last),
		TEST(list_remove),
		TEST(list_clear),
		TEST(list_join),
		TEST(list_foreach),
		TEST(list_copy),
		TEST(list_clone),
		TEST(list_filter),
		TEST(list_map),
		TEST(list_equal_true),
		TEST(list_equal_false),
		TEST(list_equal_cpm_true),
		TEST(list_equal_cmp_false),
		TEST(list_find),
		TEST(list_find_cmp),
		TEST(list_count),
		TEST(list_reverse),
		TEST(list_count_cmp),
		TEST(list_any_true),
		TEST(list_any_cmp_true),
		TEST(list_all_false),
		TEST(list_all_cmp_false),
		TEST(list_any_false),
		TEST(list_any_cmp_false),
		TEST(list_all_true),
		TEST(list_all_cmp_true),
		TEST(list_sort)
	};

	MunitSuite suite = { "/list", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}