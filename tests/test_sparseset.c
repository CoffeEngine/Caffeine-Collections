#include "caffeine_sparse_set.h"
#include "test_defs.h"



static void sparseset_arange(cff_sparseset* set, int start, int end) {
	for (int i = start, j = 0; i < end; i++, j++)
	{
		cff_sparseset_add(set, (uint64_t)i, (uintptr_t) & (test_data) { .x = i, .y = i + 1, .z = i + 2 }, NULL);
		assert_uint64(set->count, == , i + (uint64_t)1);
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
	test_data data = (test_data){ .x = index, .y = index + 1, .z = index + 2 };
	test_data found = { 0 };
	cff_sparseset_get(set, (uint64_t)index, (uintptr_t)&found);
	ASSERT_EQUALS(data, found);
	return MUNIT_OK;
}

TESTDEF(sparse_set_remove) {
	cff_sparseset* set = (cff_sparseset*)munit_data;
	
	sparseset_arange(set, 0, (int)INI_LEN);
	assert_uint64(set->lenght, == , INI_LEN);

	uint64_t index = (uint64_t)munit_rand_int_range(1, (int)(INI_LEN - 4));

	test_data data = {0};
	test_data last = { 0 };
	cff_sparseset_get(set,set->count-1, (uintptr_t)&last);

	cff_sparseset_remove(set, index);

	cff_sparseset_get(set, index, (uintptr_t)&data);

	ASSERT_EQUALS(data, last);
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

