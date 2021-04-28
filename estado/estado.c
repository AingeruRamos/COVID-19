#include "estado.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../globales.h"
#include "../persona.h"
#include "../listaEnlazadaSimple.h"


void EstadosPersonas(ListaEnlazadaRef lista){
    tipoNodoRef nodo_aux = *lista;
    int flag, indice_borrar;
    flag=0;

    while(nodo_aux != NULL){

        indice_borrar=ActualizarEstado(nodo_aux,&flag);
        if (flag == 1){
//            eliminarNodoPosicionIndice(lista, indice_borrar);
        }

        nodo_aux = nodo_aux->sig;
    }
}

int ActualizarEstado(tipoNodoRef nodo,int *flag){  //devuelve indice si la persona se muere
    Persona *persona = (Persona*) &nodo->info;
    float muerte;

    if (persona->estado == 1){  //si la persona esta contagiada, cuando presenta sintomas
            if (persona->cont_incu == PERIODO_INCUBACION){
                persona->estado = 2;
                persona->cont_incu = 0;
             }
             else{
                persona->cont_incu++;
             }
	}

	if (persona->estado == 2){ //si la persona tiene covid, cuando se recupera
            if (persona->cont_recu == PERIODO_RECUPERACION){
                persona->estado = 3;
                persona->cont_recu = 0;
            }
            else{
                srand(time(NULL));
                muerte = rand() % 101;
                muerte = muerte / 100;
                if (muerte >= persona->p_muerte){
                    persona->estado = 5;
                    N_FALLECIDOS++;
                    *flag=1;
                    return persona->id;
                }
                else{
                    persona->cont_recu++;
                }
            }
	}
}


void VacunarPersonas(ListaEnlazadaRef lista){
    tipoNodoRef nodo_aux = *lista;
    Persona persona;
    int vacunados;

    vacunados = N_PERSONAS_VACU_T;

    while((nodo_aux->sig != NULL) || (vacunados != 0)){

        persona = (Persona) nodo_aux->info;

        if ((persona.estado == 0) || (persona.estado == 3)){
            persona.estado = 4; //si que quiere aplicar politica, switch
        }
        vacunados--;

	nodo_aux = nodo_aux->sig;
    }
}
