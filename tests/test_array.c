#include <stdio.h>
#include "caffeine_array.h"
#include "caffeine_memory.h"

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

typedef struct
{
	int x, y, z;
}vec3;

static const uint64_t INI_LEN = 100;
static const uint64_t DATA_SIZE = sizeof(vec3);

#define TEST(FUNC) { "/"#FUNC, test_##FUNC, test_setup, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL }

#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], cff_array* array)

#define SKIP_ON_ERR(EXP) {cff_err_e err = (EXP); if (err != CFF_NONE_ERR) { return MUNIT_SKIP; }}


static void print_vec3(void* data, uint64_t i) {
	vec3* vec = (vec3*)data;
	printf("{ %d %d %d }, ", vec->x, vec->y, vec->z);
}

static void assert_vec3(vec3 a, vec3 b) {
	munit_assert(a.x == b.x && a.y == b.y && a.z == b.z);
}

static void print_array(cff_array* array) {
	cff_array_foreach(array, print_vec3);
	printf("\n");
}

static void array_arange(cff_array* array, int start, int end) {
	for (int i = start, j = 0; i < end; i++, j++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		cff_array_set(array, j, (uintptr_t)(&data));
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

static cff_cmp_e filter_even(void* data, uint64_t index, uint64_t data_size) {
	vec3* vec = (vec3*)data;
	if (vec->x % 2 == 0) return CFF_EQUALS;
	return CFF_NOT_EQUAL;
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

TESTDEF(array_create) {
	SKIP_ON_ERR(cff_array_create(array, DATA_SIZE, INI_LEN,NULL));

	munit_assert(array->buffer != 0);
	munit_assert_int64(array->data_size, == , DATA_SIZE);
	return MUNIT_OK;
}

TESTDEF(array_set) {
	int x = munit_rand_uint32();
	int y = munit_rand_uint32();
	int z = munit_rand_uint32();

	uint64_t index = (uint64_t)munit_rand_int_range(0, (int)(INI_LEN - 1));

	vec3 data = { .x = x,.y = y,.z = z };

	cff_array_set(array, (uint64_t)index, (uintptr_t)(&data));

	vec3 get_data = ((vec3*)array->buffer)[index];

	assert_vec3(get_data, data);
	return MUNIT_OK;
}

TESTDEF(array_get) {
	int x = munit_rand_uint32();
	int y = munit_rand_uint32();
	int z = munit_rand_uint32();

	int index = munit_rand_int_range(0, (int)(INI_LEN - 1));

	vec3 data = { .x = x,.y = y,.z = z };

	cff_array_set(array, (uint64_t)index, (uintptr_t)(&data));

	vec3 get_data = {0};

	cff_array_get(array, (uint64_t)index, (uintptr_t)(&get_data));

	assert_vec3(get_data, data);
	return MUNIT_OK;
}

TESTDEF(array_resize) {
	SKIP_ON_ERR(cff_array_resize(array, INI_LEN * 2, NULL));
	size_t allocked = _msize((void*)array->buffer);
	munit_assert(allocked == INI_LEN * 2 * array->data_size);
	return MUNIT_OK;
}

TESTDEF(array_insert) {
	array_arange(array, 0, (int)INI_LEN);

	vec3 data = { .x = 0,.y = 0,.z = 0 };
	vec3 get_data = {0};
	int insert_index = 5;
	cff_array_insert(array, insert_index, (uintptr_t)(&data));
	cff_array_get(array, insert_index, (uintptr_t)(&get_data));

	assert_vec3(get_data, data);
	return MUNIT_OK;
}

TESTDEF(array_remove) {
	array_arange(array, 0, (int)INI_LEN);

	int index_remove = 5;
	vec3 get_data = {0};
	cff_array_remove(array, index_remove);
	cff_array_get(array, index_remove, (uintptr_t)(&get_data));
	vec3 data = (vec3){ .x = (index_remove + 1) * 3, .y = (index_remove + 1) * 5, .z = (index_remove + 1) * 7 };
	assert_vec3(get_data, data);
	return MUNIT_OK;
}

TESTDEF(array_copy) {
	array_arange(array, 0, (int)INI_LEN);

	cff_array dest = { 0 };
	uint64_t start = 3;
	uint64_t count = 4;

	
	SKIP_ON_ERR(cff_array_copy(array, &dest, start, count, NULL));
	for (uint64_t i = start, j = 0; i < start+count; i++, j++)
	{
		vec3 a = { 0 };
		vec3 b = { 0 };
		cff_array_get(array, i, (uintptr_t)(&a));
		cff_array_get(&dest, j, (uintptr_t)(&b));
		assert_vec3(a, b);
	}
	cff_array_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(array_clone) {
	array_arange(array, 0, (int)INI_LEN);

	cff_array dest = { 0 };

	SKIP_ON_ERR(cff_array_clone(array, &dest, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 a = { 0 };
		vec3 b = { 0 };
		cff_array_get(array, i, (uintptr_t)(&a));
		cff_array_get(&dest, i, (uintptr_t)(&b));
		assert_vec3(a, b);
	}
	cff_array_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(array_reverse) {
	array_arange(array, 0, (int)INI_LEN);

	SKIP_ON_ERR(cff_array_reverse(array));
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 out = { 0 };
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		cff_array_get(array, (uint64_t)(INI_LEN - i - 1), (uintptr_t)(&out));
		assert_vec3(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(array_fill) {
	vec3 data = { .x = 555,.y = 777,.z = 999 };
	cff_array_fill(array, (uintptr_t)(&data));
	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 out = { 0 };
		cff_array_get(array, i, (uintptr_t)(&out));
		assert_vec3(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(array_join) {
	cff_array other = { 0 };
	SKIP_ON_ERR(cff_array_create(&other, DATA_SIZE, INI_LEN / 2, NULL));

	array_arange(array, 0, (int)INI_LEN / 2);
	array_arange(&other, (int)INI_LEN / 2, (int)INI_LEN);

	SKIP_ON_ERR(cff_array_join(array, &other, INI_LEN / 2, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		vec3 out = { 0 };
		cff_array_get(array, i, (uintptr_t)(&out));
		assert_vec3(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(array_filter) {
	cff_array other = { 0 };

	array_arange(array, 0, (int)INI_LEN);

	
	SKIP_ON_ERR(cff_array_filter(array, filter_even, &other, NULL));

	for (size_t i = 0; i < other.lenght; i++)
	{
		vec3 out = { 0 };
		cff_array_get(&other, i, (uintptr_t)(&out));
		munit_assert(out.x % 2 == 0);
	}

	if(other.lenght) cff_array_free(&other, NULL);
	return MUNIT_OK;
}

TESTDEF(array_map) {
	cff_array other = { 0 };

	array_arange(array, 0, (int)INI_LEN);
	SKIP_ON_ERR(cff_array_map(array, map_vec, &other, sizeof(int), NULL));


	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = { 0 };
		int sum = 0;
		cff_array_get(array, (uint64_t)i, (uintptr_t)(&data));
		cff_array_get(&other, (uint64_t)i, (uintptr_t)&sum);
		int data_sum = data.x + data.y + data.z;

		assert(data_sum == sum);
	}

	return MUNIT_OK;
}

TESTDEF(array_foreach) {
	array_arange(array, 0, (int)INI_LEN);
	cff_array_foreach(array, foreach_func);
	return MUNIT_OK;
}

TESTDEF(array_sort) {
	cff_array other = { 0 };

	array_arange(array, 0, (int)INI_LEN);
	SKIP_ON_ERR(cff_array_clone(array, &other, NULL));
	SKIP_ON_ERR(cff_array_reverse(&other));
	SKIP_ON_ERR(cff_array_sort(&other, vec_cmp));

	uint8_t eq = cff_array_equal(array, &other);
	cff_array_free(&other, NULL);

	munit_assert(eq == 0);
	return MUNIT_OK;
}

TESTDEF(array_free) {
	cff_array_free(array, NULL);
	munit_assert(array->data_size == 0);
	munit_assert(array->buffer == 0);
	free(array);
	return MUNIT_OK;
}

TESTDEF(array_equal) {
	cff_array other;
	SKIP_ON_ERR(cff_array_create(&other, DATA_SIZE, INI_LEN, NULL));

	array_arange(array, 0, (int)INI_LEN);
	array_arange(&other, 0, (int)INI_LEN);

	uint8_t eq = cff_array_equal(array, &other);
	cff_array_free(&other, NULL);

	munit_assert(eq == 0);
	return MUNIT_OK;
}

TESTDEF(array_find) {
	array_arange(array, 0, (int)INI_LEN);

	int index = 5;
	vec3 data = { .x = index * 3,.y = index * 5,.z = index * 7 };
	uint64_t found = 0;
	uint8_t f = cff_array_find(array, (uintptr_t)(&data), &found);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(array_find_cmp) {
	array_arange(array, 0, (int)INI_LEN);

	int index = 5;
	vec3 data = { .x = index * 3,.y = index * 5,.z = index * 7 };
	uint64_t found = 0;
	cff_array_find_cmp(array, (uintptr_t)(&data), &found, vec_cmp);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(array_count) {
	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cc += i % 2;
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint64_t count = cff_array_count(array, (uintptr_t)(&data));
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(array_count_cmp) {

	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cc += i % 2;
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint64_t count = cff_array_count_cmp(array, (uintptr_t)(&data), vec_cmp);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(array_any) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_array_any(array, (uintptr_t)(&data));
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(array_any_cmp) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_array_any_cmp(array, (uintptr_t)(&data), vec_cmp);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(array_all) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_array_all(array, (uintptr_t)(&data));
	munit_assert_false(exist);
	return MUNIT_OK;
}

TESTDEF(array_all_cmp) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_array_all_cmp(array, (uintptr_t)(&data), vec_cmp);
	munit_assert_false(exist);
	return MUNIT_OK;
}


static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_array* array = malloc(sizeof(cff_array));
	return array;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_array* array = malloc(sizeof(cff_array));
	cff_array_create(array, DATA_SIZE, INI_LEN, NULL);
	return array;
}

static void test_tear_down(void* fixture) {
	cff_array_free(fixture, NULL);
	free(fixture);
}


int test_array(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/test_create", test_array_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(array_set),
		TEST(array_get),
		TEST(array_resize),
		TEST(array_insert),
		TEST(array_remove),
		TEST(array_copy),
		TEST(array_clone),
		TEST(array_reverse),
		TEST(array_fill),
		TEST(array_join),
		TEST(array_filter),
		TEST(array_map),
		TEST(array_foreach),
		TEST(array_sort),
		{ "/test_free", test_array_free, test_setup, NULL, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(array_equal),
		TEST(array_find),
		TEST(array_find_cmp),
		TEST(array_count),
		TEST(array_count_cmp),
		TEST(array_any),
		TEST(array_any_cmp),
		TEST(array_all),
		TEST(array_all_cmp),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/array", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}