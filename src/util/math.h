#pragma once

#include <cglm/cglm.h>
#include <cglm/struct.h>

#include "types.h"

#define PI_2 GLM_PI_2
#define PI GLM_PI
#define TAU (2 * PI)
#define F32_EPSILON FLT_EPSILON
#define F64_EPSILON DBL_EPSILON

#define cosf(_x) ((f32)cos(_x))
#define sinf(_x) ((f32)sin(_x))
#define radians(_x) ((_x) * (PI / 180.0f))
#define degrees(_x) ((_x) * (180.0f / PI))
#define floori(_x) ((s32)(floor((f64)(_x))))

#define sign(_x)                                                                                             \
    ({                                                                                                       \
        __typeof__(_x) _xx = (_x);                                                                           \
        ((__typeof__(_x))((((__typeof__(_x))0) < _xx) - (_xx < ((__typeof__(_x))0))));                       \
    })

#ifdef max
#undef max
#endif

#define max(_a, _b)                                                                                          \
    ({                                                                                                       \
        __typeof__(_a) __a = (_a);                                                                           \
        __typeof__(_b) __b = (_b);                                                                           \
        __a > __b ? __a : __b;                                                                               \
    })

#ifdef min
#undef min
#endif

#define min(_a, _b)                                                                                          \
    ({                                                                                                       \
        __typeof__(_a) __a = (_a);                                                                           \
        __typeof__(_b) __b = (_b);                                                                           \
        __a < __b ? __a : __b;                                                                               \
    })

#define clamp(_x, _mn, _mx)                                                                                  \
    ({                                                                                                       \
        __typeof__(_x) __x = (_x);                                                                           \
        __typeof__(_mn) __mn = (_mn);                                                                        \
        __typeof__(_mx) __mx = (_mx);                                                                        \
        max(__mn, min(__mx, __x));                                                                           \
    })