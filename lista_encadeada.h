#ifndef __LISTA_ENCADEADA__
#define __LISTA_ENCADEADA__

#include "definicoes.h"
#include <stdlib.h>

template<typename T, bool ORDENADA = false, bool RELATIVA = false, typename T_ORDEM = char> class ListaEncadeada {
    public:
        struct Elemento {
            Elemento *proximo, *anterior;
            T dado;
            T_ORDEM rank;
        };
        

        ListaEncadeada() : inicio(0), fim(0), _tamanho(0) {}
        ~ListaEncadeada() {}

        void insere(T _dado, T_ORDEM _rank = 0){
            if (_tamanho == 0) insere_primeiro(_dado, _rank);
            else {
                if (ORDENADA) insere_ordenada(_dado, _rank);
                else anexa(_dado, _rank);
            }
            _tamanho++;
        }

        T obtem(int posicao){
            Elemento *elemento = inicio;
            while (posicao--) elemento = elemento->proximo;
            return elemento->dado;
        }

        T remove_inicio() {
            T temporario = inicio->dado;
            Elemento *inicio_antigo = inicio;
            if (inicio->proximo != 0) inicio->proximo->anterior = inicio->anterior;
            inicio = inicio->proximo;
            delete inicio_antigo;
            _tamanho--;
            return temporario;

        }

        T_ORDEM atualiza_rank_inicio(T_ORDEM valor){
            if (_tamanho == 0) return -1;
            if (valor > inicio->rank) inicio->rank = 0;
            else inicio->rank -= valor;

            return inicio->rank;
        }

        int tamanho() { 
            return _tamanho;
        }

    private:
        void insere_primeiro(T _dado, T_ORDEM _rank){
            Elemento *elemento = new Elemento();
            elemento->dado = _dado;
            elemento->rank = _rank;
            elemento->anterior = 0;
            elemento->proximo = 0;
            inicio = elemento;
            fim = elemento;
        }

        void insere_ordenada(T _dado, T_ORDEM _rank){
            Elemento *seguinte = inicio;
            while ((seguinte != 0) && (_rank > seguinte->rank)) {
                if (RELATIVA) _rank -= seguinte->rank;
                seguinte = seguinte->proximo;
            }

            if (seguinte == 0){
                anexa(_dado, _rank);
                return;
            }

            // inserindo o elemento no meio da lista
            Elemento *elemento = new Elemento();
            elemento->dado = _dado;
            elemento->rank = _rank;

            // Inserindo elemento entre dois nodos
            // Ligando os ponteiros do elemento a ser inserido
            elemento->proximo = seguinte;
            elemento->anterior = seguinte->anterior;

            // Caso haja um elemento anterior, o próximo desse anterior
            // é o elemento a ser inserido
            if (elemento->anterior) elemento->anterior->proximo = elemento;

            // Atualizando ponteiro anterior do elemento seguinte
            // a este que está sendo inserido
            seguinte->anterior = elemento;

            // Se o elemento procurado for o primeiro,
            // o ponteiro de início deve ser atualizado
            if (seguinte == inicio) inicio = elemento;

            // Ajustando o rank do elemento seguinte, já
            // que a fila é relativa
            if (RELATIVA) seguinte->rank -= _rank;
        }

        void anexa(T _dado, T_ORDEM _rank){
            Elemento *elemento = new Elemento();
            elemento->dado = _dado;
            elemento->rank = _rank;
            elemento->anterior = fim;
            elemento->proximo = 0;
            fim->proximo = elemento;
            fim = elemento;
        }

        Elemento *inicio, *fim;
        int _tamanho;
};

#endif