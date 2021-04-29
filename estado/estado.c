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

    while(nodo_aux->sig != NULL){

        indice_borrar=ActualizarEstado(nodo_aux,&flag);
        if (flag == 1){
            eliminarNodoPosicionIndice(lista, indice_borrar);
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
                PersonaSana(persona->id); //
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
    int vacunados;

  //  vacunados = N_PERSONAS_VACU_T;
    printf("gshgs");
                fflush(stdin);
    vacunados = N_PERSONAS_VACU_T;
    if(!estaVacia(*lista)){
    while((nodo_aux->sig != NULL) || (vacunados != 0)){

//        Persona *persona = (Persona*) &nodo_aux->info;

        if ((nodo_aux->info.estado == 0) || (nodo_aux->info.estado == 3)){
            nodo_aux->info.estado = 4; //si que quiere aplicar politica, switch
        }
        vacunados--;

	nodo_aux = nodo_aux->sig;
    }
    }
}


void PersonaSana(int indice){
   tipoNodoRef nodo_sano = *sanos;
   tipoNodoRef nodo_contagiado = *contagiados;
   tipoNodoRef nodo_ant;

    while(nodo_contagiado->sig != NULL){
        Persona *persona = (Persona*) &nodo_contagiado->info;
        if ( persona->id != indice){
            nodo_ant = nodo_contagiado;
            nodo_contagiado = nodo_contagiado->sig;
        }
        else{
            printf("%d- %d",persona->id,indice);
            while(nodo_sano->sig != NULL){
                nodo_sano = nodo_sano->sig;
            }
            nodo_sano->sig = nodo_contagiado;
            nodo_ant->sig = nodo_contagiado->sig;
            nodo_contagiado->sig = NULL;
        }
    }
}
