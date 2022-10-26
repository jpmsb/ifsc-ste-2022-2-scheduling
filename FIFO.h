#ifndef __FIFO_H__
#define __FIFO_H__

template<typename T, int N> class FIFO {
    public:
        enum FIFO_Errors_t {
            FIFO_ERROR_FULL = -2,
            FIFO_ERROR_EMPTY = -1,
            FIFO_SUCCESS = 0
        };

        FIFO() { clear(); }
        ~FIFO() {}

        FIFO_Errors_t enqueue(T data){
            if (size() >= capacity()){
                return FIFO_ERROR_FULL;
            }

            buffer[tail] = data;
            tail = (tail + 1) % N;
            contador++;

            return FIFO_SUCCESS;
        }
        FIFO_Errors_t dequeue(T * data){
            if (size() == 0) return FIFO_ERROR_EMPTY;

            *data = buffer[head];
            head = (head + 1) % N;
            contador--;
            return FIFO_SUCCESS;
        }

        void clear(){
            contador = 0;
            head = 0;
            tail = 0;
        }

        unsigned int size() {
            return contador; 
        }

        const unsigned int capacity() { 
            return N; 
        }

    private:
        T buffer[N];
        unsigned int head, tail, contador;
};

#endif