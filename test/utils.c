#include "utils.h"

nano_core_implement(int);
nano_implement_vector(int);
nano_implement_array(int);
nano_implement_queue(int);
nano_implement_stack(int);
nano_implement_linked_list(int);
nano_implement_hash_table(string, string);

bool int_cmp(int a, int b)
{
    return a == b;
}

bool is_even(int a, int b)
{
    return a % 2 == 1;
}

bool less_than_two(int a, int b)
{
    return a < 2;
}

int mul_by_2(int value, size_t index)
{
    return value * 2;
}

bool filter_even(int value, size_t index, int* filtered)
{
    if (value % 2 == 1)
    {
        *filtered = value;
        return true;
    }
    return false;
}