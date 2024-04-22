#define __init __attribute__ ((__section__(".init.text")))
#define __exit __attribute__ ((__section__(".init.exit")))
#define __initdata __attribute__ ((__section__(".init.data")))
