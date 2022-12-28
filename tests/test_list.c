#include "caffeine_list.h"
#include "test_defs.h"


static void list_arange(cff_list* list, int start, int end) {
	for (int i = start; i < end; i++)
	{
		test_data data = data_new_at_index(i);
		cff_list_add(list, (uintptr_t)(&data), NULL);
	}
}

TESTDEF(list_create) {
	cff_list* list = (cff_list*)munit_data;

	cff_list_create(list, DATA_SIZE);

	munit_assert_int64(list->data_size, == , DATA_SIZE);
	return MUNIT_OK;
}

TESTDEF(list_add) {
	cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}

	caffeine_list_bucket* bucket = list->list_start;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		test_data found = *((test_data*)bucket->data_ptr);
		ASSERT_EQUALS(data, found);
		bucket = bucket->next_bucket;
	}

	return MUNIT_OK;
}

TESTDEF(list_set) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, (int)INI_LEN);

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		cff_list_set(list, i, (uintptr_t)(&data));
	}

	caffeine_list_bucket* bucket = list->list_start;
	int cc = 0;
	while (bucket != NULL)
	{
		test_data data = data_new_at_index(cc);
		test_data found = *((test_data*)bucket->data_ptr);
		ASSERT_EQUALS(data, found);
		bucket = bucket->next_bucket;
		cc++;
	}

	return MUNIT_OK;
}

TESTDEF(list_insert_front) {
	cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		SKIP_ON_ERR(cff_list_insert(list, 0, (uintptr_t)(&data), NULL));
	}

	caffeine_list_bucket* bucket = list->list_start;

	for (int i = (int)(INI_LEN - 1); i >= 0; i--)
	{
		test_data data = data_new_at_index(i);
		test_data found = *((test_data*)bucket->data_ptr);
		ASSERT_EQUALS(data, found);
		bucket = bucket->next_bucket;
	}

	return MUNIT_OK;
}

TESTDEF(list_insert_mid) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, 5);

	uint64_t index_offset = 3;
	for (uint64_t i = 0; i < 5; i++)
	{
		test_data data = data_new_at_index(0);
		SKIP_ON_ERR(cff_list_insert(list, index_offset + i, (uintptr_t)(&data), NULL));
	}

	caffeine_list_bucket* bucket = list->list_start;

	for (int i = 0; i < list->count; i++)
	{
		if (i >= index_offset && i < index_offset + 5) {
			test_data data = data_new_at_index(0);
			test_data found = *((test_data*)bucket->data_ptr);
			ASSERT_EQUALS(data, found);
		}

		bucket = bucket->next_bucket;
	}

	return MUNIT_OK;
}

TESTDEF(list_insert_back) {
	cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		SKIP_ON_ERR(cff_list_insert(list, i, (uintptr_t)(&data), NULL));
	}

	caffeine_list_bucket* bucket = list->list_start;

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		test_data found = *((test_data*)bucket->data_ptr);
		ASSERT_EQUALS(data, found);
		bucket = bucket->next_bucket;
	}

	return MUNIT_OK;
}

TESTDEF(list_get) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, (int)INI_LEN);

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		test_data found = { 0 };
		cff_list_get(list, i, (uintptr_t)&found);
		ASSERT_EQUALS(data, found);
	}

	return MUNIT_OK;
}

TESTDEF(list_first) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 5, (int)INI_LEN);
	int idx = 5;
	test_data data = data_new_at_index(idx);
	test_data found = { 0 };
	cff_list_first(list, (uintptr_t)&found);
	ASSERT_EQUALS(data, found);

	return MUNIT_OK;
}

TESTDEF(list_last) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, (int)INI_LEN);
	int idx = (int)INI_LEN - 1;
	test_data data = data_new_at_index(idx);
	test_data found = { 0 };
	cff_list_last(list, (uintptr_t)&found);
	ASSERT_EQUALS(data, found);

	return MUNIT_OK;
}

TESTDEF(list_remove) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, (int)INI_LEN);

	cff_list_remove(list, 1, NULL);

	test_data out = { 0 };
	test_data expected = data_new_at_index(2);

	cff_list_get(list, 1, (uintptr_t)&out);

	ASSERT_EQUALS(out, expected);

	return MUNIT_OK;
}

TESTDEF(list_clear) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, (int)INI_LEN);

	cff_list_clear(list, NULL);

	munit_assert(list->count == 0);
	munit_assert(list->list_start == NULL);
	munit_assert(list->list_end == NULL);

	return MUNIT_OK;
}

TESTDEF(list_join) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	cff_list_create(&aux_list, DATA_SIZE);

	list_arange(list, 0, (int)INI_LEN / 2);
	list_arange(&aux_list, (int)INI_LEN / 2, (int)INI_LEN);

	cff_list_join(list, &aux_list);

	caffeine_list_bucket* bucket = list->list_start;
	int cc = 0;
	while (bucket != NULL)
	{
		test_data data = data_new_at_index(cc);
		test_data found = *((test_data*)bucket->data_ptr);
		ASSERT_EQUALS(data, found);
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
	cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		cff_list_add(list, (uintptr_t)(&data), NULL);
	}

	cff_list_foreach(list, foreach);

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data;
		cff_list_get(list,i, (uintptr_t)(&data));
		munit_assert(validate_foreach(data, i));
	}

	return MUNIT_OK;
}

TESTDEF(list_copy) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_copy(list, &aux_list, INI_LEN / 2, INI_LEN / 2, NULL));

	for (int i = 0; i < (int)INI_LEN / 2; i++)
	{
		test_data a = { 0 }, b = { 0 };

		cff_list_get(list, i + (INI_LEN / 2), (uintptr_t)&a);
		cff_list_get(&aux_list, i, (uintptr_t)&b);

		ASSERT_EQUALS(a, b);
	}

	cff_list_clear(&aux_list, NULL);
	return MUNIT_OK;
}

TESTDEF(list_clone) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data a = {0}, b ={0};

		cff_list_get(list, i, (uintptr_t)&a);
		cff_list_get(&aux_list, i, (uintptr_t)&b);

		ASSERT_EQUALS(a, b);
	}

	cff_list_clear(&aux_list, NULL);
	return MUNIT_OK;
}

TESTDEF(list_filter) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_filter(list, filter, &aux_list, NULL));

	for (uint64_t i = 0; i < aux_list.count; i++)
	{
		test_data out = { 0 };
		cff_list_get(&aux_list, i, (uintptr_t)&out);

		munit_assert(validate_filter(out,i));
	}

	cff_list_clear(&aux_list, NULL);

	return MUNIT_OK;
}

TESTDEF(list_map) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;
	

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, sizeof(int));

	SKIP_ON_ERR(cff_list_map(list, map, &aux_list, sizeof(int), NULL));

	for (uint64_t i = 0; i < INI_LEN; i++)
	{
		int out = 0;
		test_data from;
		cff_list_get(&aux_list, i, (uintptr_t)&out);
		cff_list_get(list, i, (uintptr_t)&from);
		munit_assert(validate_map(from,out,i));
	}

	cff_list_clear(&aux_list, NULL);

	return MUNIT_OK;
}

TESTDEF(list_equal_true) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));

	uint8_t eq = cff_list_equal(list, &aux_list);

	cff_list_clear(&aux_list, NULL);

	munit_assert(eq);

	return MUNIT_OK;
}

TESTDEF(list_equal_false) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));
	test_data s = { 0 };
	cff_list_set(&aux_list, 2, (uintptr_t)&s);

	uint8_t eq = cff_list_equal(list, &aux_list);

	cff_list_clear(&aux_list, NULL);

	munit_assert(!eq);

	return MUNIT_OK;
}

TESTDEF(list_equal_cpm_true) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));

	uint8_t eq = cff_list_equal_cmp(list, &aux_list, compare);

	cff_list_clear(&aux_list, NULL);

	munit_assert(eq);

	return MUNIT_OK;
}

TESTDEF(list_equal_cmp_false) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));
	test_data s = { 0 };
	cff_list_set(&aux_list, 2, (uintptr_t)&s);

	uint8_t eq = cff_list_equal_cmp(list, &aux_list, compare);

	cff_list_clear(&aux_list, NULL);

	munit_assert(!eq);

	return MUNIT_OK;
}

TESTDEF(list_find) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, (int)INI_LEN);

	test_data s = data_new_at_index(3);
	test_data out = { 0 };
	uint64_t idx;
	cff_list_find(list, (uintptr_t)&s, &idx, (uintptr_t)&out);

	munit_assert(idx == 3);
	ASSERT_EQUALS(s, out);

	return MUNIT_OK;
}

TESTDEF(list_find_cmp) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, (int)INI_LEN);

	test_data s = data_new_at_index(3);
	test_data out = { 0 };
	uint64_t idx;
	cff_list_find_cmp(list, (uintptr_t)&s, &idx, (uintptr_t)&out, compare);

	munit_assert(idx == 3);
	ASSERT_EQUALS(s, out);

	return MUNIT_OK;
}

TESTDEF(list_count) {
	cff_list* list = (cff_list*)munit_data;
	
	uint64_t cc = 0;
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i%2);
		cc += i % 2;
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint64_t count = cff_list_count(list, (uintptr_t)(&data));
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(list_count_cmp) {
	cff_list* list = (cff_list*)munit_data;
	
	uint64_t cc = 0;
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cc += i % 2;
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint64_t count = cff_list_count_cmp(list, (uintptr_t)(&data), compare);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(list_any_true) {
	cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_list_any(list, (uintptr_t)(&data));
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(list_any_cmp_true) {
	cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_list_any_cmp(list, (uintptr_t)(&data), compare);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(list_all_false) {
cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_list_all(list, (uintptr_t)(&data));
	munit_assert(!exist);
	return MUNIT_OK;
}

TESTDEF(list_all_cmp_false) {
cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_list_all_cmp(list, (uintptr_t)(&data), compare);
	munit_assert(!exist);
	return MUNIT_OK;
}

TESTDEF(list_any_false) {
cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(2);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_list_any(list, (uintptr_t)(&data));
	munit_assert(!exist);
	return MUNIT_OK;
}

TESTDEF(list_any_cmp_false) {
cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(2);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_list_any_cmp(list, (uintptr_t)(&data), compare);
	munit_assert(!exist);
	return MUNIT_OK;
}

TESTDEF(list_all_true) {
cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(1);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_list_all(list, (uintptr_t)(&data));
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(list_all_cmp_true) {
	cff_list* list = (cff_list*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = data_new_at_index(1);
		SKIP_ON_ERR(cff_list_add(list, (uintptr_t)(&data), NULL));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_list_all_cmp(list, (uintptr_t)(&data), compare);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(list_reverse) {
	cff_list* list = (cff_list*)munit_data;
	
	list_arange(list, 0, (int)INI_LEN);

	cff_list_reverse(list);


	for (int i = (int)INI_LEN - 1, j = 0; i >= 0; i--, j++)
	{
		test_data data = data_new_at_index(i);
		test_data out = { 0 };
		cff_list_get(list, j, (uintptr_t)&out);
		ASSERT_EQUALS(data, out);
	}

	return MUNIT_OK;
}

TESTDEF(list_sort) {
	cff_list* list = (cff_list*)munit_data;
	
	cff_list aux_list;

	list_arange(list, 0, (int)INI_LEN);

	cff_list_create(&aux_list, DATA_SIZE);

	SKIP_ON_ERR(cff_list_clone(list, &aux_list, NULL));

	cff_list_reverse(&aux_list);

	cff_list_sort(&aux_list, compare);

	uint8_t eq = cff_list_equal(list, &aux_list);

	cff_list_clear(&aux_list, NULL);

	munit_assert(eq);

	return MUNIT_OK;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_list* list = malloc(sizeof(cff_list));
	if (list) *list = (cff_list){ 0 };
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


int test_list(int argc, char* const* argv) {

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

	MunitSuite suite = { "/list",tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}