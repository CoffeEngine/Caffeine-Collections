#ifndef NANO_VECTOR_H
#define NANO_VECTOR_H

#include "../internal/nano_macros.h"

#ifndef CNANO_USE_RAW
#define vector(type) __nano_t(type, vector)

#define vector_create(type) __nano_fn(type, vector, create)
#define vector_desloc(type) __nano_fn(type, vector, desloc)
#define vector_insert(type) __nano_fn(type, vector, insert)
#define vector_set(type) __nano_fn(type, vector, set)
#define vector_remove(type) __nano_fn(type, vector, remove)
#define vector_get(type) __nano_fn(type, vector, get)
#define vector_first(type) __nano_fn(type, vector, first)
#define vector_last(type) __nano_fn(type, vector, last)
#define vector_push_front(type) __nano_fn(type, vector, push_front)
#define vector_push_back(type) __nano_fn(type, vector, push_back)
#define vector_pop_front(type) __nano_fn(type, vector, pop_front)
#define vector_pop_back(type) __nano_fn(type, vector, pop_back)
#define vector_copy(type) __nano_fn(type, vector, copy)
#define vector_clone(type) __nano_fn(type, vector, clone)
#define vector_equal(type) __nano_fn(type, vector, equal)
#define vector_fill(type) __nano_fn(type, vector, fill)
#define vector_find(type) __nano_fn(type, vector, find)
#define vector_find_cmp(type) __nano_fn(type, vector, find_cmp)
#define vector_resize(type) __nano_fn(type, vector, resize)
#define vector_count(type) __nano_fn(type, vector, count)
#define vector_count_cmp(type) __nano_fn(type, vector, count_cmp)
#define vector_all(type) __nano_fn(type, vector, all)
#define vector_all_cmp(type) __nano_fn(type, vector, all_cmp)
#define vector_any(type) __nano_fn(type, vector, any)
#define vector_any_cmp(type) __nano_fn(type, vector, any_cmp)
#define vector_join(type) __nano_fn(type, vector, join)
#define vector_reverse(type) __nano_fn(type, vector, reverse)
#define vector_free(type) __nano_fn(type, vector, free)
#define vector_clear(type) __nano_fn(type, vector, clear)
#define vector_lenght(type) __nano_fn(type, vector, lenght)
#define vector_map(type) __nano_fn(type, vector, map)
#define vector_filter(type) __nano_fn(type, vector, filter)
#endif

#define nano_declare_vector_alias(type) \
    typedef type alias;                 \
    nano_declare_vector(type);

#define nano_declare_vector_for(...) call_macro_x_for_each(dummy,nano_declare_vector,__VA_ARGS__)

#define nano_declare_vector(type)                                                                                             \
    typedef struct                                                                                                            \
    {                                                                                                                         \
        type *buffer;                                                                                                         \
        size_t lenght;                                                                                                        \
        size_t count;                                                                                                         \
    } __nano_t(type, vector);                                                                                                 \
                                                                                                                              \
    void __nano_fn(type, vector, create)(__nano_t(type, vector) * arr, size_t lenght);                                        \
    void __nano_fn(type, vector, desloc)(__nano_t(type, vector) * arr, size_t from, int steps);                               \
    void __nano_fn(type, vector, insert)(__nano_t(type, vector) * arr, type value, size_t index);                             \
    void __nano_fn(type, vector, set)(__nano_t(type, vector) * arr, type value, size_t index);                                \
    void __nano_fn(type, vector, remove)(__nano_t(type, vector) * arr, size_t index);                                         \
    type __nano_fn(type, vector, get)(__nano_t(type, vector) * arr, size_t index);                                            \
    type __nano_fn(type, vector, first)(__nano_t(type, vector) * arr);                                                        \
    type __nano_fn(type, vector, last)(__nano_t(type, vector) * arr);                                                         \
    void __nano_fn(type, vector, push_front)(__nano_t(type, vector) * arr, type value);                                       \
    void __nano_fn(type, vector, push_back)(__nano_t(type, vector) * arr, type value);                                        \
    void __nano_fn(type, vector, pop_front)(__nano_t(type, vector) * arr);                                                    \
    void __nano_fn(type, vector, pop_back)(__nano_t(type, vector) * arr);                                                     \
    void __nano_fn(type, vector, copy)(__nano_t(type, vector) * arr, __nano_t(type, vector) * out, size_t start, size_t end); \
    void __nano_fn(type, vector, clone)(__nano_t(type, vector) * arr, __nano_t(type, vector) * out);                          \
    bool __nano_fn(type, vector, equal)(__nano_t(type, vector) * a, __nano_t(type, vector) * b);                              \
    void __nano_fn(type, vector, fill)(__nano_t(type, vector) * arr, type value);                                             \
    int __nano_fn(type, vector, find)(__nano_t(type, vector) * arr, type value);                                              \
    int __nano_fn(type, vector, find_cmp)(__nano_t(type, vector) * arr, type value, bool (*cmp)(type a, type b));             \
    void __nano_fn(type, vector, resize)(__nano_t(type, vector) * arr, size_t lenght);                                        \
    size_t __nano_fn(type, vector, count)(__nano_t(type, vector) * arr, type value);                                          \
    size_t __nano_fn(type, vector, count_cmp)(__nano_t(type, vector) * arr, type value, bool (*cmp)(type a, type b));         \
    bool __nano_fn(type, vector, all)(__nano_t(type, vector) * arr, type value);                                              \
    bool __nano_fn(type, vector, all_cmp)(__nano_t(type, vector) * arr, type value, bool (*cmp)(type a, type b));             \
    bool __nano_fn(type, vector, any)(__nano_t(type, vector) * arr, type value);                                              \
    bool __nano_fn(type, vector, any_cmp)(__nano_t(type, vector) * arr, type value, bool (*cmp)(type a, type b));             \
    void __nano_fn(type, vector, join)(__nano_t(type, vector) * a, __nano_t(type, vector) * b);                               \
    void __nano_fn(type, vector, reverse)(__nano_t(type, vector) * arr);                                                      \
    void __nano_fn(type, vector, free)(__nano_t(type, vector) * arr);                                                         \
    void __nano_fn(type, vector, clear)(__nano_t(type, vector) * arr);                                                        \
    size_t __nano_fn(type, vector, lenght)(__nano_t(type, vector) * arr);                                                     \
    void __nano_fn(type, vector, map)(__nano_t(type, vector) * vec, type * *out, type(*map_fn)(type value, size_t index));    \
    void __nano_fn(type, vector, filter)(__nano_t(type, vector) * vec, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);

#ifdef _MSC_VER
#define vector_foreach(type, p_vec, code, ...) macro_override(##__VA_ARGS__, _4, _3, ___i___vector_foreach_2, ___i___vector_foreach_1, ___i___vector_foreach_0)(type, p_vec, code, ##__VA_ARGS__)
#else
vector_foreach(type, p_vec, code, ...) macro_override(dummy,##__VA_ARGS__, _4, _3, ___i___vector_foreach_2, ___i___vector_foreach_1, ___i___vector_foreach_0)(type, p_vec, code, ##__VA_ARGS__)
#endif

#define ___i___vector_foreach_0(type, p_vec, code)                               \
    {                                                                            \
        for (size_t cnano_index = 0; cnano_index < p_vec->count; cnano_index++)  \
        {                                                                        \
            type cnano_value = __nano_fn(type, vector, get)(p_vec, cnano_index); \
            code                                                                 \
        }                                                                        \
    }

#define ___i___vector_foreach_1(type, p_vec, code, i_name)                  \
    {                                                                       \
        for (size_t i_name = 0; i_name < p_vec->count; i_name++)            \
        {                                                                   \
            type cnano_value = __nano_fn(type, vector, get)(p_vec, i_name); \
            code                                                            \
        }                                                                   \
    }

#define ___i___vector_foreach_2(type, p_vec, code, i_name, v_name)     \
    {                                                                  \
        for (size_t i_name = 0; i_name < p_vec->count; i_name++)       \
        {                                                              \
            type v_name = __nano_fn(type, vector, get)(p_vec, i_name); \
            code                                                       \
        }                                                              \
    }

#endif