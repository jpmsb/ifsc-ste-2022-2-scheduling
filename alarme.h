#ifndef __ALARME_H__
#define __ALARME_H__

#include "definicoes.h"
#include "observador.h"
#include "fila_de_funcao.h"
#include "lista_encadeada.h"
#include "temporizador.h"

class Alarme : public Observador {
    public:
        Alarme(FilaDeFuncao * _ffuncao) : ffuncao(_ffuncao) {}
        ~Alarme() {}

        void agenda(Evento * evento){
            Microssegundos tempo_corrigido = evento->tempo - (TIMER0::micros() - evento->release_time);
            __asm__("cli");
            eventos.insere(evento, tempo_corrigido);
            __asm__("sei");
        }

        void atualiza(int valor){
            Microssegundos rank = eventos.atualiza_rank_inicio(valor);
            while (rank == 0){
                Evento *evento = eventos.remove_inicio();
                evento->release_time = TIMER0::micros();
                ffuncao->insere(evento, evento->prioridade);
                rank = eventos.atualiza_rank_inicio(0);             
            }
        }

    private:
        FilaDeFuncao * ffuncao;
        ListaEncadeada<Evento*, true, true, Microssegundos> eventos;
};

#endif
