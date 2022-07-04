#ifndef NANO_QUEUE_H
#define NANO_QUEUE_H

#include "../internal/nano_macros.h"
#include "../internal/nano_foreach_macro.h"

#ifndef CNANO_USE_RAW
#define queue(type) __nano_t(type, queue)

#define queue(type) __nano_t(type, queue)
#define queue_create(type) __nano_fn(type, queue, create)
#define queue_free(type) __nano_fn(type, queue, free)
#define queue_clear(type) __nano_fn(type, queue, clear)
#define queue_enqueue(type) __nano_fn(type, queue, enqueue)
#define queue_dequeue(type) __nano_fn(type, queue, dequeue)
#define queue_first(type) __nano_fn(type, queue, first)
#define queue_last(type) __nano_fn(type, queue, last)
#define queue_clone(type) __nano_fn(type, queue, clone)
#define queue_equal(type) __nano_fn(type, queue, equal)
#define queue_copy(type) __nano_fn(type, queue, copy)
#define queue_find(type) __nano_fn(type, queue, find)
#define queue_find_cmp(type) __nano_fn(type, queue, find_cmp)
#define queue_fill(type) __nano_fn(type, queue, fill)
#define queue_count(type) __nano_fn(type, queue, count)
#define queue_count_cmp(type) __nano_fn(type, queue, count_cmp)
#define queue_all(type) __nano_fn(type, queue, all)
#define queue_all_cmp(type) __nano_fn(type, queue, all_cmp)
#define queue_any(type) __nano_fn(type, queue, any)
#define queue_any_cmp(type) __nano_fn(type, queue, any_cmp)
#define queue_join(type) __nano_fn(type, queue, join)
#define queue_reverse(type) __nano_fn(type, queue, reverse)
#define queue_resize(type) __nano_fn(type, queue, resize)
#define queue_lenght(type) __nano_fn(type, queue, lenght)
#define queue_map(type) __nano_fn(type, queue, map)
#define queue_filter(type) __nano_fn(type, queue, filter)

#endif

#define nano_declare_queue_alias(type, alias) \
    typedef type alias;                       \
    nano_declare_queue(alias)

#define nano_declare_queue_for(...) call_macro_x_for_each(nano_declare_queue, __VA_ARGS__)
#define nano_declare_queue(type)                                                                                            \
    typedef struct                                                                                                          \
    {                                                                                                                       \
        type *buffer;                                                                                                       \
        size_t lenght;                                                                                                      \
        size_t count;                                                                                                       \
    } queue(type);                                                                                                          \
    void __nano_fn(type, queue, create)(__nano_t(type, queue) * arr, size_t lenght);                                        \
    void __nano_fn(type, queue, free)(__nano_t(type, queue) * arr);                                                         \
    void __nano_fn(type, queue, clear)(__nano_t(type, queue) * arr);                                                        \
    void __nano_fn(type, queue, enqueue)(__nano_t(type, queue) * arr, type value);                                          \
    type __nano_fn(type, queue, denqueue)(__nano_t(type, queue) * arr);                                                     \
    type __nano_fn(type, queue, first)(__nano_t(type, queue) * arr);                                                        \
    type __nano_fn(type, queue, last)(__nano_t(type, queue) * arr);                                                         \
    void __nano_fn(type, queue, copy)(__nano_t(type, queue) * arr, __nano_t(type, queue) * *out, size_t start, size_t end); \
    void __nano_fn(type, queue, clone)(__nano_t(type, queue) * arr, __nano_t(type, queue) * *out);                          \
    bool __nano_fn(type, queue, equal)(__nano_t(type, queue) * a, __nano_t(type, queue) * b);                               \
    void __nano_fn(type, queue, fill)(__nano_t(type, queue) * arr, type value);                                             \
    int __nano_fn(type, queue, find)(__nano_t(type, queue) * arr, type value);                                              \
    int __nano_fn(type, queue, find_cmp)(__nano_t(type, queue) * arr, type value, bool (*cmp)(type a, type b));             \
    void __nano_fn(type, queue, resize)(__nano_t(type, queue) * arr, size_t lenght);                                        \
    size_t __nano_fn(type, queue, count)(__nano_t(type, queue) * arr, type value);                                          \
    size_t __nano_fn(type, queue, count_cmp)(__nano_t(type, queue) * arr, type value, bool (*cmp)(type a, type b));         \
    bool __nano_fn(type, queue, all)(__nano_t(type, queue) * arr, type value);                                              \
    bool __nano_fn(type, queue, all_cmp)(__nano_t(type, queue) * arr, type value, bool (*cmp)(type a, type b));             \
    bool __nano_fn(type, queue, any)(__nano_t(type, queue) * arr, type value);                                              \
    bool __nano_fn(type, queue, any_cmp)(__nano_t(type, queue) * arr, type value, bool (*cmp)(type a, type b));             \
    void __nano_fn(type, queue, join)(__nano_t(type, queue) * a, __nano_t(type, queue) * b);                                \
    void __nano_fn(type, queue, reverse)(__nano_t(type, queue) * arr);                                                      \
    size_t __nano_fn(type, queue, lenght)(__nano_t(type, queue) * arr);                                                     \
    void __nano_fn(type, queue, map)(__nano_t(type, queue) * vec, type * *out, type(*map_fn)(type value, size_t index));    \
    void __nano_fn(type, queue, filter)(__nano_t(type, queue) * vec, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);

#endif