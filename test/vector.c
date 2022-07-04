#include "utils.h"


TEST_FUNC(test_insert)
{
    vector(int) *vec = user_data;

    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    vector_insert(int)(vec, v1, 0);
    vector_insert(int)(vec, v2, 0);
    vector_insert(int)(vec, v3, 0);

    munit_assert(vec->buffer[0] == v3);
    munit_assert(vec->buffer[1] == v2);
    munit_assert(vec->buffer[2] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_set)
{
    vector(int) *vec = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    vector_set(int)(vec, v1, 0);
    vector_set(int)(vec, v2, 1);
    vector_set(int)(vec, v3, 2);

    munit_assert(vec->buffer[3] == 0);
    munit_assert(vec->buffer[2] == v3);
    munit_assert(vec->buffer[1] == v2);
    munit_assert(vec->buffer[0] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_clear)
{
    vector(int) *vec = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    vector_set(int)(vec, v1, 0);
    vector_set(int)(vec, v2, 1);
    vector_set(int)(vec, v3, 2);

    vector_clear(int)(vec);

    assert(vec->count == 0);

    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    vector(int) *vec = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    vector_push_back(int)(vec, v1);
    vector_push_back(int)(vec, v2);
    vector_push_back(int)(vec, v3);

    vector_remove(int)(vec, 1);

    munit_assert(vec->buffer[2] == v3);
    munit_assert(vec->buffer[1] == v3);
    munit_assert(vec->buffer[0] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_get)
{
    vector(int) *vec = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    vector_set(int)(vec, v1, 0);
    vector_set(int)(vec, v2, 1);
    vector_set(int)(vec, v3, 2);

    int g1 = vector_get(int)(vec, 0);
    int g2 = vector_get(int)(vec, 1);
    int g3 = vector_get(int)(vec, 2);

    munit_assert(g1 == v1);
    munit_assert(g2 == v2);
    munit_assert(g3 == v3);

    return MUNIT_OK;
}

TEST_FUNC(test_first)
{
    vector(int) *vec = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    int arr[3] = {v1, v2, v3};

    vector_push_back(int)(vec, v1);
    vector_push_back(int)(vec, v2);
    vector_push_back(int)(vec, v3);

    for (size_t i = 0; i < 3; i++)
    {
        int g = vector_first(int)(vec);
        munit_assert(g == arr[i]);
        vector_pop_front(int)(vec);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_last)
{
    vector(int) *vec = user_data;
    for (size_t i = 0; i < 5; i++)
    {
        vector_push_back(int)(vec, i * 3);
        int g = vector_last(int)(vec);
        munit_assert(g == i * 3);
    }
    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    vector(int) *vec = user_data;
    vector(int) other_vec;
    for (size_t z = 0; z < 1000; z++)
    {
        size_t vec_len = 8;
        size_t start = munit_rand_uint32() % 5;
        size_t len = munit_rand_int_range(1, vec_len - start - 1);

        vector_create(int)(&other_vec, len + 2);

        for (size_t i = 0; i < vec_len; i++)
        {
            vector_push_back(int)(vec, munit_rand_uint32());
        }

        vector_copy(int)(vec, &other_vec, start, start + len);

        for (size_t i = start, c = 0; i < start + len; i++, c++)
        {
            munit_assert(vector_get(int)(vec, i) == other_vec.buffer[c]);
        }

        vector_free(int)(&other_vec);
    }
    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    vector(int) *vec = user_data;
    vector(int) other_vec;

    size_t vec_len = 8;

    vector_create(int)(&other_vec, vec_len + 2);

    for (size_t i = 0; i < vec_len; i++)
    {
        vector_push_back(int)(vec, munit_rand_uint32());
    }

    vector_clone(int)(vec, &other_vec);

    for (size_t i = 0; i < vec_len; i++)
    {
        munit_assert(vector_get(int)(vec, i) == other_vec.buffer[i]);
    }

    vector_free(int)(&other_vec);

    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    vector(int) *vec = user_data;
    vector(int) other_vec;

    size_t vec_len = 8;

    vector_create(int)(&other_vec, vec_len + 2);

    for (size_t i = 0; i < vec_len; i++)
    {
        vector_push_back(int)(vec, munit_rand_uint32());
    }

    vector_clone(int)(vec, &other_vec);

    bool eq = vector_equal(int)(vec, &other_vec);

    munit_assert(eq);

    vector_free(int)(&other_vec);

    return MUNIT_OK;
}

TEST_FUNC(test_fill)
{
    vector(int) *vec = user_data;
    int rnd = munit_rand_uint32();
    vector_fill(int)(vec, rnd);

    for (size_t i = 0; i < vector_lenght(int)(vec); i++)
    {
        int v = vector_get(int)(vec, i);
        assert(v == rnd);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_find)
{
    vector(int) *vec = user_data;
    int value = munit_rand_uint32();
    int pos = munit_rand_int_range(0, (vector_lenght(int)(vec)) / 2);
    for (size_t i = 0; i < vector_lenght(int)(vec) - 2; i++)
    {
        vector_push_back(int)(vec, 0);
    }

    vector_set(int)(vec, value, pos);
    int f_pos = vector_find(int)(vec, value);

    assert(pos == f_pos);
    return MUNIT_OK;
}

TEST_FUNC(test_find_cmp)
{
    vector(int) *vec = user_data;
    int value = munit_rand_uint32();
    int pos = munit_rand_int_range(0, (vector_lenght(int)(vec)) / 2);
    for (size_t i = 0; i < vector_lenght(int)(vec) - 2; i++)
    {
        vector_push_back(int)(vec, 0);
    }

    vector_set(int)(vec, value, pos);
    int f_pos = vector_find_cmp(int)(vec, value, int_cmp);

    assert(pos == f_pos);
    return MUNIT_OK;
}

TEST_FUNC(test_resize)
{
    vector(int) *vec = user_data;
    vector_resize(int)(vec, 15);
    vector_fill(int)(vec, 3);
    int arr[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    munit_assert_memory_equal(sizeof(int) * 15, vec->buffer, arr);
    munit_assert(vector_lenght(int)(vec) == 15);
    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    vector(int) *vec = user_data;

    size_t c = 0;
    int len = vector_lenght(int)(vec);
    for (size_t i = 0; i < len; i++)
    {
        c += i % 2;
        vector_push_back(int)(vec, i % 2);
    }
    munit_assert(c == vector_count(int)(vec, 1));
    munit_assert(0 == vector_count(int)(vec, -1));
    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    vector(int) *vec = user_data;

    size_t c = 0;
    int len = vector_lenght(int)(vec);
    for (size_t i = 0; i < len; i++)
    {
        c += i % 2;
        vector_push_back(int)(vec, i % 2);
    }
    munit_assert(c == vector_count_cmp(int)(vec, 1, int_cmp));
    munit_assert(0 == vector_count_cmp(int)(vec, -1, int_cmp));
    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    vector(int) *vec = user_data;
    int len = vector_lenght(int)(vec);

    for (size_t i = 0; i < len; i++)
    {
        vector_push_back(int)(vec, 1);
    }

    munit_assert(vector_all(int)(vec, 1));
    munit_assert(vector_all(int)(vec, 0) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    vector(int) *vec = user_data;
    int len = vector_lenght(int)(vec);

    for (size_t i = 0; i < len; i++)
    {
        vector_push_back(int)(vec, i % 2);
    }

    munit_assert(vector_all_cmp(int)(vec, 0, less_than_two));
    munit_assert(vector_all_cmp(int)(vec, 0, is_even) == false);
    munit_assert(vector_all_cmp(int)(vec, 2, int_cmp) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_any)
{
    vector(int) *vec = user_data;
    int len = vector_lenght(int)(vec);

    for (size_t i = 0; i < len; i++)
    {
        vector_push_back(int)(vec, i % 2);
    }

    munit_assert(vector_any(int)(vec, 0));
    munit_assert(vector_any(int)(vec, 1));
    munit_assert(vector_any(int)(vec, 2) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_any_cmp)
{
    vector(int) *vec = user_data;
    int len = vector_lenght(int)(vec);

    for (size_t i = 0; i < len; i++)
    {
        vector_push_back(int)(vec, i % 2);
    }

    munit_assert(vector_any_cmp(int)(vec, 0, less_than_two));
    munit_assert(vector_any_cmp(int)(vec, 1, is_even));
    munit_assert(vector_any_cmp(int)(vec, 2, int_cmp) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    vector(int) other;
    vector(int) *vec = user_data;

    int len = vector_lenght(int)(vec);
    vector_create(int)(&other, len);

    for (size_t i = 0; i < len; i++)
    {
        uint32_t v = munit_rand_uint32();
        vector_push_back(int)(vec, v);
        vector_push_back(int)(&other, v);
    }

    vector_join(int)(vec, &other);

    for (size_t i = 0; i < len; i++)
    {
        int a = vector_get(int)(vec, i);
        int b = vector_get(int)(vec, i + len);
        munit_assert(a == b);
    }

    vector_free(int)(&other);
    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    vector(int) *vec = user_data;
    int len = vector_lenght(int)(vec);
    for (size_t i = 0; i < len; i++)
    {
        vector_push_back(int)(vec, i);
    }

    vector_reverse(int)(vec);

    for (size_t i = 0, v = len - 1; i < len; i++, v--)
    {
        munit_assert(vector_get(int)(vec, i) == v);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_lenght)
{
    vector(int) *vec = user_data;
    int len = vector_lenght(int)(vec);
    munit_assert(len == 10);
    return MUNIT_OK;
}

TEST_FUNC(test_map)
{
    vector(int) *vec = user_data;
    int *out;

    int len = vector_lenght(int)(vec);

    for (size_t i = 0; i < len; i++)
    {
        vector_push_back(int)(vec, i);
    }

    vector_map(int)(vec, &out, mul_by_2);

    for (size_t i = 0; i < len; i++)
    {
        munit_assert(vector_get(int)(vec, i) * 2 == out[i]);
    }

    free(out);
    return MUNIT_OK;
}

TEST_FUNC(test_filter)
{
    vector(int) *vec = user_data;
    int *out;
    size_t vec_len;
    int len = vector_lenght(int)(vec);
    for (size_t i = 0; i < len; i++)
    {
        vector_push_back(int)(vec, i);
    }

    vector_filter(int)(vec, &out, filter_even, &vec_len);
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
    vector(int) *my_vec = (vector(int) *)malloc(sizeof(vector(int)));
    vector_create(int)(my_vec, 10);

    for (int i = 0; i < my_vec->lenght; i++)
        my_vec->buffer[i] = 0;
    return my_vec;
}

static void clear(void *data)
{
    vector(int) *arr = (vector(int) *)data;
    vector_free(int)(arr);
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
       TEST("/clear", test_clear),
       TEST("/map", test_map),
       TEST("/filter", test_filter),
       {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL} };

MunitSuite vector_suite = { "/vector", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

