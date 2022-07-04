#ifndef NANO_STACK_H
#define NANO_STACK_H

#include "../internal/nano_macros.h"
#include "../internal/nano_foreach_macro.h"

#ifndef CNANO_USE_RAW
#define stack(type) __nano_t(type, stack)
#define stack_create(type) __nano_fn(type, stack, create)
#define stack_free(type) __nano_fn(type, stack, free)
#define stack_clear(type) __nano_fn(type, stack, clear)
#define stack_push(type) __nano_fn(type, stack, push)
#define stack_pop(type) __nano_fn(type, stack, pop)
#define stack_top(type) __nano_fn(type, stack, top)
#define stack_clone(type) __nano_fn(type, stack, clone)
#define stack_equal(type) __nano_fn(type, stack, equal)
#define stack_copy(type) __nano_fn(type, stack, copy)
#define stack_find(type) __nano_fn(type, stack, find)
#define stack_find_cmp(type) __nano_fn(type, stack, find_cmp)
#define stack_fill(type) __nano_fn(type, stack, fill)
#define stack_count(type) __nano_fn(type, stack, count)
#define stack_count_cmp(type) __nano_fn(type, stack, count_cmp)
#define stack_all(type) __nano_fn(type, stack, all)
#define stack_all_cmp(type) __nano_fn(type, stack, all_cmp)
#define stack_any(type) __nano_fn(type, stack, any)
#define stack_any_cmp(type) __nano_fn(type, stack, any_cmp)
#define stack_join(type) __nano_fn(type, stack, join)
#define stack_reverse(type) __nano_fn(type, stack, reverse)
#define stack_resize(type) __nano_fn(type, stack, resize)
#define stack_lenght(type) __nano_fn(type, stack, lenght)
#define stack_map(type) __nano_fn(type, stack, map)
#define stack_filter(type) __nano_fn(type, stack, filter)

#endif

#define nano_declare_stack_alias(type, alias) \
    typedef type alias;                       \
    nano_declare_stack(alias)

#define nano_declare_stack_for(...) call_macro_x_for_each(nano_declare_stack, __VA_ARGS__)
#define nano_declare_stack(type)                                                                                            \
    typedef struct                                                                                                          \
    {                                                                                                                       \
        type *buffer;                                                                                                       \
        size_t lenght;                                                                                                      \
        size_t count;                                                                                                       \
    } stack(type);                                                                                                          \
    void __nano_fn(type, stack, create)(__nano_t(type, stack) * arr, size_t lenght);                                        \
    void __nano_fn(type, stack, free)(__nano_t(type, stack) * arr);                                                         \
    void __nano_fn(type, stack, clear)(__nano_t(type, stack) * arr);                                                        \
    void __nano_fn(type, stack, push)(__nano_t(type, stack) * arr, type value);                                             \
    type __nano_fn(type, stack, pop)(__nano_t(type, stack) * arr);                                                          \
    type __nano_fn(type, stack, top)(__nano_t(type, stack) * arr);                                                          \
    void __nano_fn(type, stack, copy)(__nano_t(type, stack) * arr, __nano_t(type, stack) * *out, size_t start, size_t end); \
    void __nano_fn(type, stack, clone)(__nano_t(type, stack) * arr, __nano_t(type, stack) * *out);                          \
    bool __nano_fn(type, stack, equal)(__nano_t(type, stack) * a, __nano_t(type, stack) * b);                               \
    void __nano_fn(type, stack, fill)(__nano_t(type, stack) * arr, type value);                                             \
    int __nano_fn(type, stack, find)(__nano_t(type, stack) * arr, type value);                                              \
    int __nano_fn(type, stack, find_cmp)(__nano_t(type, stack) * arr, type value, bool (*cmp)(type a, type b));             \
    void __nano_fn(type, stack, resize)(__nano_t(type, stack) * arr, size_t lenght);                                        \
    size_t __nano_fn(type, stack, count)(__nano_t(type, stack) * arr, type value);                                          \
    size_t __nano_fn(type, stack, count_cmp)(__nano_t(type, stack) * arr, type value, bool (*cmp)(type a, type b));         \
    bool __nano_fn(type, stack, all)(__nano_t(type, stack) * arr, type value);                                              \
    bool __nano_fn(type, stack, all_cmp)(__nano_t(type, stack) * arr, type value, bool (*cmp)(type a, type b));             \
    bool __nano_fn(type, stack, any)(__nano_t(type, stack) * arr, type value);                                              \
    bool __nano_fn(type, stack, any_cmp)(__nano_t(type, stack) * arr, type value, bool (*cmp)(type a, type b));             \
    void __nano_fn(type, stack, join)(__nano_t(type, stack) * a, __nano_t(type, stack) * b);                                \
    void __nano_fn(type, stack, reverse)(__nano_t(type, stack) * arr);                                                      \
    size_t __nano_fn(type, stack, lenght)(__nano_t(type, stack) * arr);                                                     \
    void __nano_fn(type, stack, map)(__nano_t(type, stack) * vec, type * *out, type(*map_fn)(type value, size_t index));    \
    void __nano_fn(type, stack, filter)(__nano_t(type, stack) * vec, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);
#endif