#include "utils.h"

static void *setup(const MunitParameter params[], void *user_data)
{
    queue(int) *my_arr = (queue(int) *)malloc(sizeof(queue(int)));
    queue_create(int)(my_arr, 10);

    for (int i = 0; i < my_arr->lenght; i++)
        my_arr->buffer[i] = 0;
    return my_arr;
}

static void clear(void *data)
{
    queue(int) *arr = (queue(int) *)data;
    free(arr->buffer);
    free(arr);
}

TEST_FUNC(test_enqueue)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    for (int i = 0; i < 10; i++)
    {
        int v = queue_dequeue(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_dequeue)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    for (int i = 0; i < 10; i++)
    {
        int v = queue_dequeue(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_first)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    for (int i = 0; i < 10; i++)
    {
        int v = queue_first(int)(my_arr);
        queue_dequeue(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_last)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
        int v = queue_last(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_clear)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    queue_clear(int)(my_arr);
    int l = my_arr->count;
    assert(l == 0);

    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    queue(int) *my_arr = user_data;
    queue(int) other, *other_ptr = &other;

    queue_create(int)(other_ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    queue_copy(int)(my_arr, &other_ptr, 0, 5);

    for (int i = 0; i < 5; i++)
    {
        int v = queue_dequeue(int)(other_ptr);
        assert(v == i);
    }

    queue_free(int)(other_ptr);
    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    queue(int) *my_arr = user_data;
    queue(int) other, *other_ptr = &other;

    queue_create(int)(other_ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }
    queue_clone(int)(my_arr, &other_ptr);

    bool res = queue_equal(int)(my_arr, other_ptr);

    queue_free(int)(other_ptr);

    assert(res);
    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    queue(int) *my_arr = user_data;
    queue(int) other, *other_ptr = &other;

    queue_create(int)(other_ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }
    queue_clone(int)(my_arr, &other_ptr);

    bool res = queue_equal(int)(my_arr, other_ptr);

    queue_free(int)(other_ptr);

    assert(res);
    return MUNIT_OK;
}

TEST_FUNC(test_fill)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }
    queue_fill(int)(my_arr, 5);
    bool res = queue_all(int)(my_arr, 5);
    assert(res);
    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }
    queue_fill(int)(my_arr, 5);

    bool res1 = queue_all(int)(my_arr, 5);

    queue_enqueue(int)(my_arr, 9);

    bool res2 = queue_all(int)(my_arr, 5);

    assert(res1 && !res2);

    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }
    queue_fill(int)(my_arr, 5);

    bool res1 = queue_all_cmp(int)(my_arr, 5, int_cmp);

    queue_enqueue(int)(my_arr, 9);

    bool res2 = queue_all_cmp(int)(my_arr, 5, int_cmp);

    assert(res1 && !res2);

    return MUNIT_OK;
}

TEST_FUNC(test_any)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }
    queue_fill(int)(my_arr, 5);

    bool res1 = queue_any(int)(my_arr, 9);

    queue_enqueue(int)(my_arr, 9);

    bool res2 = queue_any(int)(my_arr, 9);

    assert(!res1 && res2);

    return MUNIT_OK;
}

TEST_FUNC(test_any_cmp)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }
    queue_fill(int)(my_arr, 5);

    bool res1 = queue_any_cmp(int)(my_arr, 9, int_cmp);

    queue_enqueue(int)(my_arr, 9);

    bool res2 = queue_any_cmp(int)(my_arr, 9, int_cmp);

    assert(!res1 && res2);

    return MUNIT_OK;
}

TEST_FUNC(test_find)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    int pos = queue_find(int)(my_arr, 3);
    int pos1 = queue_find(int)(my_arr, -1);

    assert(pos == 3 && pos1 == -1);

    return MUNIT_OK;
}

TEST_FUNC(test_find_cmp)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    int pos = queue_find_cmp(int)(my_arr, 3, int_cmp);
    int pos1 = queue_find_cmp(int)(my_arr, -1, int_cmp);

    assert(pos == 3 && pos1 == -1);

    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i % 2);
    }

    int pos = queue_count(int)(my_arr, 1);
    int pos1 = queue_count(int)(my_arr, 0);

    assert(pos == 5);
    assert(pos1 == 5);

    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i % 2);
    }

    int pos = queue_count_cmp(int)(my_arr, 0, int_cmp);
    int pos1 = queue_count_cmp(int)(my_arr, 1, int_cmp);

    assert(pos == 5);
    assert(pos1 == 5);

    return MUNIT_OK;
}

TEST_FUNC(test_resize)
{
    queue(int) *my_arr = user_data;
    queue_resize(int)(my_arr, 15);

    assert(my_arr->lenght == 15);

    for (size_t i = 0; i < 15; i++)
    {
        queue_enqueue(int)(my_arr, i % 2);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    queue(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    queue_reverse(int)(my_arr);

    for (int i = 9; i >= 0; i--)
    {
        int v = queue_dequeue(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_lenght)
{
    queue(int) *my_arr = user_data;

    assert(my_arr->lenght == 10);

    queue_resize(int)(my_arr, 15);

    assert(my_arr->lenght == 15);

    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    queue(int) *my_arr = user_data;

    queue(int) other, *other_ptr = &other;
    queue_create(int)(other_ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
        queue_enqueue(int)(other_ptr, i + 10);
    }

    queue_join(int)(my_arr, other_ptr);

    for (int i = 0; i < 20; i++)
    {
        int v = queue_dequeue(int)(my_arr);
        assert(v == i);
    }
    queue_free(int)(other_ptr);
    return MUNIT_OK;
}

TEST_FUNC(test_map)
{
    queue(int) *my_arr = user_data;
    int out[10] = {0};
    queue(int) out_queue;
    out_queue.buffer = out;
    out_queue.lenght = 10;

    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    out_queue.count = my_arr->count;
    queue_map(int)(my_arr, &(out_queue.buffer), mul_by_2);

    bool res = queue_all_cmp(int)(&out_queue, 0, is_even);
    assert(!res);
    return MUNIT_OK;
}

TEST_FUNC(test_filter)
{
    queue(int) *my_arr = user_data;
    int out[10] = {0};
    queue(int) out_queue;
    out_queue.buffer = out;
    out_queue.count = 0;
    out_queue.lenght = 10;

    for (size_t i = 0; i < 10; i++)
    {
        queue_enqueue(int)(my_arr, i);
    }

    queue_filter(int)(my_arr, &(out_queue.buffer), filter_even, &(out_queue.count));
    bool res = queue_all_cmp(int)(&out_queue, 0, is_even);
    assert(res);
    return MUNIT_OK;
}

static MunitTest tests[] = {
        TEST("/enqueue", test_enqueue),
        TEST("/dequeue", test_dequeue),
        TEST("/first", test_first),
        TEST("/last", test_last),
        TEST("/clear", test_clear),
        TEST("/copy", test_copy),
        TEST("/clone", test_clone),
        TEST("/equal", test_equal),
        TEST("/fill", test_fill),
        TEST("/find", test_find),
        TEST("/find_cmp", test_find_cmp),
        TEST("/resize", test_resize),
        TEST("/count", test_count),
        TEST("/count_cmp", test_count_cmp),
        TEST("/all", test_all),
        TEST("/all_cmp", test_all_cmp),
        TEST("/any", test_any),
        TEST("/any_cmp", test_any_cmp),
        TEST("/join", test_join),
        TEST("/reverse", test_reverse),
        TEST("/lenght", test_lenght),
        TEST("/map", test_map),
        TEST("/filter", test_filter),
        {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL} };
MunitSuite queue_suite = { "/queue", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };