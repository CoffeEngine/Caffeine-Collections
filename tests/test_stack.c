#include <stdio.h>
#include "caffeine_stack.h"
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

#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], cff_stack* stack)

TESTDEF(stack_create) {
	caffeine_stack_create(stack, DATA_SIZE, INI_LEN, NULL);

	munit_assert(stack->buffer != 0);
	munit_assert(stack->count == 0);
	munit_assert(stack->data_size == DATA_SIZE);
	munit_assert(stack->lenght == INI_LEN);

	return MUNIT_OK;
}
TESTDEF(stack_resize) {
	uint64_t n_size = (uint64_t)munit_rand_int_range(10, 100);
	caffeine_stack_resize(stack, n_size, NULL);

	for (size_t i = 0; i < n_size; i++)
	{
		vec3 v = { .x = i, .y = i, .z = 1 };
		caffeine_stack_push(stack, &v, NULL);
	}

	vec3* buffer = (vec3*)stack->buffer;

	for (size_t i = 0; i < n_size; i++)
	{
		munit_assert(buffer[i].x == i);
	}

	return MUNIT_OK;
}
TESTDEF(stack_push) {

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 v = { .x = i, .y = i, .z = 1 };
		caffeine_stack_push(stack, &v, NULL);
	}

	munit_assert(stack->count == INI_LEN);

	vec3* buffer = (vec3*)stack->buffer;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		munit_assert(buffer[i].x == i);
	}

	return MUNIT_OK;
}
TESTDEF(stack_pop) {
	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 v = { .x = i, .y = i, .z = 1 };
		caffeine_stack_push(stack, &v, NULL);
	}

	for (size_t i = 0, v = INI_LEN - 1; i < INI_LEN; v--, i++)
	{
		vec3 out;
		caffeine_stack_pop(stack, &out, NULL);

		munit_assert(out.x == v);
	}

	munit_assert(stack->count == 0);

	return MUNIT_OK;
}
TESTDEF(stack_reverse) {

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 v = { .x = i, .y = i, .z = 1 };
		caffeine_stack_push(stack, &v, NULL);
	}

	caffeine_stack_reverse(stack);

	vec3* buffer = (vec3*)stack->buffer;

	for (size_t i = 0, v = INI_LEN - 1; i < INI_LEN; v--, i++)
	{
		munit_assert(buffer[i].x == v);
	}

	return MUNIT_OK;
}
TESTDEF(stack_free) {
	caffeine_stack_free(stack, NULL);

	munit_assert_null(stack->buffer);
	munit_assert(stack->count == 0);
	munit_assert(stack->data_size == 0);
	munit_assert(stack->lenght == 0);

	return MUNIT_OK;
}
TESTDEF(stack_clear) {

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 v = { .x = i, .y = i, .z = 1 };
		caffeine_stack_push(stack, &v, NULL);
	}

	caffeine_stack_clear(stack);

	munit_assert(stack->count == 0);

	vec3 tmp;
	uint8_t res = caffeine_stack_pop(stack, &tmp, NULL);
	munit_assert(res == 0);

	return MUNIT_OK;
}
TESTDEF(stack_copy) {
	cff_stack tmp_stack;
	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 v = { .x = i, .y = i, .z = 1 };
		caffeine_stack_push(stack, &v, NULL);
	}

	caffeine_stack_create(&tmp_stack, stack->data_size, INI_LEN / 2, NULL);
	caffeine_stack_copy(stack, &tmp_stack, 0, INI_LEN / 2, NULL);

	for (size_t i = 0; i < INI_LEN / 2; i++)
	{
		vec3* tmp = (vec3*)tmp_stack.buffer;
		munit_assert(tmp[i].x == i);
	}

	caffeine_stack_free(&tmp_stack, NULL);
	return MUNIT_OK;
}
TESTDEF(stack_clone) {
	cff_stack tmp_stack;
	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 v = { .x = i, .y = i, .z = 1 };
		caffeine_stack_push(stack, &v, NULL);
	}

	caffeine_stack_create(&tmp_stack, stack->data_size, INI_LEN, NULL);
	caffeine_stack_clone(stack, &tmp_stack, NULL);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3* tmp = (vec3*)tmp_stack.buffer;
		munit_assert(tmp[i].x == i);
	}

	caffeine_stack_free(&tmp_stack, NULL);
	return MUNIT_OK;
}
TESTDEF(stack_top) {
	for (size_t i = 0; i < INI_LEN; i++)
	{
		vec3 v = { .x = i, .y = i, .z = 1 };
		caffeine_stack_push(stack, &v, NULL);

		vec3 out;
		caffeine_stack_top(stack, &out);

		munit_assert(v.x == out.x);
	}
	return MUNIT_OK;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_stack* stack = malloc(sizeof(cff_stack));
	return stack;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_stack* stack = malloc(sizeof(cff_stack));
	caffeine_stack_create(stack, DATA_SIZE, INI_LEN, NULL);
	return stack;
}

static void test_tear_down(void* fixture) {
	caffeine_stack_free(fixture, NULL);
	free(fixture);
}

static void test_tear_down_free(void* fixture) {
	free(fixture);
}

int test_stack(int argc, char* const argv[]) {

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