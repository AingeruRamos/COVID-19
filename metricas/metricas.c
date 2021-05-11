#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../globales.h"
#include "../listaEnlazadaSimple.h"

void GuardarPosiciones(char* nombre) {
    char* nombreFichero = (char*) malloc(sizeof(char)*200);
    strcpy(nombreFichero, nombre);
    strcat(nombreFichero, ".pos");

    FILE* fp = fopen(nombreFichero, "w");

    tipoNodoRef nodo_aux = *sanos;
    struct Persona* persona;;
    while(nodo_aux != NULL) {
        persona = (struct Persona*) &nodo_aux->info;
        fprintf(fp, "ID: %d; ", persona->id);
        fprintf(fp, "Posicion(X: %d, Y: %d); ", persona->pos.x, persona->pos.y);
        fprintf(fp, "Estado: %d", persona->estado);
        fputs("\n", fp);
        nodo_aux = nodo_aux->sig;
    }

    fprintf(fp, "\n");

    nodo_aux = *contagiados;
    while(nodo_aux != NULL) {
        persona = (struct Persona*) &nodo_aux->info;
        fprintf(fp, "ID: %d; ", persona->id);
        fprintf(fp, "Posicion(X: %d, Y: %d); ", persona->pos.x, persona->pos.y);
        fprintf(fp, "Estado: %d", persona->estado);
        fputs("\n", fp);
        nodo_aux = nodo_aux->sig;
    }

    fclose(fp);
    free(nombreFichero);
}

void GuardarMetricas(char* nombre) {
    char* nombreFichero = (char*) malloc(sizeof(char)*200);
    strcpy(nombreFichero, nombre);
    strcat(nombreFichero, ".metricas");

    FILE* fp = fopen(nombreFichero, "w");

    M_SANOS = (float) N_SANOS / N_PERSONAS;
    M_CONTAGIADOS = (float) N_CONTAGIADOS / N_PERSONAS;
    M_RECUPERADOS =(float) N_RECUPERADOS /N_PERSONAS;
    M_FALLECIDOS = (float) N_FALLECIDOS / N_PERSONAS;
    if (N_CONTAGIADOS == 0){
        R0 = N_CONTAGIADOS;
    }
    else{
        R0= N_CONTAGIADOS-1;
    }

    fprintf(fp, "SANOS: %f\n", M_SANOS);
    fprintf(fp, "CONTAGIADOS: %f\n", M_CONTAGIADOS);
    fprintf(fp, "RECUPERADOS: %f\n", M_RECUPERADOS);
    fprintf(fp, "FALLECIDOS: %f\n", M_FALLECIDOS);
    fprintf(fp, "R0: %f\n", R0);

    fclose(fp);
    free(nombreFichero);
}

void GuardarDatos(int id_metricas, int flag) {
    char* ruta = (char*) malloc(sizeof(char)*200);
    sprintf(ruta, "datos/%d_%d_%d_%d_%d_%d_%d/", N_PERSONAS, MAX_X, MAX_Y, TIEMPO_SIMULACION, ALFA, BETA, PORCENT_VACUNACION);
    mkdir(ruta, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    sprintf(ruta, "%s%d", ruta, id_metricas);

    GuardarPosiciones(ruta);

    if (flag == 1){
        GuardarMetricas(ruta);
    }

    free(ruta);
}
