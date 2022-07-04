#include "utils.h"



TEST_FUNC(test_insert)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    array_insert(int)(my_arr, v1, 0);
    array_insert(int)(my_arr, v2, 0);
    array_insert(int)(my_arr, v3, 0);

    munit_assert(my_arr->buffer[0] == v3);
    munit_assert(my_arr->buffer[1] == v2);
    munit_assert(my_arr->buffer[2] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_set)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    array_set(int)(my_arr, v1, 0);
    array_set(int)(my_arr, v2, 1);
    array_set(int)(my_arr, v3, 2);

    munit_assert(my_arr->buffer[3] == 0);
    munit_assert(my_arr->buffer[2] == v3);
    munit_assert(my_arr->buffer[1] == v2);
    munit_assert(my_arr->buffer[0] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    array_set(int)(my_arr, v1, 0);
    array_set(int)(my_arr, v2, 1);
    array_set(int)(my_arr, v3, 2);

    array_remove(int)(my_arr, 1);

    munit_assert(my_arr->buffer[2] == 0);
    munit_assert(my_arr->buffer[1] == v3);
    munit_assert(my_arr->buffer[0] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_get)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    array_set(int)(my_arr, v1, 0);
    array_set(int)(my_arr, v2, 1);
    array_set(int)(my_arr, v3, 2);

    int g1 = array_get(int)(my_arr, 0);
    int g2 = array_get(int)(my_arr, 1);
    int g3 = array_get(int)(my_arr, 2);

    munit_assert(g1 == v1);
    munit_assert(g2 == v2);
    munit_assert(g3 == v3);

    return MUNIT_OK;
}

TEST_FUNC(test_first)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    int arr[3] = {v1, v2, v3};

    array_set(int)(my_arr, v1, 0);
    array_set(int)(my_arr, v2, 1);
    array_set(int)(my_arr, v3, 2);

    for (size_t i = 0; i < 3; i++)
    {
        int g = array_first(int)(my_arr);
        munit_assert(g == arr[i]);
        array_remove(int)(my_arr, 0);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_last)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    array_set(int)(my_arr, v1, my_arr->lenght - 1);
    int g1 = array_last(int)(my_arr);
    munit_assert(g1 == v1);
    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    array(int) *my_arr = user_data;
    for (size_t z = 0; z < 1000; z++)
    {
        size_t start = munit_rand_uint32() % 5;
        size_t len = munit_rand_int_range(1, my_arr->lenght - start - 1);

        int *buff = malloc(sizeof(int) * len);

        for (size_t i = 0; i < my_arr->lenght; i++)
        {
            array_set(int)(my_arr, munit_rand_uint32(), i);
        }

        array_copy(int)(my_arr, &buff, start, start + len);

        for (size_t i = start, c = 0; i < start + len; i++, c++)
        {
            munit_assert(array_get(int)(my_arr, i) == buff[c]);
        }

        free(buff);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, munit_rand_uint32(), i);
    }

    int *buff = malloc(sizeof(int) * my_arr->lenght);
    array_clone(int)(my_arr, &buff);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(array_get(int)(my_arr, i) == buff[i]);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    array(int) other_arr = {.buffer = 0, .lenght = 0};
    array(int) *my_arr = user_data;

    array_create(int)(&other_arr, my_arr->lenght);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        uint32_t v = munit_rand_uint32();
        array_set(int)(my_arr, v, i);
        array_set(int)(&other_arr, v, i);
    }

    bool eq = array_equal(int)(&other_arr, my_arr);
    munit_assert(eq);

    array_free(int)(&other_arr);
    return MUNIT_OK;
}

TEST_FUNC(test_fill)
{
    array(int) *my_arr = user_data;

    uint32_t number = munit_rand_uint32();

    array_fill(int)(my_arr, number);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(array_get(int)(my_arr, i) == number);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_find)
{
    array(int) *my_arr = user_data;
    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i, i);
        int pos = array_find(int)(my_arr, i);
        munit_assert(pos == i);
    }

    int pos = array_find(int)(my_arr, -342);
    munit_assert(pos == -1);

    return MUNIT_OK;
}

TEST_FUNC(test_find_cmp)
{
    array(int) *my_arr = user_data;
    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i, i);
        int pos = array_find_cmp(int)(my_arr, i, int_cmp);
        munit_assert(pos == i);
    }

    int pos = array_find_cmp(int)(my_arr, -342, int_cmp);
    munit_assert(pos == -1);

    return MUNIT_OK;
}

TEST_FUNC(test_resize)
{
    array(int) *my_arr = user_data;
    size_t i = 0;
    for (; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i, i);
    }
    array_resize(int)(my_arr, my_arr->lenght * 2);
    for (; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i, i);
    }
    for (i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(array_get(int)(my_arr, i) == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    array(int) *my_arr = user_data;

    size_t c = 0;
    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        c += i % 2;
        array_set(int)(my_arr, i % 2, i);
    }
    munit_assert(c == array_count(int)(my_arr, 1));
    munit_assert(0 == array_count(int)(my_arr, -1));
    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    array(int) *my_arr = user_data;

    size_t c = 0;
    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        c += i % 2;
        array_set(int)(my_arr, i % 2, i);
    }
    munit_assert(c == array_count_cmp(int)(my_arr, 1, int_cmp));
    munit_assert(0 == array_count_cmp(int)(my_arr, -1, int_cmp));
    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, 1, i);
    }

    munit_assert(array_all(int)(my_arr, 1));
    munit_assert(array_all(int)(my_arr, 0) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i % 2, i);
    }

    munit_assert(array_all_cmp(int)(my_arr, 0, less_than_two));
    munit_assert(array_all_cmp(int)(my_arr, 0, is_even) == false);
    munit_assert(array_all_cmp(int)(my_arr, 2, int_cmp) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_any)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i % 2, i);
    }

    munit_assert(array_any(int)(my_arr, 0));
    munit_assert(array_any(int)(my_arr, 1));
    munit_assert(array_any(int)(my_arr, 2) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_any_cmp)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i % 2, i);
    }

    munit_assert(array_any_cmp(int)(my_arr, 0, less_than_two));
    munit_assert(array_any_cmp(int)(my_arr, 0, is_even));
    munit_assert(array_any_cmp(int)(my_arr, 2, int_cmp) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    array(int) other_arr = {.buffer = 0, .lenght = 0};
    array(int) *my_arr = user_data;

    array_create(int)(&other_arr, my_arr->lenght);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        uint32_t v = munit_rand_uint32();
        array_set(int)(my_arr, v, i);
        array_set(int)(&other_arr, v, i);
    }

    size_t i_len = my_arr->lenght;
    array_join(int)(my_arr, &other_arr);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(array_get(int)(my_arr, i) == array_get(int)(my_arr, i + i_len));
    }

    array_free(int)(&other_arr);
    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i, i);
    }

    array_reverse(int)(my_arr);

    for (size_t i = 0, v = my_arr->lenght - 1; i < my_arr->lenght; i++, v--)
    {
        munit_assert(array_get(int)(my_arr, i) == v);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_lenght)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i, i);
    }

    for (size_t i = 0; i < 5; i++)
    {
        size_t n_size = munit_rand_int_range(5, 15);
        array_resize(int)(my_arr, n_size);
        munit_assert(array_lenght(int)(my_arr) == n_size);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_map)
{
    array(int) *my_arr = user_data;
    int *out;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i, i);
    }

    array_map(int)(my_arr, &out, mul_by_2);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(array_get(int)(my_arr, i) * 2 == out[i]);
    }

    free(out);
    return MUNIT_OK;
}

TEST_FUNC(test_filter)
{
    array(int) *my_arr = user_data;
    int *out;
    size_t vec_len;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        array_set(int)(my_arr, i, i);
    }

    array_filter(int)(my_arr, &out, filter_even, &vec_len);
    munit_assert(vec_len == 5);
    for (size_t i = 0; i < vec_len; i++)
    {
        munit_assert(out[i] == 1 + (i * 2));
    }

    free(out);
    return MUNIT_OK;
}

static void *setup(const MunitParameter params[], void *user_data)
{
    array(int) *my_arr = (array(int) *)malloc(sizeof(array(int)));
    array_create(int)(my_arr, 10);

    for (int i = 0; i < my_arr->lenght; i++)
        my_arr->buffer[i] = 0;
    return my_arr;
}

static void clear(void *data)
{
    array(int) *arr = (array(int) *)data;
    free(arr->buffer);
    free(arr);
}

static MunitTest tests[] = {
        TEST("/insert", test_insert),
        TEST("/set", test_set),
        TEST("/remove", test_remove),
        TEST("/get", test_get),
        TEST("/first", test_first),
        TEST("/last", test_last),
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
MunitSuite array_suite = { "/array", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };