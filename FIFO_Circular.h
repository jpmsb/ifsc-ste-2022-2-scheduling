#ifndef __FIFO_CIRCULAR__
#define __FIFO_CIRCULAR__

#include <string.h>

template<typename T, int N> class FIFO_C {
    public:
        FIFO_C(){
            clear();
        }

        ~FIFO_C(){}

        void enqueue(T valor){
            head = ++head % N;
            buffer[head] = valor;
        }

        int get(int pos){
            return buffer[pos];
        }

        int getLast(){
            return buffer[head];
        }

        void clear(){
            memset(buffer, 0, N);
            head = -1;
        }

    private:
        T buffer[N];
        unsigned int head;
};
#endif