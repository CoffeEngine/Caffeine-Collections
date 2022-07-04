#ifndef _TEST_UTILS
#define _TEST_UTILS

#include "munit.h"
#include <stdlib.h>
#include <stdio.h>
#include "cnano.h"

#define TEST(name, function)                                       \
    {                                                              \
        name, function, setup, clear, MUNIT_TEST_OPTION_NONE, NULL \
    }

#define TEST_FUNC(name) static MunitResult name(const MunitParameter params[], void *user_data)



typedef char* string;
nano_declare_vector(int);
nano_declare_array(int);
nano_declare_queue(int);
nano_declare_stack(int);
nano_declare_linked_list(int);
nano_declare_hash_table(string, string);

bool int_cmp(int a, int b);
bool is_even(int a, int b);
bool less_than_two(int a, int b);
int mul_by_2(int value, size_t index);
bool filter_even(int value, size_t index, int* filtered);

#endif