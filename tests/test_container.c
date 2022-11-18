#include <stdio.h>
#include "caffeine_container.h"
#include "caffeine_memory.h"

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

typedef struct
{
	int x, y, z;
}vec3;

static const uint64_t INI_LEN = 10;
static const uint64_t DATA_SIZE = sizeof(vec3);

#define TEST(FUNC) { "/"#FUNC, test_##FUNC, test_setup, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL }

#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], cff_container* container)

#define SKIP_ON_ERR(EXP) {cff_err_e err = (EXP); if (err != CFF_NONE_ERR) { return MUNIT_ERROR; }}


static void print_vec3(void* data, uint64_t i) {
	vec3* vec = (vec3*)data;
	printf("{ %d %d %d }, ", vec->x, vec->y, vec->z);
}

static void print_container(cff_container* container) {
	cff_container_foreach(container, print_vec3, INI_LEN);
	printf("\n");
}

static void assert_vec3(vec3 a, vec3 b) {
	munit_assert(a.x == b.x && a.y == b.y && a.z == b.z);
}

static void container_arange(cff_container* container, int start, int end) {
	for (int i = start, j = 0; i < end; i++,j++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		cff_container_set(container, j, (uintptr_t)(&data), INI_LEN);
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
	return vec->x % 2 == 0;
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

TESTDEF(container_create) {
	SKIP_ON_ERR(cff_container_create(container, DATA_SIZE, INI_LEN, NULL));

	munit_assert(container->buffer != 0);
	munit_assert_int64(container->data_size, == , DATA_SIZE);
	return MUNIT_OK;
}

TESTDEF(container_set) {
	int x = munit_rand_uint32();
	int y = munit_rand_uint32();
	int z = munit_rand_uint32();

	int index = munit_rand_int_range(0, (int)(INI_LEN -1));

	vec3 data = { .x = x,.y = y,.z = z };

	cff_container_set(container, (uint64_t)index, (uintptr_t)(&data), INI_LEN);

	vec3 get_data = ((vec3*)container->buffer)[index];

	assert_vec3(get_data, data);
	return MUNIT_OK;
}

TESTDEF(container_get) {
	int x = munit_rand_uint32();
	int y = munit_rand_uint32();
	int z = munit_rand_uint32();

	int index = munit_rand_int_range(0, (int)(INI_LEN - 1));

	vec3 data = { .x = x,.y = y,.z = z };

	cff_container_set(container, (uint64_t)index, (uintptr_t)(&data), INI_LEN);

	vec3 get_data = {0};

	cff_container_get(container, (uint64_t)index, (uintptr_t)(&get_data), INI_LEN);

	assert_vec3(get_data, data);
	return MUNIT_OK;
}

TESTDEF(container_desloc) {

	container_arange(container, 0, (int)INI_LEN);

	int index = 3;
	int step = 2;
	cff_container_desloc(container, (uint64_t)index, (int64_t)step, INI_LEN);
	vec3 get_data = {0};
	cff_container_get(container, (uint64_t)index + step, (uintptr_t)(&get_data), INI_LEN);
	vec3 data = (vec3){ .x = index * 3, .y = index * 5, .z = index * 7 };
	assert_vec3(get_data, data);


	index = 3;
	step = -2;
	cff_container_desloc(container, (uint64_t)index, (int64_t)step, INI_LEN);
	get_data;
	cff_container_get(container, (uint64_t)index + step, (uintptr_t)(&get_data), INI_LEN);
	data = (vec3){ .x = index * 3, .y = index * 5, .z = index * 7 };
	assert_vec3(get_data, data);
	return MUNIT_OK;
}

TESTDEF(container_resize) {
	SKIP_ON_ERR(cff_container_resize(container, INI_LEN * 2, NULL));
	size_t allocked = _msize((void*)container->buffer);
	munit_assert(allocked == INI_LEN * 2 * container->data_size);
	return MUNIT_OK;
}

TESTDEF(container_insert) {
	container_arange(container, 0, (int)INI_LEN);

	vec3 data = { .x = 0,.y = 0,.z = 0 };
	vec3 get_data = {0};
	int insert_index = 5;
	cff_container_insert(container, insert_index,(uintptr_t)(&data), INI_LEN);
	cff_container_get(container, insert_index, (uintptr_t)(&get_data), INI_LEN);

	assert_vec3(get_data, data);
	return MUNIT_OK;
}

TESTDEF(container_remove) {
	container_arange(container, 0, (int)INI_LEN);
	
	int index_remove = munit_rand_int_range(0,INI_LEN-1);
	vec3 get_data = {0};
	uint8_t res = cff_container_remove(container, index_remove, INI_LEN);
	
	munit_assert_false(index_remove != (INI_LEN-1) && res == 0);
	munit_assert_false(index_remove == (INI_LEN-1) && res == 1);

	if (res) {
		cff_container_get(container, index_remove, (uintptr_t)(&get_data), INI_LEN);
		vec3 data = (vec3){ .x = (index_remove + 1) * 3, .y = (index_remove + 1) * 5, .z = (index_remove + 1) * 7 };
		assert_vec3(get_data, data);
	}
	
	return MUNIT_OK;
}

TESTDEF(container_copy) {
	container_arange(container, 0, (int)INI_LEN);

	cff_container dest = { 0 };
	uint64_t start = 3;
	uint64_t count = 4;

	uint64_t n_len = 0;
	SKIP_ON_ERR(cff_container_copy(container, &dest, start, count, INI_LEN, &n_len, NULL));
	for (uint64_t i = start, j = 0; i < (start+ count); i++, j++)
	{
		vec3 a = { 0 };
		vec3 b = { 0 };
		cff_container_get(container, i, (uintptr_t)(&a), INI_LEN);
		cff_container_get(&dest, j, (uintptr_t)(&b), n_len);
		assert_vec3(a, b);
	}
	cff_container_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(container_clone) {
	container_arange(container, 0, (int)INI_LEN);

	cff_container dest = { 0 };

	SKIP_ON_ERR(cff_container_clone(container, &dest, INI_LEN, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 a = { 0 };
		vec3 b = { 0 };
		cff_container_get(container, i, (uintptr_t)(&a), INI_LEN);
		cff_container_get(&dest, i, (uintptr_t)(&b), INI_LEN);
		assert_vec3(a, b);
	}
	cff_container_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(container_reverse) {
	container_arange(container, 0, (int)INI_LEN);

	SKIP_ON_ERR(cff_container_reverse(container, INI_LEN));
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 out = { 0 };
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		cff_container_get(container, (uint64_t)(INI_LEN - i - 1), (uintptr_t)(&out), INI_LEN);
		assert_vec3(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(container_fill) {
	vec3 data = { .x = 555,.y = 777,.z = 999 };
	cff_container_fill(container, (uintptr_t)(&data), INI_LEN);
	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 out = { 0 };
		cff_container_get(container, i, (uintptr_t)(&out), INI_LEN);
		assert_vec3(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(container_join) {
	cff_container other = { 0 };
	SKIP_ON_ERR(cff_container_create(&other, DATA_SIZE, INI_LEN / 2, NULL));

	container_arange(container, 0, (int)(INI_LEN / 2));
	container_arange(&other,(int)( INI_LEN / 2),(int)(INI_LEN));

	SKIP_ON_ERR(cff_container_join(container, &other, INI_LEN / 2, INI_LEN, INI_LEN / 2, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		vec3 out = { 0 };
		cff_container_get(container, i, (uintptr_t)(&out), INI_LEN);
		assert_vec3(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(container_filter) {
	cff_container other = { 0 };

	container_arange(container, 0, (int)INI_LEN);

	uint64_t f_len = 0;
	SKIP_ON_ERR(cff_container_filter(container, filter_even, &other, INI_LEN, &f_len, NULL));

	for (size_t i = 0; i < f_len; i++)
	{
		vec3 out = { 0 };
		cff_container_get(&other, i, (uintptr_t)(&out), f_len);
		munit_assert(out.x % 2 == 0);
	}
	cff_container_free(&other, NULL);
	return MUNIT_OK;
}

TESTDEF(container_map) {
	cff_container other = { 0 };

	container_arange(container, 0, (int)INI_LEN);
	SKIP_ON_ERR(cff_container_map(container, map_vec, &other, sizeof(int), INI_LEN, NULL));


	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = { 0 };
		int sum = 0;
		cff_container_get(container, i, (uintptr_t)(&data), INI_LEN);
		cff_container_get(&other, (uint64_t)i, (uintptr_t)&sum, INI_LEN);
		int data_sum = data.x + data.y + data.z;

		assert(data_sum == sum);
	}

	return MUNIT_OK;
}

TESTDEF(container_foreach) {
	container_arange(container, 0, (int)INI_LEN);
	cff_container_foreach(container, foreach_func, INI_LEN);
	return MUNIT_OK;
}

TESTDEF(container_sort) {
	cff_container other = { 0 };

	container_arange(container, 0, (int)INI_LEN);
	SKIP_ON_ERR(cff_container_clone(container, &other, INI_LEN, NULL));
	SKIP_ON_ERR(cff_container_reverse(&other, INI_LEN));
	SKIP_ON_ERR(cff_container_sort(&other, vec_cmp, INI_LEN));

	uint8_t eq = cff_container_equal(container, &other, INI_LEN);
	cff_container_free(&other, NULL);

	munit_assert(eq == 0);
	return MUNIT_OK;
}

TESTDEF(container_free) {
	cff_container_free(container, NULL);
	munit_assert(container->data_size == 0);
	munit_assert(container->buffer == 0);
	free(container);
	return MUNIT_OK;
}

TESTDEF(container_equal) {
	cff_container other;
	SKIP_ON_ERR(cff_container_create(&other, DATA_SIZE, INI_LEN, NULL));

	container_arange(container, 0, (int)INI_LEN);
	container_arange(&other, 0, (int)INI_LEN);

	uint8_t eq = cff_container_equal(container, &other, INI_LEN);
	cff_container_free(&other, NULL);

	munit_assert(eq == 0);
	return MUNIT_OK;
}

TESTDEF(container_find) {
	container_arange(container, 0, (int)INI_LEN);

	int index = 5;
	vec3 data = { .x = index * 3,.y = index * 5,.z = index * 7 };
	uint64_t found = 0;
	uint8_t f = cff_container_find(container, (uintptr_t)(&data), &found, INI_LEN);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(container_find_cmp) {
	container_arange(container, 0, (int)INI_LEN);

	int index = 5;
	vec3 data = { .x = index * 3,.y = index * 5,.z = index * 7 };
	uint64_t found = 0;
	cff_container_find_cmp(container, (uintptr_t)(&data), &found, vec_cmp, INI_LEN);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(container_count) {
	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cc += i % 2;
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint64_t count = cff_container_count(container, (uintptr_t)(&data), INI_LEN);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(container_count_cmp) {

	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cc += i % 2;
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint64_t count = cff_container_count_cmp(container, (uintptr_t)(&data), vec_cmp, INI_LEN);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(container_any) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_container_any(container, (uintptr_t)(&data), INI_LEN);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(container_any_cmp) {

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_container_any_cmp(container, (uintptr_t)(&data), vec_cmp, INI_LEN);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(container_all) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_container_all(container, (uintptr_t)(&data), INI_LEN);
	munit_assert_false(exist);
	return MUNIT_OK;
}

TESTDEF(container_all_cmp) {
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_container_all_cmp(container, (uintptr_t)(&data), vec_cmp, INI_LEN);
	munit_assert_false(exist);
	return MUNIT_OK;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_container* container = malloc(sizeof(cff_container));
	cff_container_create(container, DATA_SIZE, INI_LEN, NULL);
	return container;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_container* container = malloc(sizeof(cff_container));
	return container;
}

static void test_tear_down(void* fixture) {
	cff_container_free(fixture, NULL);
	free(fixture);
}


int test_container(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/test_create", test_container_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(container_set),
		TEST(container_get),
		TEST(container_desloc),
		TEST(container_resize),
		TEST(container_insert),
		TEST(container_remove),
		TEST(container_copy),
		TEST(container_clone),
		TEST(container_reverse),
		TEST(container_fill),
		TEST(container_join),
		TEST(container_filter),
		TEST(container_map),
		TEST(container_foreach),
		TEST(container_sort),
		{ "/test_free", test_container_free, test_setup, NULL, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(container_equal),
		TEST(container_find),
		TEST(container_find_cmp),
		TEST(container_count),
		TEST(container_count_cmp),
		TEST(container_any),
		TEST(container_any_cmp),
		TEST(container_all),
		TEST(container_all_cmp),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/container", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}