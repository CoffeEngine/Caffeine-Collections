#include <stdio.h>
#include "caffeine_ordered_container.h"
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

#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], void* munit_data)

#define SKIP_ON_ERR(EXP) {cff_err_e err = (EXP); if (err != CFF_NONE_ERR) { return MUNIT_ERROR; }}

#pragma region UTILS


static void print_vec3(void* data, uint64_t i) {
	vec3* vec = (vec3*)data;
	printf("{ %d %d %d }, ", vec->x, vec->y, vec->z);
}

static void print_container(cff_ordered_container* container) {
	cff_ordered_container_foreach(container, print_vec3, INI_LEN);
	printf("\n");
}

static void assert_vec3(vec3 a, vec3 b) {
	munit_assert(a.x == b.x && a.y == b.y && a.z == b.z);
}

static void container_arange(cff_ordered_container* container, int start, int end) {
	for (int i = start, j = 0; i < end; i++, j++)
	{
		int x = munit_rand_int_range(0,10);
		int y = munit_rand_int_range(0, 10);
		int z = munit_rand_int_range(0, 10);
		vec3 data = { .x = x ,.y = y ,.z = z };
		cff_ordered_container_add(container, (uintptr_t)(&data), j, INI_LEN);
	}
}

static void container_arange_eq(cff_ordered_container* container, int start, int end) {
	for (int i = start, j = 0; i < end; i++, j++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		cff_ordered_container_add(container, (uintptr_t)(&data), j, INI_LEN);
	}
}


static void assert_order(cff_ordered_container* container, comparer_fn order_func, uint64_t len) {
	vec3* value = (vec3*)container->buffer;
	
	for (size_t i = 1; i < len; i++)
	{
		vec3* current = value + i;
		vec3* prev = current - 1;
		munit_assert(order_func(prev, current, container->data_size) != CFF_GREATER);
	}
}


#pragma endregion


#pragma region CALLBACKS

static cff_cmp_e vec3_order(const void* const ptr_a, const void* const ptr_b, uint64_t data_size) {
	vec3* a = (vec3*)ptr_a;
	vec3* b = (vec3*)ptr_b;

	if (a->x == b->x) {
		return CFF_EQUALS;
	}

	if (a->x < b->x) return CFF_LESS;

	return CFF_GREATER;
}

static cff_cmp_e vec3_order_reverse(const void* const ptr_a, const void* const ptr_b, uint64_t data_size) {
	vec3* a = (vec3*)ptr_a;
	vec3* b = (vec3*)ptr_b;

	if (a->x == b->x) {
		return CFF_EQUALS;
	}

	if (a->x > b->x) return CFF_LESS;

	return CFF_GREATER;
}

static cff_cmp_e vec_cmp(const void* const ptr_a, const void* const ptr_b, uint64_t data_size) {
	vec3* a = (vec3*)ptr_a;
	vec3* b = (vec3*)ptr_b;

	if (a->x == b->x && a->y == b->y && a->z == b->z) {
		return CFF_EQUALS;
	}

	if (a->x < b->x) return CFF_LESS;
	if (a->x > b->x) return CFF_GREATER;

	return CFF_NOT_EQUAL;
}

static bool filter_even(const void* const data, uint64_t index, uint64_t data_size) {
	vec3* vec = (vec3*)data;
	return vec->x % 2 == 0;
}

static void foreach_func(void* data, uint64_t i) {
	vec3 vec = *(vec3*)data;
	vec3 other = { .x = (int)i * 3,.y = (int)i * 5,.z = (int)i * 7 };
}

static void map_vec(const void* const from_ptr, void* to_ptr, uint64_t index) {
	vec3* from = (vec3*)from_ptr;
	int* to = (int*)to_ptr;

	*to = from->x + from->y + from->z;
}

static cff_cmp_e int_cmp(const void* const ptr_a, const void* const ptr_b, uint64_t data_size) {
	int a = *(int*)ptr_a;
	int b = *(int*)ptr_b;


	if (a < b) return CFF_LESS;
	if (a > b) return CFF_GREATER;
	return CFF_EQUALS;
}
#pragma endregion

TESTDEF(ordered_container_create) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	SKIP_ON_ERR(cff_ordered_container_create(container, DATA_SIZE, vec3_order, INI_LEN, NULL));

	munit_assert(container->buffer != 0);
	munit_assert_int64(container->data_size, == , DATA_SIZE);
	return MUNIT_OK;
}


TESTDEF(ordered_container_get) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	
	vec3 data1 = { .x = 3,.y = 3,.z = 3 };
	vec3 data2 = { .x = 0,.y = 0,.z = 0 };

	cff_ordered_container_add(container,(uintptr_t)(&data1),0, INI_LEN);
	cff_ordered_container_add(container,(uintptr_t)(&data2),1, INI_LEN);

	vec3 get_data = { 0 };

	cff_ordered_container_get(container, (uint64_t)1, (uintptr_t)(&get_data), INI_LEN);

	assert_vec3(get_data, data1);
	assert_order(container, vec3_order, 2);
	return MUNIT_OK;
}


TESTDEF(ordered_container_resize) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	SKIP_ON_ERR(cff_ordered_container_resize(container, INI_LEN * 2, NULL));

#ifdef CFF_COMP_MSVC
	size_t allocked = _msize((void*)container->buffer);
	munit_assert(allocked == INI_LEN * 2 * container->data_size);
#endif

	return MUNIT_OK;
}



TESTDEF(ordered_container_remove) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	uint64_t index_remove = (uint64_t)munit_rand_int_range(0, (int)(INI_LEN - 1));
	uint8_t res = cff_ordered_container_remove(container, index_remove, INI_LEN);

	munit_assert_false(index_remove != (INI_LEN - 1) && res == 0);
	munit_assert_false(index_remove == (INI_LEN - 1) && res == 1);

	
	assert_order(container, vec3_order, INI_LEN-1);
	return MUNIT_OK;
}

TESTDEF(ordered_container_copy) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	cff_ordered_container dest = { 0 };
	uint64_t start = 3;
	uint64_t count = 4;

	uint64_t n_len = 0;
	SKIP_ON_ERR(cff_ordered_container_copy(container, &dest, start, count, INI_LEN, &n_len, NULL));
	
	for (uint64_t i = start, j = 0; i < (start + count); i++, j++)
	{
		vec3 a = { 0 };
		vec3 b = { 0 };
		cff_ordered_container_get(container, i, (uintptr_t)(&a), INI_LEN);
		cff_ordered_container_get(&dest, j, (uintptr_t)(&b), n_len);
		assert_vec3(a, b);
	}

	assert_order(container, vec3_order, INI_LEN);
	assert_order(&dest, vec3_order, n_len);

	cff_ordered_container_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(ordered_container_clone) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	cff_ordered_container dest = { 0 };

	SKIP_ON_ERR(cff_ordered_container_clone(container, &dest, INI_LEN, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 a = { 0 };
		vec3 b = { 0 };
		cff_ordered_container_get(container, i, (uintptr_t)(&a), INI_LEN);
		cff_ordered_container_get(&dest, i, (uintptr_t)(&b), INI_LEN);
		assert_vec3(a, b);
	}

	assert_order(container, vec3_order, INI_LEN);
	assert_order(&dest, vec3_order, INI_LEN);

	cff_ordered_container_free(&dest, NULL);
	return MUNIT_OK;
}


TESTDEF(ordered_container_fill) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	vec3 data = { .x = 555,.y = 777,.z = 999 };
	cff_ordered_container_fill(container, (uintptr_t)(&data), INI_LEN);
	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 out = { 0 };
		cff_ordered_container_get(container, i, (uintptr_t)(&out), INI_LEN);
		assert_vec3(data, out);
	}

	assert_order(container, vec3_order, INI_LEN);
	return MUNIT_OK;
}

TESTDEF(ordered_container_join) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	cff_ordered_container other = { 0 };
	SKIP_ON_ERR(cff_ordered_container_create(&other, DATA_SIZE,vec3_order, INI_LEN / 2, NULL));

	container_arange(container, 0, (int)(INI_LEN / 2));
	container_arange(&other, (int)(INI_LEN / 2), (int)(INI_LEN));

	SKIP_ON_ERR(cff_ordered_container_join(container, &other, INI_LEN / 2, INI_LEN, INI_LEN / 2, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		vec3 out = { 0 };
		cff_ordered_container_get(container, i, (uintptr_t)(&out), INI_LEN);
		assert_vec3(data, out);
	}

	assert_order(container, vec3_order, INI_LEN);
	return MUNIT_OK;
}

TESTDEF(ordered_container_filter) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	cff_ordered_container other = { 0 };

	container_arange(container, 0, (int)INI_LEN);

	uint64_t f_len = 0;
	SKIP_ON_ERR(cff_ordered_container_filter(container, filter_even, &other, INI_LEN, &f_len, NULL));

	for (size_t i = 0; i < f_len; i++)
	{
		vec3 out = { 0 };
		cff_ordered_container_get(&other, i, (uintptr_t)(&out), f_len);
		munit_assert(out.x % 2 == 0);
	}

	assert_order(container, vec3_order, INI_LEN);
	assert_order(&other, vec3_order, f_len);
	
	cff_ordered_container_free(&other, NULL);
	return MUNIT_OK;
}

TESTDEF(ordered_container_map) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	cff_ordered_container other = { 0 };

	container_arange(container, 0, (int)INI_LEN);
	SKIP_ON_ERR(cff_ordered_container_map(container, map_vec, &other, int_cmp, sizeof(int), INI_LEN, NULL));

	assert_order(container, vec3_order, INI_LEN);
	assert_order(container, int_cmp, INI_LEN);

	return MUNIT_OK;
}

TESTDEF(ordered_container_foreach) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);
	cff_ordered_container_foreach(container, foreach_func, INI_LEN);
	return MUNIT_OK;
}

TESTDEF(ordered_container_sort) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;


	container_arange(container, 0, (int)INI_LEN);


	SKIP_ON_ERR(cff_ordered_container_sort(container, vec3_order_reverse, INI_LEN));

	assert_order(container, vec3_order_reverse, INI_LEN);
	return MUNIT_OK;
}

TESTDEF(ordered_container_free) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	cff_ordered_container_free(container, NULL);
	munit_assert(container->data_size == 0);
	munit_assert(container->buffer == 0);
	free(container);
	return MUNIT_OK;
}

TESTDEF(ordered_container_equal) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	cff_ordered_container other;
	SKIP_ON_ERR(cff_ordered_container_create(&other, DATA_SIZE, vec3_order, INI_LEN, NULL));

	container_arange_eq(container, 0, (int)INI_LEN);
	container_arange_eq(&other, 0, (int)INI_LEN);

	uint8_t eq = cff_ordered_container_equal(container, &other, INI_LEN);
	cff_ordered_container_free(&other, NULL);

	munit_assert(eq == 0);
	return MUNIT_OK;
}

TESTDEF(ordered_container_find) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	container_arange_eq(container, 0, (int)INI_LEN);

	int index = 5;
	vec3 data = { .x = index * 3,.y = index * 5,.z = index * 7 };
	uint64_t found = 0;
	uint8_t f = cff_ordered_container_find(container, (uintptr_t)(&data), &found, INI_LEN);
	munit_assert(f);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(ordered_container_find_cmp) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	container_arange_eq(container, 0, (int)INI_LEN);

	int index = 5;
	vec3 data = { .x = index * 3,.y = index * 5,.z = index * 7 };
	uint64_t found = 0;
	cff_ordered_container_find_cmp(container, (uintptr_t)(&data), &found, vec_cmp, INI_LEN);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(ordered_container_count) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cc += i % 2;
		cff_ordered_container_add(container, (uintptr_t)(&data),i, INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint64_t count = cff_ordered_container_count(container, (uintptr_t)(&data), INI_LEN);
	assert_order(container, vec3_order, INI_LEN);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(ordered_container_count_cmp) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cc += i % 2;
		cff_ordered_container_add(container, (uintptr_t)(&data),i, INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint64_t count = cff_ordered_container_count_cmp(container, (uintptr_t)(&data), vec_cmp, INI_LEN);
	assert_order(container, vec3_order, INI_LEN);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(ordered_container_any) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_ordered_container_add(container, (uintptr_t)(&data),i, INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_ordered_container_any(container, (uintptr_t)(&data), INI_LEN);
	assert_order(container, vec3_order, INI_LEN);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(ordered_container_any_cmp) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_ordered_container_add(container, (uintptr_t)(&data),i, INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_ordered_container_any_cmp(container, (uintptr_t)(&data), vec_cmp, INI_LEN);
	assert_order(container, vec3_order, INI_LEN);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(ordered_container_all) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_ordered_container_add(container, (uintptr_t)(&data),i, INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_ordered_container_all(container, (uintptr_t)(&data), INI_LEN);
	assert_order(container, vec3_order, INI_LEN);
	munit_assert_false(exist);
	return MUNIT_OK;
}

TESTDEF(ordered_container_all_cmp) {
	cff_ordered_container* container = (cff_ordered_container*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		vec3 data = { .x = i % 2,.y = i % 2,.z = i % 2 };
		cff_ordered_container_add(container,(uintptr_t)(&data),i, INI_LEN);
	}
	vec3 data = { .x = 1,.y = 1,.z = 1 };
	uint8_t exist = cff_ordered_container_all_cmp(container, (uintptr_t)(&data), vec_cmp, INI_LEN);
	assert_order(container, vec3_order, INI_LEN);
	munit_assert_false(exist);
	return MUNIT_OK;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_ordered_container* container = malloc(sizeof(cff_ordered_container));
	cff_ordered_container_create(container, DATA_SIZE, vec3_order, INI_LEN, NULL);
	return container;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_ordered_container* container = malloc(sizeof(cff_ordered_container));
	if (container)*container = (cff_ordered_container){ 0 };
	return container;
}

static void test_tear_down(void* fixture) {
	cff_ordered_container_free(fixture, NULL);
	free(fixture);
}


int test_ordered_container(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/ordered_container_create", test_ordered_container_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(ordered_container_get),
		TEST(ordered_container_resize),
		TEST(ordered_container_remove),
		TEST(ordered_container_copy),
		TEST(ordered_container_clone),
		TEST(ordered_container_fill),
		//TEST(ordered_container_join),
		TEST(ordered_container_filter),
		TEST(ordered_container_map),
		TEST(ordered_container_foreach),
		TEST(ordered_container_sort),
		{ "/ordered_container_free", test_ordered_container_free, test_setup, NULL, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(ordered_container_equal),
		TEST(ordered_container_find),
		TEST(ordered_container_find_cmp),
		TEST(ordered_container_count),
		TEST(ordered_container_count_cmp),
		TEST(ordered_container_any),
		TEST(ordered_container_any_cmp),
		TEST(ordered_container_all),
		TEST(ordered_container_all_cmp),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/ordered", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}