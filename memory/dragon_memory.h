#ifndef __MEMORY_H
#define __MEMORY_H


#include <stdint.h>


#define dmb()		__asm__ __volatile__ ("" : : : "memory")

#define __read_int(a)			(*(volatile unsigned int *)(a))
#define __write_int(v,a)		(*(volatile unsigned int *)(a) = (v))

#define __read_byte(a)			(*(volatile unsigned char *)(a))
#define __write_byte(v,a)		(*(volatile unsigned char *)(a) = (v))

#define __read_long(a)			(*(volatile unsigned long *)(a))
#define __write_long(v,a)		(*(volatile unsigned long *)(a) = (v))


#define read_long(c)	({ unsigned int  __v = __read_long((unsigned long)c); dmb(); __v; })
#define write_long(v,c)	({ unsigned int  __v = v; dmb(); __write_long(__v, (unsigned long)c);})

#define read_byte(c)	({ unsigned char  __v = __read_byte(c); dmb(); __v; })
#define write_byte(v,c)	({ unsigned char  __v = v; dmb(); __write_byte(__v,c);})

#define read_int(c)	({ unsigned long  __v = __read_int(c); dmb(); __v; })
#define write_int(v,c)	({ unsigned long  __v = v; dmb(); __write_int(__v,c);})



#define offsetof(TYPE, MEMBER) ((uint32_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({              \
    void *__mptr = (void *)(ptr);                   \
    ((type *)(__mptr - offsetof(type, member))); })




#endif
