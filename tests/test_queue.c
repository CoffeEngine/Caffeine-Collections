#include "caffeine_queue.h"
#include "test_defs.h"



TESTDEF(queue_create) {
	cff_queue* queue = (cff_queue*)munit_data;

	cff_queue_create(queue, DATA_SIZE, INI_LEN, NULL);
	munit_assert_not_null((void*)(queue->buffer));
	munit_assert(queue->count == 0);
	munit_assert(queue->data_size == DATA_SIZE);
	munit_assert(queue->lenght == INI_LEN);
	return MUNIT_OK;
}

TESTDEF(queue_resize) {
	cff_queue* queue = (cff_queue*)munit_data;
	
	uint64_t n_size = (uint64_t)munit_rand_int_range(10, 100);
	cff_queue_resize(queue, n_size, NULL);
	munit_assert(n_size == queue->lenght);

	for (size_t i = 0; i < n_size; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_queue_enqueue(queue, (uintptr_t)&v, NULL);
	}

	for (size_t i = 0; i < n_size; i++)
	{
		test_data* tmp = (test_data*)queue->buffer;
		munit_assert(tmp[i].x == i);
	}

	return MUNIT_OK;
}

TESTDEF(queue_enqueue) {
cff_queue* queue = (cff_queue*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_queue_enqueue(queue, (uintptr_t)&v,NULL);
	}

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data* tmp = (test_data*)queue->buffer;
		munit_assert(tmp[i].x == i);
	}

	return MUNIT_OK;
}

TESTDEF(queue_reverse) {
	cff_queue* queue = (cff_queue*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_queue_enqueue(queue, (uintptr_t)&v, NULL);
	}
	cff_queue_reverse(queue);
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data* tmp = (test_data*)queue->buffer;
		munit_assert(tmp[i].x == (INI_LEN-1) - i);
	}

	return MUNIT_OK;
}

TESTDEF(queue_free) {
	cff_queue* queue = (cff_queue*)munit_data;
	
	cff_queue_free(queue, NULL);
	
	munit_assert_null((void*)queue->buffer);
	munit_assert(queue->count == 0);
	munit_assert(queue->data_size == 0);
	munit_assert(queue->lenght == 0);
	return MUNIT_OK;
}

TESTDEF(queue_clear) {
	cff_queue* queue = (cff_queue*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_queue_enqueue(queue, (uintptr_t)&v, NULL);
	}

	cff_queue_clear(queue);

	munit_assert(queue->count == 0);

	test_data tmp = {0};
	uint8_t res = cff_queue_dequeue(queue, (uintptr_t)&tmp, NULL);
	munit_assert(res == 0);

	return MUNIT_OK;
}

TESTDEF(queue_copy) {
	cff_queue* queue = (cff_queue*)munit_data;
	
	cff_queue tmp_queue;
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_queue_enqueue(queue, (uintptr_t)&v, NULL);
	}

	cff_queue_create(&tmp_queue, queue->data_size, INI_LEN / 2, NULL);
	cff_queue_copy(queue, &tmp_queue, 0, INI_LEN / 2, NULL);

	for (size_t i = 0; i < INI_LEN/2; i++)
	{
		test_data* tmp = (test_data*)tmp_queue.buffer;
		munit_assert(tmp[i].x == i);
	}

	cff_queue_free(&tmp_queue, NULL);
	return MUNIT_OK;
}

TESTDEF(queue_clone) {
	cff_queue* queue = (cff_queue*)munit_data;
	
	cff_queue tmp_queue;
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_queue_enqueue(queue, (uintptr_t)&v, NULL);
	}

	cff_queue_create(&tmp_queue, queue->data_size, INI_LEN, NULL);
	cff_queue_clone(queue, &tmp_queue, NULL);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data* tmp = (test_data*)tmp_queue.buffer;
		munit_assert(tmp[i].x == i);
	}

	cff_queue_free(&tmp_queue, NULL);
	return MUNIT_OK;
}

TESTDEF(queue_dequeue) {
	cff_queue* queue = (cff_queue*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data v = { .x = i, .y = i, .z = 1 };
		cff_queue_enqueue(queue, (uintptr_t)&v, NULL);
	}

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data tmp ={0};
		cff_queue_dequeue(queue, (uintptr_t)&tmp, NULL);
		munit_assert(tmp.x == i);
	}

	return MUNIT_OK;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_queue* queue = malloc(sizeof(cff_queue));
	if (queue) *queue = (cff_queue){ 0 };
	return queue;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_queue* queue = malloc(sizeof(cff_queue));
	cff_queue_create(queue, DATA_SIZE, INI_LEN, NULL);
	return queue;
}

static void test_tear_down(void* fixture) {
	cff_queue_free(fixture, NULL);
	free(fixture);
}

static void test_tear_down_free(void* fixture) {
	free(fixture);
}

int test_queue(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/queue_create", test_queue_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		{ "/queue_free", test_queue_free, test_setup, test_tear_down_free, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(queue_enqueue),
		TEST(queue_resize),
		TEST(queue_reverse),
		TEST(queue_clear),
		TEST(queue_copy),
		TEST(queue_clone),
		TEST(queue_dequeue),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/queue", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}