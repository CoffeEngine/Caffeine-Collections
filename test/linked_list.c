#include "utils.h"

TEST_FUNC(test_insert)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_insert(int)(my_list, 5, 0);
    linked_list_insert(int)(my_list, 6, 0);

    int v = linked_list_get(int)(my_list, 1);

    assert(v == 5);
    return MUNIT_OK;
}

TEST_FUNC(test_set)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_insert(int)(my_list, 5, 0);
    linked_list_insert(int)(my_list, 6, 0);

    linked_list_set(int)(my_list, 0, 1);

    int v = linked_list_get(int)(my_list, 1);

    assert(v == 0);
    return MUNIT_OK;
}

TEST_FUNC(test_add)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 5);
    linked_list_add(int)(my_list, 7);

    int v = linked_list_get(int)(my_list, 1);

    assert(v == 7);
    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 5);
    linked_list_add(int)(my_list, 7);

    linked_list_remove(int)(my_list, 0);

    int v = linked_list_get(int)(my_list, 0);

    assert(v == 7);
    return MUNIT_OK;
}

TEST_FUNC(test_get)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 5);
    linked_list_add(int)(my_list, 7);

    int v = linked_list_get(int)(my_list, 1);

    assert(v == 7);
    return MUNIT_OK;
}

TEST_FUNC(test_first)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 5);
    linked_list_add(int)(my_list, 7);

    int v = linked_list_first(int)(my_list);

    assert(v == 5);
    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list(int) out;
    linked_list(int) *pout = &out;

    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 3);
    linked_list_add(int)(my_list, 4);

    linked_list_clone(int)(my_list, &pout);

    munit_assert(my_list->count == out.count);

    bool eq = linked_list_equal(int)(my_list, pout);
    munit_assert(eq);

    linked_list_free(int)(pout, 0);
    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list(int) out;
    linked_list(int) *pout = &out;

    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 3);
    linked_list_add(int)(my_list, 4);

    linked_list_clone(int)(my_list, &pout);

    munit_assert(my_list->count == out.count);

    bool eq = linked_list_equal(int)(my_list, pout);
    munit_assert(eq);

    linked_list_free(int)(pout, 0);
    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list(int) out;
    linked_list(int) *pout = &out;

    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 3);
    linked_list_add(int)(my_list, 4);
    linked_list_add(int)(my_list, 5);
    linked_list_add(int)(my_list, 6);

    linked_list_copy(int)(my_list, &pout, 1, 5);

    for (size_t i = 1; i < my_list->count - 1; i++)
    {
        int a = linked_list_get(int)(my_list, i);
        int b = linked_list_get(int)(&out, i - 1);
        assert(a == b);
    }

    linked_list_free(int)(pout, 0);
    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 4);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 6);

    int cc = linked_list_count(int)(my_list, 1);

    assert(cc == 3);
    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 4);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 6);

    int cc = linked_list_count_cmp(int)(my_list, 1, int_cmp);

    assert(cc == 3);
    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    linked_list(int) a, b, ab;
    linked_list_create(int)(&a);
    linked_list_create(int)(&b);
    linked_list_create(int)(&ab);

    linked_list_add(int)(&a, 1);
    linked_list_add(int)(&a, 2);
    linked_list_add(int)(&a, 3);

    linked_list_add(int)(&b, 4);
    linked_list_add(int)(&b, 5);
    linked_list_add(int)(&b, 6);

    linked_list_add(int)(&ab, 1);
    linked_list_add(int)(&ab, 2);
    linked_list_add(int)(&ab, 3);
    linked_list_add(int)(&ab, 4);
    linked_list_add(int)(&ab, 5);
    linked_list_add(int)(&ab, 6);

    linked_list_join(int)(&a, &b);
    bool eq = linked_list_equal(int)(&a, &ab);

    linked_list_free(int)(&a, 0);
    linked_list_free(int)(&b, 0);
    linked_list_free(int)(&ab, 0);

    munit_assert(eq);
    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    linked_list(int) a, b;
    linked_list_create(int)(&a);
    linked_list_create(int)(&b);

    linked_list_add(int)(&a, 1);
    linked_list_add(int)(&a, 2);
    linked_list_add(int)(&a, 3);

    linked_list_add(int)(&b, 3);
    linked_list_add(int)(&b, 2);
    linked_list_add(int)(&b, 1);

    linked_list_reverse(int)(&a);
    bool eq = linked_list_equal(int)(&a, &b);

    linked_list_free(int)(&a, 0);
    linked_list_free(int)(&b, 0);

    munit_assert(eq);

    return MUNIT_OK;
}

TEST_FUNC(test_fill)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);

    linked_list_fill(int)(my_list, 2);

    bool eq1 = linked_list_all(int)(my_list, 1);
    bool eq2 = linked_list_all(int)(my_list, 2);

    munit_assert(!eq1);
    munit_assert(eq2);

    return MUNIT_OK;
}

TEST_FUNC(test_lenght)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);

    size_t len = linked_list_lenght(int)(my_list);

    munit_assert(len == 4);

    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);

    bool eq1 = linked_list_all(int)(my_list, 1);
    bool eq2 = linked_list_all(int)(my_list, 2);

    munit_assert(eq1);
    munit_assert(!eq2);

    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);

    bool eq1 = linked_list_all_cmp(int)(my_list, 1, int_cmp);
    bool eq2 = linked_list_all_cmp(int)(my_list, 2, int_cmp);

    munit_assert(eq1);
    munit_assert(!eq2);

    return MUNIT_OK;
}

TEST_FUNC(test_any)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);

    bool eq1 = linked_list_any(int)(my_list, 2);
    bool eq2 = linked_list_any(int)(my_list, 3);

    munit_assert(eq1);
    munit_assert(!eq2);

    return MUNIT_OK;
}

TEST_FUNC(test_any_cmp)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);

    bool eq1 = linked_list_any_cmp(int)(my_list, 2, int_cmp);
    bool eq2 = linked_list_any_cmp(int)(my_list, 3, int_cmp);

    munit_assert(eq1);
    munit_assert(!eq2);

    return MUNIT_OK;
}

TEST_FUNC(test_map)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list(int) out, *out_pointer = &out;
    linked_list_create(int)(out_pointer);

    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 1);

    linked_list_map(int)(my_list, &out_pointer, mul_by_2);

    bool eq1 = linked_list_all_cmp(int)(out_pointer, 2, int_cmp);
    bool eq2 = linked_list_any_cmp(int)(out_pointer, 1, int_cmp);

    linked_list_free(int)(out_pointer, 0);

    munit_assert(eq1);
    munit_assert(!eq2);

    return MUNIT_OK;
}

TEST_FUNC(test_filter)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list(int) out, *out_pointer = &out;
    linked_list_create(int)(out_pointer);

    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 3);
    linked_list_add(int)(my_list, 4);

    linked_list_filter(int)(my_list, &out_pointer, filter_even);

    bool eq1 = linked_list_all_cmp(int)(out_pointer, 2, is_even);

    linked_list_free(int)(out_pointer, 0);
    munit_assert(eq1);

    return MUNIT_OK;
}

TEST_FUNC(test_find)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 3);
    linked_list_add(int)(my_list, 4);

    int pos = linked_list_find(int)(my_list, 4);

    assert(pos == 3);
    return MUNIT_OK;
}
TEST_FUNC(test_find_cmp)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 3);
    linked_list_add(int)(my_list, 4);

    int pos = linked_list_find_cmp(int)(my_list, 4, int_cmp);

    assert(pos == 3);
    return MUNIT_OK;
}

TEST_FUNC(test_last)
{
    linked_list(int) *my_list = (linked_list(int) *)user_data;
    linked_list_add(int)(my_list, 1);
    linked_list_add(int)(my_list, 2);
    linked_list_add(int)(my_list, 3);
    linked_list_add(int)(my_list, 4);

    int v = linked_list_last(int)(my_list);

    assert(v == 4);
    return MUNIT_OK;
}

static void *setup(const MunitParameter params[], void *user_data)
{
    linked_list(int) *my_list = (linked_list(int) *)malloc(sizeof(linked_list(int)));
    linked_list_create(int)(my_list);

    return my_list;
}

static void clear(void *data)
{
    linked_list(int) *arr = (linked_list(int) *)data;
    //linked_list_free(int)(arr, NULL);
}

static MunitTest tests[] = {
       TEST("/insert", test_insert),
       TEST("/set", test_set),
       TEST("/add", test_add),
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

MunitSuite linked_list_suite = { "/linked_list", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };