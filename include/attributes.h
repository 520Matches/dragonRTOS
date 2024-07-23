#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

#define __WEAK	__attribute__((weak))


#define __INIT __attribute__ ((__section__(".init.text")))
#define __EXIT __attribute__ ((__section__(".init.exit")))
#define __INITDATA __attribute__ ((__section__(".init.data")))

#endif
