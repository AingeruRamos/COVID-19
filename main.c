#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <math.h>

#include "globales.h"
#include "persona.h"
#include "listaEnlazadaSimple.h"
#include "estado/estado.h"
#include "propagacion/propagacion.h"
#include "move/move.h"
#include "metricas/metricas.h"

void InicializarParametros(char** argv,char* v);
void InicializarGlobales();
void calcular_edad(ListaEnlazadaRef lista,int n);

int main(int argc, char** argv) {

    int tiempo, n_metrica, flag;
    char *v = NULL;
    double seconds, microseconds,elapsed;
    struct timeval begin,end;

    if(argc != 9) {
        printf("Error en los parametros\n");
        return -1;
    }

    gettimeofday(&begin,0);

    srand(time(NULL));

    InicializarParametros(argv,v);
    InicializarGlobales();

    n_metrica = 0;
    flag = 0;

    for(tiempo=0; tiempo<TIEMPO_SIMULACION; tiempo++) {
        //Actualizar Estados
        EstadosPersonas(contagiados,sanos);
        VacunarPersonas(sanos);
        //Propagación
	AplicarPropagacion();
        //Movimiento
        AplicarMovimiento(sanos);
        AplicarMovimiento(contagiados);

        if(TIEMPO_BATCH == 0 || (tiempo % TIEMPO_BATCH) == 0) {
            if (tiempo == (TIEMPO_SIMULACION - 1)){
                flag = 1;
            }
            GuardarDatos(n_metrica,flag);
            n_metrica++;
        }
    }

    liberarListaEnlazada(sanos);
    liberarListaEnlazada(contagiados);

    gettimeofday(&end,0);

    seconds=end.tv_sec - begin.tv_sec;
    microseconds= end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;

    printf("El tiempo de ejecución es %f seconds.\n", elapsed);

    return 0;
}

void InicializarParametros(char** argv, char* v) {
    N_PERSONAS = strtol(argv[1], &v, 10);
    MAX_X = strtol(argv[2], &v, 10);
    MAX_Y = strtol(argv[3], &v, 10);
    TIEMPO_SIMULACION = strtol(argv[4], &v, 10);

    ALFA = strtol(argv[5], &v, 10);
    BETA = strtol(argv[6], &v, 10);
    PORCENT_VACUNACION = strtol(argv[7], &v, 10);

    TIEMPO_BATCH = strtol(argv[8], &v, 10);
}

void InicializarGlobales() {
    float porcent_vacunacion;

    N_SANOS = N_PERSONAS-1;
    N_CONTAGIADOS = 1;
    N_RECUPERADOS = 0;
    N_FALLECIDOS = 0;

    porcent_vacunacion = PORCENT_VACUNACION / 100;
    N_PERSONAS_VACU = (int) N_PERSONAS * porcent_vacunacion;
    N_PERSONAS_VACU_T = (int) N_PERSONAS_VACU / TIEMPO_SIMULACION;

    sanos = (ListaEnlazadaRef) malloc(sizeof(ListaEnlazada));
    contagiados = (ListaEnlazadaRef) malloc(sizeof(ListaEnlazada));

    int i;
    struct Persona* nueva_persona;

    crearVacia(sanos);
    for(i=0; i<N_SANOS; i++) {
        nueva_persona = NuevaPersona(i, 0);
        insertarNodoFinal(sanos, nueva_persona);
    }

    crearVacia(contagiados);
    nueva_persona = NuevaPersona(N_PERSONAS-1, 1);
    insertarNodoFinal(contagiados, nueva_persona);

    calcular_edad(sanos,N_SANOS);
    calcular_edad(contagiados,N_CONTAGIADOS);

    M_SANOS = 0.0;
    M_CONTAGIADOS = 0.0;
    M_RECUPERADOS = 0.0;
    M_FALLECIDOS = 0.0;
    R0 = 0.0;
}


void calcular_edad(ListaEnlazadaRef lista,int n){
    int semilla,edad,i;
    float mu;
    tipoNodoRef nodo = *lista;
    Persona *persona;
    gsl_rng *r;

    mu=110;
    semilla=1;

    gsl_rng_env_setup();
    r = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(r, semilla);

    //media edad = alfa / (alfa + beta)

    for (i=0 ; i< n; i++){
        persona = (Persona*) &nodo->info;
        edad = round(mu * gsl_ran_beta(r, ALFA, BETA));
        persona->edad = edad;
        persona->p_muerte = calcular_p_morir(edad);
        nodo = nodo->sig;
    }

    gsl_rng_free(r);
}

