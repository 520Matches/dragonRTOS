#include "plaform.h"

typedef struct {
	int (*register)(void *d, d_type_t type);
	int (*match)(void *device, void *driver);
}plaform_bus_t;
