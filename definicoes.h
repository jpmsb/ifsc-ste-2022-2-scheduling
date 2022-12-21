#ifndef __DEFINICOES_H__
#define __DEFINICOES_H__

typedef unsigned long long Microssegundos; // 64 bits

#define SCHED_FIFO 0
#define SCHED_RMS 1
#define SCHED_EDD 2

#define SCHED_TYPE SCHED_EDD

// Enable dynamic objects creation/destruction with C++
typedef unsigned int size_t;
void *operator new   (size_t objsize);
void  operator delete(void* obj);

#endif // __DEFINICOES_H__