#include "utils.h"

static bool cmp_string(string a, string b)
{
    return strncmp(a, b, 8) == 0;
}

TEST_FUNC(test_add)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");
    bool er = hash_map_exist(string, string)(myhash, "Ruan");
    bool ev = hash_map_exist(string, string)(myhash, "Vic");

    munit_assert(er);
    munit_assert(ev);

    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    hash_map_remove(string, string)(myhash, "Ruan");

    bool er = hash_map_exist(string, string)(myhash, "Ruan");
    bool ev = hash_map_exist(string, string)(myhash, "Vic");

    munit_assert((!er));
    munit_assert(ev);

    return MUNIT_OK;
}

TEST_FUNC(test_get)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");

    string out = NULL;
    hash_map_get(string, string)(myhash, "Ruan", &out);

    int cmp = strncmp(out, "Azevedo", sizeof("Azevedo"));

    munit_assert(cmp == 0);
    return MUNIT_OK;
}

TEST_FUNC(test_clear)
{
    hash_map(string, string) *myhash = user_data;

    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    hash_map_clear(string, string)(myhash);

    bool er = hash_map_exist(string, string)(myhash, "Ruan");
    bool ev = hash_map_exist(string, string)(myhash, "Vic");

    munit_assert((!er));
    munit_assert((!ev));

    return MUNIT_OK;
}

TEST_FUNC(test_exist)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    hash_map_remove(string, string)(myhash, "Ruan");

    bool er = hash_map_exist(string, string)(myhash, "Ruan");
    bool ev = hash_map_exist(string, string)(myhash, "Vic");

    munit_assert((!er));
    munit_assert(ev);

    return MUNIT_OK;
}

TEST_FUNC(test_lenght)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    size_t len1 = hash_map_lenght(string, string)(myhash);

    hash_map_remove(string, string)(myhash, "Ruan");

    size_t len2 = hash_map_lenght(string, string)(myhash);

    munit_assert(len1 == 2);
    munit_assert(len2 == 1);

    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    hash_map(string, string) clonesrc;

    hash_map(string, string) *clonehash = &clonesrc;

    hash_map_clone(string, string)(myhash, &clonehash);

    bool er = hash_map_exist(string, string)(clonehash, "Ruan");
    bool ev = hash_map_exist(string, string)(clonehash, "Vic");

    munit_assert(er);
    munit_assert(ev);

    size_t len1 = hash_map_lenght(string, string)(myhash);
    size_t len2 = hash_map_lenght(string, string)(clonehash);

    hash_map_free(string, string)(clonehash);

    munit_assert(len1 == len2);

    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    hash_map(string, string) clonesrc;

    hash_map(string, string) *clonehash = &clonesrc;

    hash_map_clone(string, string)(myhash, &clonehash);

    bool equals = hash_map_equal(string, string)(myhash, clonehash);

    hash_map_free(string, string)(clonehash);

    munit_assert(equals);

    return MUNIT_OK;
}

TEST_FUNC(test_count_values)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Nilton", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    size_t count = hash_map_count_values(string, string)(myhash, "Azevedo");

    assert(count == 2);

    return MUNIT_OK;
}

TEST_FUNC(test_count_values_cmp)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Nilton", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    size_t count = hash_map_count_values_cmp(string, string)(myhash, "Azevedo", cmp_string);

    assert(count == 2);

    return MUNIT_OK;
}

TEST_FUNC(test_all_values)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Nilton", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    bool all = hash_map_all_values(string, string)(myhash, "Azevedo");

    assert(all == false);

    hash_map_remove(string, string)(myhash, "Vic");

    all = hash_map_all_values(string, string)(myhash, "Azevedo");
    assert(all == true);

    return MUNIT_OK;
}

TEST_FUNC(test_all_values_cmp)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Nilton", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    bool all = hash_map_all_values_cmp(string, string)(myhash, "Azevedo", cmp_string);

    assert(all == false);

    hash_map_remove(string, string)(myhash, "Vic");

    all = hash_map_all_values_cmp(string, string)(myhash, "Azevedo", cmp_string);
    assert(all == true);

    return MUNIT_OK;
}

TEST_FUNC(test_any_values)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Nilton", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    bool all = hash_map_any_values(string, string)(myhash, "França");

    assert(all == true);

    hash_map_remove(string, string)(myhash, "Vic");

    all = hash_map_any_values(string, string)(myhash, "França");
    assert(all == false);

    return MUNIT_OK;
}

TEST_FUNC(test_any_values_cmp)
{
    hash_map(string, string) *myhash = user_data;
    hash_map_add(string, string)(myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(myhash, "Nilton", "Azevedo");
    hash_map_add(string, string)(myhash, "Vic", "França");

    bool all = hash_map_any_values_cmp(string, string)(myhash, "França", cmp_string);

    assert(all == true);

    hash_map_remove(string, string)(myhash, "Vic");

    all = hash_map_any_values_cmp(string, string)(myhash, "França", cmp_string);
    assert(all == false);

    return MUNIT_OK;
}

static uintmax_t hashfn(char *key)
{
    uintmax_t k = 0;
    char *c = key;
    size_t len = strlen(key);
    for (size_t i = 0; i < len; i++)
    {
        k += (int)(c[i]);
    }
    return k;
}
static bool hashcmp(char *a, char *b)
{
    return strcmp(a, b) == 0;
}

static void *setup(const MunitParameter params[], void *user_data)
{
    hash_map(string, string) *my_hash = (hash_map(string, string) *)malloc(sizeof(hash_map(string, string)));
    hash_map_create(string, string)(my_hash, 16, hashfn, hashcmp);
    return my_hash;
}

static void clear(void *data)
{
    hash_map(string, string) *myhash = (hash_map(string, string) *)data;
    hash_map_free(string, string)(myhash);
}

static MunitTest tests[] = {
    TEST("/test_add", test_add),
    TEST("/test_remove", test_remove),
    TEST("/test_get", test_get),
    TEST("/test_clear", test_clear),
    TEST("/test_exist", test_exist),
    TEST("/test_lenght", test_lenght),
    TEST("/test_clone", test_clone),
    TEST("/test_equal", test_equal),
    TEST("/test_count_values", test_count_values),
    TEST("/test_count_values_cmp", test_count_values_cmp),
    TEST("/test_all_values", test_all_values),
    TEST("/test_all_values_cmp", test_all_values_cmp),
    TEST("/test_any_values", test_any_values),
    TEST("/test_any_values_cmp", test_any_values_cmp),
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL} };

MunitSuite hash_map_suite = { "/hash", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };