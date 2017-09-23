
#include "../memory/memory.h"
#include "memory.h"

void* malloc(unsigned int size) {
	return (void*) kmalloc(size);
	
}

void mfree(void* ptr, unsigned int size) {
	kfree(ptr, size);
	
}
