#include "utils.h"

static void *setup(const MunitParameter params[], void *user_data)
{
    stack(int) *my_arr = (stack(int) *)malloc(sizeof(stack(int)));
    stack_create(int)(my_arr, 10);

    for (int i = 0; i < my_arr->lenght; i++)
        my_arr->buffer[i] = 0;
    return my_arr;
}

static void clear(void *data)
{
    stack(int) *arr = (stack(int) *)data;
    free(arr->buffer);
    free(arr);
}

TEST_FUNC(test_push)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }

    for (int i = 9; i >= 0; i--)
    {
        int v = stack_pop(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_pop)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }

    for (int i = 9; i >= 0; i--)
    {
        int v = stack_pop(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_top)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }

    for (int i = 9; i >= 0; i--)
    {
        int v = stack_top(int)(my_arr);
        stack_pop(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_clear)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }

    stack_clear(int)(my_arr);
    int l = my_arr->count;
    assert(l == 0);

    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    stack(int) *my_arr = user_data;
    stack(int) other, *other_ptr = &other;

    stack_create(int)(other_ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }

    stack_copy(int)(my_arr, &other_ptr, 0, 5);

    for (int i = 4; i >= 0; i--)
    {
        int v = stack_pop(int)(other_ptr);
        assert(v == i);
    }

    stack_free(int)(other_ptr);
    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    stack(int) *my_arr = user_data;
    stack(int) other, *other_ptr = &other;

    stack_create(int)(other_ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }
    stack_clone(int)(my_arr, &other_ptr);

    bool res = stack_equal(int)(my_arr, other_ptr);

    stack_free(int)(other_ptr);

    assert(res);
    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    stack(int) *my_arr = user_data;
    stack(int) other, *other_ptr = &other;

    stack_create(int)(other_ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }
    stack_clone(int)(my_arr, &other_ptr);

    bool res = stack_equal(int)(my_arr, other_ptr);

    stack_free(int)(other_ptr);

    assert(res);
    return MUNIT_OK;
}

TEST_FUNC(test_fill)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }
    stack_fill(int)(my_arr, 5);
    bool res = stack_all(int)(my_arr, 5);
    assert(res);
    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        stack_push(int)(my_arr, i);
    }
    stack_fill(int)(my_arr, 5);

    bool res1 = stack_all(int)(my_arr, 5);

    stack_push(int)(my_arr, 9);

    bool res2 = stack_all(int)(my_arr, 5);

    assert(res1 && !res2);

    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        stack_push(int)(my_arr, i);
    }
    stack_fill(int)(my_arr, 5);

    bool res1 = stack_all_cmp(int)(my_arr, 5, int_cmp);

    stack_push(int)(my_arr, 9);

    bool res2 = stack_all_cmp(int)(my_arr, 5, int_cmp);

    assert(res1 && !res2);

    return MUNIT_OK;
}

TEST_FUNC(test_any)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        stack_push(int)(my_arr, i);
    }
    stack_fill(int)(my_arr, 5);

    bool res1 = stack_any(int)(my_arr, 9);

    stack_push(int)(my_arr, 9);

    bool res2 = stack_any(int)(my_arr, 9);

    assert(!res1 && res2);

    return MUNIT_OK;
}

TEST_FUNC(test_any_cmp)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        stack_push(int)(my_arr, i);
    }
    stack_fill(int)(my_arr, 5);

    bool res1 = stack_any_cmp(int)(my_arr, 9, int_cmp);

    stack_push(int)(my_arr, 9);

    bool res2 = stack_any_cmp(int)(my_arr, 9, int_cmp);

    assert(!res1 && res2);

    return MUNIT_OK;
}

TEST_FUNC(test_find)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        stack_push(int)(my_arr, i);
    }

    int pos = stack_find(int)(my_arr, 3);
    int pos1 = stack_find(int)(my_arr, -1);

    assert(pos == 3 && pos1 == -1);

    return MUNIT_OK;
}

TEST_FUNC(test_find_cmp)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 9; i++)
    {
        stack_push(int)(my_arr, i);
    }

    int pos = stack_find_cmp(int)(my_arr, 3, int_cmp);
    int pos1 = stack_find_cmp(int)(my_arr, -1, int_cmp);

    assert(pos == 3 && pos1 == -1);

    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i % 2);
    }

    int pos = stack_count(int)(my_arr, 1);
    int pos1 = stack_count(int)(my_arr, 0);

    assert(pos == 5);
    assert(pos1 == 5);

    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i % 2);
    }

    int pos = stack_count_cmp(int)(my_arr, 0, int_cmp);
    int pos1 = stack_count_cmp(int)(my_arr, 1, int_cmp);

    assert(pos == 5);
    assert(pos1 == 5);

    return MUNIT_OK;
}

TEST_FUNC(test_resize)
{
    stack(int) *my_arr = user_data;
    stack_resize(int)(my_arr, 15);

    assert(my_arr->lenght == 15);

    for (size_t i = 0; i < 15; i++)
    {
        stack_push(int)(my_arr, i % 2);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    stack(int) *my_arr = user_data;
    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }

    stack_reverse(int)(my_arr);

    for (size_t i = 0; i < 10; i++)
    {
        int v = stack_pop(int)(my_arr);
        assert(v == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_lenght)
{
    stack(int) *my_arr = user_data;

    assert(my_arr->lenght == 10);

    stack_resize(int)(my_arr, 15);

    assert(my_arr->lenght == 15);

    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    stack(int) *my_arr = user_data;

    stack(int) other, *other_ptr = &other;
    stack_create(int)(other_ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
        stack_push(int)(other_ptr, i + 10);
    }

    stack_join(int)(my_arr, other_ptr);

    for (int i = 19; i >= 0; i--)
    {
        int v = stack_pop(int)(my_arr);
        assert(v == i);
    }
    stack_free(int)(other_ptr);
    return MUNIT_OK;
}

TEST_FUNC(test_map)
{
    stack(int) *my_arr = user_data;
    int out[10] = {0};
    stack(int) out_stack;
    out_stack.buffer = out;
    out_stack.lenght = 10;

    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }

    out_stack.count = my_arr->count;
    stack_map(int)(my_arr, &(out_stack.buffer), mul_by_2);

    bool res = stack_all_cmp(int)(&out_stack, 0, is_even);
    assert(!res);
    return MUNIT_OK;
}

TEST_FUNC(test_filter)
{
    stack(int) *my_arr = user_data;
    int out[10] = {0};
    stack(int) out_stack;
    out_stack.buffer = out;
    out_stack.count = 0;
    out_stack.lenght = 10;

    for (size_t i = 0; i < 10; i++)
    {
        stack_push(int)(my_arr, i);
    }

    stack_filter(int)(my_arr, &(out_stack.buffer), filter_even, &(out_stack.count));
    bool res = stack_all_cmp(int)(&out_stack, 0, is_even);
    assert(res);
    return MUNIT_OK;
}



static MunitTest tests[] = {
    TEST("/push", test_push),
    TEST("/pop", test_pop),
    TEST("/top", test_top),
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
MunitSuite stack_suite = { "/stack", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };