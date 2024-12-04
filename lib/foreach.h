#ifndef __FOREACH_H
#define __FOREACH_H

#include "connect.h"

#define foreach2(__type, __array)                                               \
            using(__type *_p = __array)                                         \
            for (   uint_fast32_t CONNECT2(count,__LINE__) = dimof(__array);    \
                    CONNECT2(count,__LINE__) > 0;                               \
                    _p++, CONNECT2(count,__LINE__)--                            \
                )

#define foreach3(__type, __array, __item)                                       \
            using(__type *_p = __array, *__item = _p, _p = _p, )                \
            for (   uint_fast32_t CONNECT2(count,__LINE__) = dimof(__array);    \
                    CONNECT2(count,__LINE__) > 0;                               \
                    _p++, __item = _p, CONNECT2(count,__LINE__)--               \
                )


#define foreach(...)	CONNECT2(foreach, VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)


#endif
