#include "definicoes.h"

#include <stdlib.h>
void* operator new(size_t objsize) { 
    return malloc(objsize); 
} 

void operator delete(void* obj, size_t size) { 
    free(obj); 
}
