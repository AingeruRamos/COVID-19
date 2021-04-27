#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "globales.h"

#include "persona.h"
#include "listaEnlazadaSimple.h"
#include "move/move.h"
#include "metricas/metricas.h"

void InicializarParametros(char** argv);
void InicializarGlobales();

int main(int argc, char** argv) {

    if(argc != 9) {
        printf("Error en los parametros\n");
        return -1;
    }

    srand(time(NULL));

    InicializarParametros(argv);
    InicializarGlobales();
    
    int tiempo, n_metrica;
    n_metrica = 0;
    for(tiempo=0; tiempo<TIEMPO_SIMULACION; tiempo++) {
        //Actualizar Estados

        //Propagación

        //Movimiento
        AplicarMovimiento(sanos);
        AplicarMovimiento(contagiados);

        if(TIEMPO_BATCH == 0 || (tiempo % TIEMPO_BATCH) == 0) {
            GuardarDatos(n_metrica);
            n_metrica++;
        }
    }

    return 0;
}

void InicializarParametros(char** argv) {
    N_PERSONAS = (int) atoi(argv[1]);
    MAX_X = (int) atoi(argv[2]);
    MAX_Y = (int) atoi(argv[3]);
    TIEMPO_SIMULACION = (int) atoi(argv[4]);

    ALFA = (float) atof(argv[5]);
    BETA = (float) atof(argv[6]);
    PORCENT_VACUNACION = (float) atof(argv[7]);

    TIEMPO_BATCH = (int) atoi(argv[8]);
}

void InicializarGlobales() {
    N_SANOS = N_PERSONAS-1;
    N_CONTAGIADOS = 1;
    N_RECUPERADOS = 0;
    N_FALLECIDOS = 0;

    sanos = (ListaEnlazadaRef) malloc(sizeof(ListaEnlazada));
    contagiados = (ListaEnlazadaRef) malloc(sizeof(ListaEnlazada));

    int i;
    struct Persona* nueva_persona;

    crearVacia(sanos);
    for(i=0; i<N_SANOS; i++) {
        nueva_persona = NuevaPersona(i, 10, 0, 0.1);
        insertarNodoFinal(sanos, nueva_persona);
    }

    crearVacia(contagiados);
    nueva_persona = NuevaPersona(N_PERSONAS, 10, 1, 0.1);
    insertarNodoFinal(contagiados, nueva_persona);

    M_SANOS = 1.0;
    M_CONTAGIADOS = 1.0;
    M_RECUPERADOS = 1.0;
    M_FALLECIDOS = 1.0;
    R0 = 1.0;
}