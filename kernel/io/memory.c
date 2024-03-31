#include "memory.h"

uint8_t* ptr = (uint8_t*) 3145728;
void* kalloc(size_t size){
	void* ret = (void*) ptr;
	ptr += size;
	ptr+= 2;
	return ret;
}