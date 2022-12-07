#ifndef __DEFINICOES_H__
#define __DEFINICOES_H__

typedef unsigned long long Microssegundos; // 64 bits

// Enable dynamic objects creation/destruction with C++
typedef unsigned int size_t;
void *operator new   (size_t objsize);
void  operator delete(void* obj);

#endif // __DEFINICOES_H__