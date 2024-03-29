#include "caffeine_stack.h"
#include "test_defs.h"



TESTDEF(stack_create) {
	cff_stack* stack = (cff_stack*)munit_data;

	cff_stack_create(stack, DATA_SIZE, INI_LEN, NULL);

	munit_assert(stack->buffer != 0);
	munit_assert(stack->count == 0);
	munit_assert(stack->data_size == DATA_SIZE);
	munit_assert(stack->lenght == INI_LEN);

	return MUNIT_OK;
}
TESTDEF(stack_resize) {
	cff_stack* stack = (cff_stack*)munit_data;
	
	uint64_t n_size = (uint64_t)munit_rand_int_range(10, 100);
	cff_stack_resize(stack, n_size, NULL);

	for (size_t i = 0; i < n_size; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_stack_push(stack, (uintptr_t)&v, NULL);
	}

	test_data* buffer = (test_data*)stack->buffer;

	for (size_t i = 0; i < n_size; i++)
	{
		munit_assert(buffer[i].x == i);
	}

	return MUNIT_OK;
}
TESTDEF(stack_push) {
cff_stack* stack = (cff_stack*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_stack_push(stack, (uintptr_t)&v, NULL);
	}

	munit_assert(stack->count == INI_LEN);

	test_data* buffer = (test_data*)stack->buffer;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		munit_assert(buffer[i].x == i);
	}

	return MUNIT_OK;
}
TESTDEF(stack_pop) {
	cff_stack* stack = (cff_stack*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_stack_push(stack, (uintptr_t)&v, NULL);
	}

	for (int i = 0, v = (int)INI_LEN - 1; i < (int)INI_LEN; v--, i++)
	{
		test_data out= {0};
		cff_stack_pop(stack, (uintptr_t)&out, NULL);

		munit_assert(out.x == v);
	}

	munit_assert(stack->count == 0);

	return MUNIT_OK;
}
TESTDEF(stack_reverse) {
	cff_stack* stack = (cff_stack*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_stack_push(stack, (uintptr_t)&v, NULL);
	}

	cff_stack_reverse(stack);

	test_data* buffer = (test_data*)stack->buffer;

	for (int i = 0, v = (int)INI_LEN - 1; i < (int)INI_LEN; v--, i++)
	{
		munit_assert(buffer[i].x == v);
	}

	return MUNIT_OK;
}
TESTDEF(stack_free) {
	cff_stack* stack = (cff_stack*)munit_data;
	
	cff_stack_free(stack, NULL);

	munit_assert_null((void*)stack->buffer);
	munit_assert(stack->count == 0);
	munit_assert(stack->data_size == 0);
	munit_assert(stack->lenght == 0);

	return MUNIT_OK;
}
TESTDEF(stack_clear) {
cff_stack* stack = (cff_stack*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_stack_push(stack, (uintptr_t)&v, NULL);
	}

	cff_stack_clear(stack);

	munit_assert(stack->count == 0);

	test_data tmp ={0};
	uint8_t res = cff_stack_pop(stack, (uintptr_t)&tmp, NULL);
	munit_assert(res == 0);

	return MUNIT_OK;
}
TESTDEF(stack_copy) {
	cff_stack* stack = (cff_stack*)munit_data;
	
	cff_stack tmp_stack;
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_stack_push(stack, (uintptr_t)&v, NULL);
	}

	cff_stack_create(&tmp_stack, stack->data_size, INI_LEN / 2, NULL);
	cff_stack_copy(stack, &tmp_stack, 0, INI_LEN / 2, NULL);

	for (size_t i = 0; i < INI_LEN / 2; i++)
	{
		test_data* tmp = (test_data*)tmp_stack.buffer;
		munit_assert(tmp[i].x == i);
	}

	cff_stack_free(&tmp_stack, NULL);
	return MUNIT_OK;
}
TESTDEF(stack_clone) {
	cff_stack* stack = (cff_stack*)munit_data;
	
	cff_stack tmp_stack;
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_stack_push(stack, (uintptr_t)&v, NULL);
	}

	cff_stack_create(&tmp_stack, stack->data_size, INI_LEN, NULL);
	cff_stack_clone(stack, &tmp_stack, NULL);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data* tmp = (test_data*)tmp_stack.buffer;
		munit_assert(tmp[i].x == i);
	}

	cff_stack_free(&tmp_stack, NULL);
	return MUNIT_OK;
}
TESTDEF(stack_top) {
	cff_stack* stack = (cff_stack*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_stack_push(stack, (uintptr_t)&v, NULL);

		test_data out= {0};
		cff_stack_top(stack, (uintptr_t)&out);

		munit_assert(v.x == out.x);
	}
	return MUNIT_OK;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_stack* stack = malloc(sizeof(cff_stack));
	if (stack) *stack = (cff_stack){ 0 };
	return stack;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_stack* stack = malloc(sizeof(cff_stack));
	cff_stack_create(stack, DATA_SIZE, INI_LEN, NULL);
	return stack;
}

static void test_tear_down(void* fixture) {
	cff_stack_free(fixture, NULL);
	free(fixture);
}

static void test_tear_down_free(void* fixture) {
	free(fixture);
}

int test_stack(int argc, char* const* argv) {

	MunitTest tests[] = {
		{ "/stack_create", test_stack_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		{ "/stack_free", test_stack_free, test_setup, test_tear_down_free, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(stack_push),
		TEST(stack_pop),
		TEST(stack_resize),
		TEST(stack_reverse),
		TEST(stack_clear),
		TEST(stack_copy),
		TEST(stack_clone),
		TEST(stack_top),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/stack", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}