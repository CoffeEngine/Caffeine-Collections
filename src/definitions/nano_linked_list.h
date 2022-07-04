#ifndef NANO_LINKED_LIST_H
#define NANO_LINKED_LIST_H

#include "../internal/nano_macros.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

#ifndef CNANO_USE_RAW
#define linked_list(type) __nano_t(type, linked_list)

#define linked_list_create(type) __nano_fn(type, linked_list, create)
#define linked_list_insert(type) __nano_fn(type, linked_list, insert)
#define linked_list_set(type) __nano_fn(type, linked_list, set)
#define linked_list_add(type) __nano_fn(type, linked_list, add)
#define linked_list_remove(type) __nano_fn(type, linked_list, remove)
#define linked_list_get(type) __nano_fn(type, linked_list, get)
#define linked_list_first(type) __nano_fn(type, linked_list, first)
#define linked_list_copy(type) __nano_fn(type, linked_list, copy)
#define linked_list_clone(type) __nano_fn(type, linked_list, clone)
#define linked_list_equal(type) __nano_fn(type, linked_list, equal)
#define linked_list_fill(type) __nano_fn(type, linked_list, fill)
#define linked_list_find(type) __nano_fn(type, linked_list, find)
#define linked_list_find_cmp(type) __nano_fn(type, linked_list, find_cmp)
#define linked_list_count(type) __nano_fn(type, linked_list, count)
#define linked_list_count_cmp(type) __nano_fn(type, linked_list, count_cmp)
#define linked_list_all(type) __nano_fn(type, linked_list, all)
#define linked_list_all_cmp(type) __nano_fn(type, linked_list, all_cmp)
#define linked_list_join(type) __nano_fn(type, linked_list, join)
#define linked_list_reverse(type) __nano_fn(type, linked_list, reverse)
#define linked_list_free(type) __nano_fn(type, linked_list, free)
#define linked_list_lenght(type) __nano_fn(type, linked_list, lenght)
#define linked_list_any(type) __nano_fn(type, linked_list, any)
#define linked_list_any_cmp(type) __nano_fn(type, linked_list, any_cmp)
#define linked_list_last(type) __nano_fn(type, linked_list, last)
#define linked_list_map(type) __nano_fn(type, linked_list, map)
#define linked_list_filter(type) __nano_fn(type, linked_list, filter)
#endif

#define nano_declare_linked_list_alias(type, alias) \
    typedef type alias;                             \
    nano_declare_linked_list(type);

#define nano_declare_linked_list_for(...) call_macro_x_for_each(nano_declare_linked_list, __VA_ARGS__)

#define nano_declare_linked_list(type)                                                                                                                                       \
    typedef struct __nano_t(type, linked_list_node)                                                                                                                          \
    {                                                                                                                                                                        \
        struct __nano_t(type, linked_list_node) * pnext;                                                                                                                     \
        type value;                                                                                                                                                          \
    }                                                                                                                                                                        \
    __nano_t(type, linked_list_node_t);                                                                                                                                      \
    typedef struct                                                                                                                                                           \
    {                                                                                                                                                                        \
        __nano_t(type, linked_list_node_t) * first;                                                                                                                          \
        __nano_t(type, linked_list_node_t) * last;                                                                                                                           \
        size_t count;                                                                                                                                                        \
    } __nano_t(type, linked_list);                                                                                                                                           \
                                                                                                                                                                             \
    void __nano_fn(type, linked_list, create)(__nano_t(type, linked_list) * arr);                                                                                            \
    void __nano_fn(type, linked_list, insert)(__nano_t(type, linked_list) * arr, type value, size_t index);                                                                  \
    void __nano_fn(type, linked_list, set)(__nano_t(type, linked_list) * arr, type value, size_t index);                                                                     \
    void __nano_fn(type, linked_list, add)(__nano_t(type, linked_list) * arr, type value);                                                                                   \
    type __nano_fn(type, linked_list, remove)(__nano_t(type, linked_list) * arr, size_t index);                                                                              \
    type __nano_fn(type, linked_list, get)(__nano_t(type, linked_list) * arr, size_t index);                                                                                 \
    type __nano_fn(type, linked_list, first)(__nano_t(type, linked_list) * arr);                                                                                             \
    void __nano_fn(type, linked_list, copy)(__nano_t(type, linked_list) * arr, __nano_t(type, linked_list) * *out, size_t start, size_t end);                                \
    void __nano_fn(type, linked_list, clone)(__nano_t(type, linked_list) * arr, __nano_t(type, linked_list) * *out);                                                         \
    bool __nano_fn(type, linked_list, equal)(__nano_t(type, linked_list) * a, __nano_t(type, linked_list) * b);                                                              \
    void __nano_fn(type, linked_list, fill)(__nano_t(type, linked_list) * arr, type value);                                                                                  \
    int __nano_fn(type, linked_list, find)(__nano_t(type, linked_list) * arr, type value);                                                                                   \
    int __nano_fn(type, linked_list, find_cmp)(__nano_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b));                                                  \
    size_t __nano_fn(type, linked_list, count)(__nano_t(type, linked_list) * arr, type value);                                                                               \
    size_t __nano_fn(type, linked_list, count_cmp)(__nano_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b));                                              \
    bool __nano_fn(type, linked_list, all)(__nano_t(type, linked_list) * arr, type value);                                                                                   \
    bool __nano_fn(type, linked_list, all_cmp)(__nano_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b));                                                  \
    void __nano_fn(type, linked_list, join)(__nano_t(type, linked_list) * a, __nano_t(type, linked_list) * b);                                                               \
    void __nano_fn(type, linked_list, reverse)(__nano_t(type, linked_list) * arr);                                                                                           \
    void __nano_fn(type, linked_list, free)(__nano_t(type, linked_list) * arr, void (*custom_free)(type a));                                                                 \
    size_t __nano_fn(type, linked_list, lenght)(__nano_t(type, linked_list) * arr);                                                                                          \
    bool __nano_fn(type, linked_list, any)(__nano_t(type, linked_list) * arr, type value);                                                                                   \
    bool __nano_fn(type, linked_list, any_cmp)(__nano_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b));                                                  \
    void __nano_fn(type, linked_list, map)(__nano_t(type, linked_list) * arr, __nano_t(type, linked_list) * *out, type(*map)(type value, size_t index));                     \
    void __nano_fn(type, linked_list, filter)(__nano_t(type, linked_list) * arr, __nano_t(type, linked_list) * *out, type(*filter)(type value, size_t index, int8_t * add)); \
    type __nano_fn(type, linked_list, last)(__nano_t(type, linked_list) * arr);

#define linked_list_foreach(type, p_list, code, ...) macro_override(dummy, ##__VA_ARGS__, _4, _3, ___i___linked_list_foreach_2, ___i___linked_list_foreach_1, ___i___linked_list_foreach_0)(type, p_list, code, ##__VA_ARGS__)

#define ___i___linked_list_foreach_0(type, p_list, code)                             \
    {                                                                                \
        __nano_t(type, linked_list_node_t) *___c_i_cnano_loop_pnext = p_list->first; \
        for (size_t cnano_index = 0; cnano_index < p_list->count; cnano_index++)     \
        {                                                                            \
            type cnano_value = ___c_i_cnano_loop_pnext->value;                       \
            code;                                                                    \
            ___c_i_cnano_loop_pnext = ___c_i_cnano_loop_pnext->pnext;                \
        }                                                                            \
    }

#define ___i___linked_list_foreach_1(type, p_list, code, i_name)                     \
    {                                                                                \
        __nano_t(type, linked_list_node_t) *___c_i_cnano_loop_pnext = p_list->first; \
        for (size_t i_name = 0; i_name < p_list->count; i_name++)                    \
        {                                                                            \
            type cnano_value = ___c_i_cnano_loop_pnext->value;                       \
            code;                                                                    \
            ___c_i_cnano_loop_pnext = ___c_i_cnano_loop_pnext->pnext;                \
        }                                                                            \
    }

#define ___i___linked_list_foreach_2(type, p_list, code, i_name, v_name)             \
    {                                                                                \
        __nano_t(type, linked_list_node_t) *___c_i_cnano_loop_pnext = p_list->first; \
        for (size_t i_name = 0; i_name < p_list->count; i_name++)                    \
        {                                                                            \
            type v_name = ___c_i_cnano_loop_pnext->value;                            \
            code;                                                                    \
            ___c_i_cnano_loop_pnext = ___c_i_cnano_loop_pnext->pnext;                \
        }                                                                            \
    }
#endif