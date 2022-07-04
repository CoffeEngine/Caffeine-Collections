#ifndef NANO_FOR_EACH_MACRO_H_
#define _get_nth_arg(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, N, ...) N

#define _fe_0(_call, ...)
#define _fe_1(_call, x) _call(x)
#define _fe_2(_call, x, ...) _call(x) _fe_1(_call, __VA_ARGS__)
#define _fe_3(_call, x, ...) _call(x) _fe_2(_call, __VA_ARGS__)
#define _fe_4(_call, x, ...) _call(x) _fe_3(_call, __VA_ARGS__)
#define _fe_5(_call, x, ...) _call(x) _fe_4(_call, __VA_ARGS__)
#define _fe_6(_call, x, ...) _call(x) _fe_5(_call, __VA_ARGS__)
#define _fe_7(_call, x, ...) _call(x) _fe_6(_call, __VA_ARGS__)
#define _fe_8(_call, x, ...) _call(x) _fe_7(_call, __VA_ARGS__)
#define _fe_9(_call, x, ...)) _call(x) _fe_8(_call, __VA_ARGS__)
#define _fe_10(_call, x, ...) _call(x) _fe_9(_call, __VA_ARGS__)
#define _fe_11(_call, x, ...) _call(x) _fe_10(_call, __VA_ARGS__)
#define _fe_12(_call, x, ...) _call(x) _fe_11(_call, __VA_ARGS__)
#define _fe_13(_call, x, ...) _call(x) _fe_12(_call, __VA_ARGS__)
#define _fe_14(_call, x, ...) _call(x) _fe_13(_call, __VA_ARGS__)
#define _fe_15(_call, x, ...) _call(x) _fe_14(_call, __VA_ARGS__)
#define _fe_16(_call, x, ...) _call(x) _fe_15(_call, __VA_ARGS__)
#define _fe_17(_call, x, ...) _call(x) _fe_16(_call, __VA_ARGS__)
#define _fe_18(_call, x, ...) _call(x) _fe_17(_call, __VA_ARGS__)
#define _fe_19(_call, x, ...) _call(x) _fe_18(_call, __VA_ARGS__)
#define _fe_20(_call, x, ...) _call(x) _fe_19(_call, __VA_ARGS__)
#define _fe_21(_call, x, ...) _call(x) _fe_20(_call, __VA_ARGS__)
#define _fe_22(_call, x, ...) _call(x) _fe_21(_call, __VA_ARGS__)
#define _fe_23(_call, x, ...) _call(x) _fe_22(_call, __VA_ARGS__)
#define _fe_24(_call, x, ...) _call(x) _fe_23(_call, __VA_ARGS__)
#define _fe_25(_call, x, ...) _call(x) _fe_24(_call, __VA_ARGS__)
#define _fe_26(_call, x, ...) _call(x) _fe_25(_call, __VA_ARGS__)
#define _fe_27(_call, x, ...) _call(x) _fe_26(_call, __VA_ARGS__)
#define _fe_28(_call, x, ...) _call(x) _fe_27(_call, __VA_ARGS__)
#define _fe_29(_call, x, ...) _call(x) _fe_28(_call, __VA_ARGS__)
#define _fe_30(_call, x, ...) _call(x) _fe_29(_call, __VA_ARGS__)
#define _fe_31(_call, x, ...) _call(x) _fe_30(_call, __VA_ARGS__)
#define _fe_32(_call, x, ...) _call(x) _fe_31(_call, __VA_ARGS__)

#ifdef _MSC_VER
#define call_macro_x_for_each(x, ...)                                                                                    \
    _get_nth_arg(##__VA_ARGS__,                                                                               \
                 _fe_32, _fe_31, _fe_30, _fe_29, _fe_28, _fe_27, _fe_26, _fe_25, _fe_24, _fe_23, _fe_22, _fe_21, _fe_20, \
                 _fe_19, _fe_18, _fe_17, _fe_16, _fe_15, _fe_14, _fe_13, _fe_12, _fe_11, _fe_10,                         \
                 _fe_9, _fe_8, _fe_7, _fe_6, _fe_5, _fe_4, _fe_3, _fe_2, _fe_1, _fe_0)(x, ##__VA_ARGS__)
#else
#define call_macro_x_for_each(x, ...)                                                                                    \
    _get_nth_arg("ignored", ##__VA_ARGS__,                                                                               \
                 _fe_32, _fe_31, _fe_30, _fe_29, _fe_28, _fe_27, _fe_26, _fe_25, _fe_24, _fe_23, _fe_22, _fe_21, _fe_20, \
                 _fe_19, _fe_18, _fe_17, _fe_16, _fe_15, _fe_14, _fe_13, _fe_12, _fe_11, _fe_10,                         \
                 _fe_9, _fe_8, _fe_7, _fe_6, _fe_5, _fe_4, _fe_3, _fe_2, _fe_1, _fe_0)(x, ##__VA_ARGS__)
#endif

#endif