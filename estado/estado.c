#include "estado.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../globales.h"
#include "../persona.h"
#include "../listaEnlazadaSimple.h"


void SigueintePersona(ListaEnlazadaRef lista){
    tipoNodoRef nodo_aux = *lista;

    while(nodo_aux != NULL){
        ActualizarEstado(nodo_aux);
        nodo_aux = nodo_aux->sig;
    }
}

void ActualizarEstado(tipoNodoInfo nodo){
    Persona* persona = (Persona*) &nodo->info;
    float muerte;

    if (nodo_aux->estado == 1){
            if (nodo_aux->cont_incu == PERIODO_INCUBACION){
                nodo_aux->estado = 2;
                nodo_aux->cont_incu = 0;
             }
             else{
                nodo_aux->cont_incu++;
             }
	}

	if (nodo_aux->estado == 2){
            if (nodo_aux->cont_recu == PERIODO_RECUPERACION){
                nodo_aux->estado = 3;
                nodo_aux->cont_recu = 0;
            }
            else{
                srand(time(NULL));
                muerte = rand() % 101;
                muerte = muerte / 100;
                if (muerte >= nodo_aux->p_muerte){
                    nodo_aux->estado = 5;
                    //liberar nodo????
                }
                else{
                    nodo_aux->cont_recu++;
                }
            }
	}

       


}
