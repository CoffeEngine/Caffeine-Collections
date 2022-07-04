#ifndef NANO_ARRAY_H
#define NANO_ARRAY_H

#include "../internal/nano_macros.h"
#include "../internal/nano_foreach_macro.h"

#ifndef CNANO_USE_RAW
#define array(type) __nano_t(type, array)

#define array_create(type) __nano_fn(type, array, create)
#define array_desloc(type) __nano_fn(type, array, desloc)
#define array_insert(type) __nano_fn(type, array, insert)
#define array_set(type) __nano_fn(type, array, set)
#define array_remove(type) __nano_fn(type, array, remove)
#define array_get(type) __nano_fn(type, array, get)
#define array_first(type) __nano_fn(type, array, first)
#define array_last(type) __nano_fn(type, array, last)
#define array_copy(type) __nano_fn(type, array, copy)
#define array_clone(type) __nano_fn(type, array, clone)
#define array_equal(type) __nano_fn(type, array, equal)
#define array_fill(type) __nano_fn(type, array, fill)
#define array_find(type) __nano_fn(type, array, find)
#define array_find_cmp(type) __nano_fn(type, array, find_cmp)
#define array_resize(type) __nano_fn(type, array, resize)
#define array_count(type) __nano_fn(type, array, count)
#define array_count_cmp(type) __nano_fn(type, array, count_cmp)
#define array_all(type) __nano_fn(type, array, all)
#define array_all_cmp(type) __nano_fn(type, array, all_cmp)
#define array_any(type) __nano_fn(type, array, any)
#define array_any_cmp(type) __nano_fn(type, array, any_cmp)
#define array_join(type) __nano_fn(type, array, join)
#define array_reverse(type) __nano_fn(type, array, reverse)
#define array_free(type) __nano_fn(type, array, free)
#define array_lenght(type) __nano_fn(type, array, lenght)
#define array_map(type) __nano_fn(type, array, map)
#define array_filter(type) __nano_fn(type, array, filter)
#endif

#define nano_declare_array_alias(type, alias) \
    typedef type alias;                       \
    nano_declare_array(alias)

#define nano_declare_array_for(...) call_macro_x_for_each(nano_declare_array, __VA_ARGS__)
#define nano_declare_array(type)                                                                                         \
    typedef struct                                                                                                       \
    {                                                                                                                    \
        type *buffer;                                                                                                    \
        size_t lenght;                                                                                                   \
    } array(type);                                                                                                       \
                                                                                                                         \
    void __nano_fn(type, array, create)(__nano_t(type, array) * arr, size_t lenght);                                     \
    void __nano_fn(type, array, desloc)(__nano_t(type, array) * arr, size_t from, int steps);                            \
    void __nano_fn(type, array, insert)(__nano_t(type, array) * arr, type value, size_t index);                          \
    void __nano_fn(type, array, set)(__nano_t(type, array) * arr, type value, size_t index);                             \
    void __nano_fn(type, array, remove)(__nano_t(type, array) * arr, size_t index);                                      \
    type __nano_fn(type, array, get)(__nano_t(type, array) * arr, size_t index);                                         \
    type __nano_fn(type, array, first)(__nano_t(type, array) * arr);                                                     \
    type __nano_fn(type, array, last)(__nano_t(type, array) * arr);                                                      \
    void __nano_fn(type, array, copy)(__nano_t(type, array) * arr, type * *out, size_t start, size_t end);               \
    void __nano_fn(type, array, clone)(__nano_t(type, array) * arr, type * *out);                                        \
    bool __nano_fn(type, array, equal)(__nano_t(type, array) * a, __nano_t(type, array) * b);                            \
    void __nano_fn(type, array, fill)(__nano_t(type, array) * arr, type value);                                          \
    int __nano_fn(type, array, find)(__nano_t(type, array) * arr, type value);                                           \
    int __nano_fn(type, array, find_cmp)(__nano_t(type, array) * arr, type value, bool (*cmp)(type a, type b));          \
    void __nano_fn(type, array, resize)(__nano_t(type, array) * arr, size_t lenght);                                     \
    size_t __nano_fn(type, array, count)(__nano_t(type, array) * arr, type value);                                       \
    size_t __nano_fn(type, array, count_cmp)(__nano_t(type, array) * arr, type value, bool (*cmp)(type a, type b));      \
    bool __nano_fn(type, array, all)(__nano_t(type, array) * arr, type value);                                           \
    bool __nano_fn(type, array, all_cmp)(__nano_t(type, array) * arr, type value, bool (*cmp)(type a, type b));          \
    bool __nano_fn(type, array, any)(__nano_t(type, array) * arr, type value);                                           \
    bool __nano_fn(type, array, any_cmp)(__nano_t(type, array) * arr, type value, bool (*cmp)(type a, type b));          \
    void __nano_fn(type, array, join)(__nano_t(type, array) * a, __nano_t(type, array) * b);                             \
    void __nano_fn(type, array, reverse)(__nano_t(type, array) * arr);                                                   \
    void __nano_fn(type, array, free)(__nano_t(type, array) * arr);                                                      \
    size_t __nano_fn(type, array, lenght)(__nano_t(type, array) * arr);                                                  \
    void __nano_fn(type, array, map)(__nano_t(type, array) * arr, type * *out, type(*map_fn)(type value, size_t index)); \
    void __nano_fn(type, array, filter)(__nano_t(type, array) * arr, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);

#define array_foreach(type, p_arr, code, ...) macro_override(dummy, ##__VA_ARGS__, _4, _3, ___i___array_foreach_2, ___i___array_foreach_1, ___i___array_foreach_0)(type, p_arr, code, ##__VA_ARGS__)

#define ___i___array_foreach_0(type, p_arr, code)                                \
    {                                                                            \
        for (size_t cnano_index = 0; cnano_index < arr->lenght; cnano_index++)   \
        {                                                                        \
            type canano_value = __nano_fn(type, array, get)(p_arr, cnano_index); \
            code                                                                 \
        }                                                                        \
    }

#define ___i___array_foreach_1(type, p_arr, code, i_name)                   \
    {                                                                       \
        for (size_t i_name = 0; i_name < arr->lenght; i_name++)             \
        {                                                                   \
            type canano_value = __nano_fn(type, array, get)(p_arr, i_name); \
            code                                                            \
        }                                                                   \
    }

#define ___i___array_foreach_2(type, p_arr, code, i_name, v_name)     \
    {                                                                 \
        for (size_t i_name = 0; i_name < arr->lenght; i_name++)       \
        {                                                             \
            type v_name = __nano_fn(type, array, get)(p_arr, i_name); \
            code                                                      \
        }                                                             \
    }
#endif