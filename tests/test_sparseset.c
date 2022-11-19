#include <stdio.h>
#include "caffeine_sparse_set.h"
#include "caffeine_memory.h"

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

typedef struct
{
	int x, y, z;
}vec3;

const uint64_t INI_LEN = 10;
const uint64_t DATA_SIZE = sizeof(vec3);

#define TEST(FUNC) { "/"#FUNC, test_##FUNC, test_setup, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL }

#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], void* munit_data)

#define SKIP_ON_ERR(EXP) {cff_err_e err = (EXP); if (err != CFF_NONE_ERR) { return MUNIT_ERROR; }}

static void assert_vec3(vec3 a, vec3 b) {
	munit_assert(a.x == b.x && a.y == b.y && a.z == b.z);
}

static void sparseset_arange(cff_sparseset* set, int start, int end) {
	for (int i = start, j = 0; i < end; i++, j++)
	{
		vec3 data = { .x = i * 3,.y = i * 5,.z = i * 7 };
		cff_sparseset_add(set, (uint64_t)i, (uintptr_t) & (vec3) { .x = i, .y = i + 1, .z = i + 2 }, NULL);
		assert_uint64(set->count, == , i + 1);
	}
}

TESTDEF(sparse_set_create) {
	cff_sparseset* set = (cff_sparseset*)munit_data;

	cff_sparseset_create(set, INI_LEN, DATA_SIZE, NULL);
	assert_uint64(set->lenght, == , INI_LEN);
	assert_uint64(set->count, == , 0);
	assert_uint64(set->data_size, == , DATA_SIZE);
	assert_not_null((void*)set->dense);
	assert_not_null((void*)set->sparse);
	assert_not_null((void*)set->dense_index);
	return MUNIT_OK;
}

TESTDEF(sparse_set_add){
cff_sparseset* set = (cff_sparseset*)munit_data;
	
	sparseset_arange(set, 0, (int)INI_LEN);
	assert_uint64(set->lenght, == , INI_LEN);

	sparseset_arange(set, (int)INI_LEN, (int)INI_LEN*2);
	assert_uint64(set->lenght, == , INI_LEN * 2);

	return MUNIT_OK;
}

TESTDEF(sparse_set_get) {
	cff_sparseset* set = (cff_sparseset*)munit_data;
	
	sparseset_arange(set, 0, (int)INI_LEN);
	assert_uint64(set->lenght, == , INI_LEN);

	int index = 5;
	vec3 data = (vec3){ .x = index, .y = index + 1, .z = index + 2 };
	vec3 found = { 0 };
	cff_sparseset_get(set, (uint64_t)index, (uintptr_t)&found);
	assert_vec3(data, found);
	return MUNIT_OK;
}

TESTDEF(sparse_set_remove) {
	cff_sparseset* set = (cff_sparseset*)munit_data;
	
	sparseset_arange(set, 0, (int)INI_LEN);
	assert_uint64(set->lenght, == , INI_LEN);

	uint64_t index = (uint64_t)munit_rand_int_range(1, (int)(INI_LEN - 4));

	vec3 data = {0};
	vec3 last = { 0 };
	cff_sparseset_get(set,set->count-1, (uintptr_t)&last);

	cff_sparseset_remove(set, index);

	cff_sparseset_get(set, index, (uintptr_t)&data);

	assert_vec3(data, last);
	return MUNIT_OK;
}

TESTDEF(sparse_set_clear) {
	cff_sparseset* set = (cff_sparseset*)munit_data;
	
	sparseset_arange(set, 0, (int)INI_LEN);
	assert_uint64(set->lenght, == , INI_LEN);

	cff_sparseset_clear(set);

	munit_assert(set->count == 0);
	return MUNIT_OK;
}

TESTDEF(sparse_set_free) {
	cff_sparseset* set = (cff_sparseset*)munit_data;
	
	sparseset_arange(set, 0, (int)INI_LEN);
	assert_uint64(set->lenght, == , INI_LEN);

	cff_sparseset_free(set, NULL);

	munit_assert(set->count == 0);
	munit_assert(set->lenght == 0);
	munit_assert(set->data_size == 0);
	free(set);
	return MUNIT_OK;
}

TESTDEF(sparse_set_get_dense) {
	cff_sparseset* set = (cff_sparseset*)munit_data;
	
	uintptr_t dense = cff_sparseset_get_dense(set);

	munit_assert(dense != 0);
	return MUNIT_OK;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_sparseset* set = munit_malloc(sizeof(cff_sparseset));
	assert_not_null(set);
	memset(set, 0,sizeof(cff_sparseset));
	return set;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_sparseset* set = munit_malloc(sizeof(cff_sparseset));
	assert_not_null(set);
	memset(set, 0, sizeof(cff_sparseset));
	cff_sparseset_create(set, INI_LEN, DATA_SIZE, NULL);
	return set;
}

static void test_tear_down(void* fixture) {
	cff_sparseset_free((cff_sparseset*)fixture, NULL);
	free(fixture);
}


int test_sparseset(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/test_create_pass", test_sparse_set_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(sparse_set_add),
		TEST(sparse_set_get),
		TEST(sparse_set_remove),
		TEST(sparse_set_clear),
		TEST(sparse_set_get_dense),
		{ "/test_sparse_set_free", test_sparse_set_create, test_setup_create, NULL, MUNIT_TEST_OPTION_NONE, NULL },
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/sparse set", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main(&suite, NULL, argc, argv);
}

