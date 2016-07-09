#ifndef __LOADER_TYPES_H__
#define __LOADER_TYPES_H__

#include <machine/types.h>

#define NULL (void*)0

/* CONCAT(x,y) concatenates identifiers 'x' and 'y' => xy */
#define __CONCAT(x,y) x ## y
#define CONCAT(x,y) __CONCAT(x,y)

#endif /* __LOADER_TYPES_H__ */
