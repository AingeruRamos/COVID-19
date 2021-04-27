#include "propagacion.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../globales.h"
#include "../persona.h"
#include "../listaEnlazadaSimple.h"

float DistanciaEntrePersonas(struct Persona* p1, struct Persona* p2) {
    int dx;
    if(p1->pos.x > p2->pos.x) { dx = p1->pos.x-p2->pos.x; } 
    else { dx = p2->pos.x-p1->pos.x; }

    int dy;
    if(p1->pos.y > p2->pos.y) { dy = p1->pos.y-p2->pos.y; } 
    else { dy = p2->pos.y-p1->pos.y; }

    return sqrt(dx*dx+dy*dy);
}

void AplicarPropagacion() {
    tipoNodoRef nodo_sanos = *sanos;
    tipoNodoRef nodo_contagiados = *contagiados;
    tipoNodoRef nodo_aux;

    struct Persona* persona_sana;
    struct Persona* persona_contagiada;
    struct Persona* persona_copia;

    float d, r;
    int cambio_nodo;

    while(nodo_sanos != NULL) {
	cambio_nodo = 1;
        persona_sana = &nodo_sanos->info;
        while(nodo_contagiados != NULL) {
            persona_contagiada = &nodo_contagiados->info;
            d = DistanciaEntrePersonas(persona_sana, persona_contagiada);
            if(d < RADIO_CONTAGIO) {
               r = ((float) rand()/(float) RAND_MAX);
               if(r < P_CONTAGIO) {
		   cambio_nodo = 0;
		   nodo_aux = nodo_sanos->sig;
		   persona_copia = CopiarPersona(persona_sana);
                   persona_copia->estado = 3;
                   eliminarNodo(sanos, nodo_sanos);
		   insertarNodoComienzo(contagiados, persona_copia);
                }
            }
            nodo_contagiados = nodo_contagiados->sig;
        }
	if(cambio_nodo) {
            nodo_sanos = nodo_sanos->sig;
   	} else {
	    nodo_sanos = nodo_aux;
	}
   }
}
