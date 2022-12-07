#ifndef __OBSERVADOR_H__
#define __OBSERVADOR_H__

class Observador {
    public:
        virtual ~Observador(){}
        virtual void atualiza(int valor){}
};

#endif