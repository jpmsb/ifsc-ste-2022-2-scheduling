// Arquivo: fifo.h
// Autor: Arliones Hoeller, IFSC-SJE

#ifndef __FIFO_H__
#define __FIFO_H__

template<typename T, int N>
class FIFO
{
public:
    enum FIFO_Errors_t
    {
        FIFO_ERROR_FULL = -2,
        FIFO_ERROR_EMPTY = -1,
        FIFO_SUCCESS = 0
    };

    FIFO()
    {
        clear();
    }
    
    ~FIFO()
    {
    }

    FIFO_Errors_t enqueue(T data)
    {
        // If queue is full return error
        if (size() >= capacity())
        {
            return FIFO_ERROR_FULL;
        }

        buffer[tail] = data;
        tail = (tail + 1) % N;
        count++;

        return FIFO_SUCCESS;
    }

    FIFO_Errors_t dequeue(T * data)
    {
        // If queue is empty return error
        if (size() == 0)
        {
            return FIFO_ERROR_EMPTY;
        }

        *data = buffer[head];
        head = (head + 1) % N;
        count--;

        return FIFO_SUCCESS;
    }

    void clear()
    {
        count = 0;
        head = 0;
        tail = 0;
    }

    unsigned int size() { return count; }
    const unsigned int capacity() { return N; }

private:
    T buffer[N];
    unsigned int head, tail, count;
};

#endif
