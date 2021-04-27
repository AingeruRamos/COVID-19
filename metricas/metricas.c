#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../globales.h"
#include "../listaEnlazadaSimple.h"

void GuardarPosiciones(char* nombre) {
    char* nombreFichero = (char*) malloc(sizeof(char)*14);
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
    char* nombreFichero = (char*) malloc(sizeof(char)*19);
    strcpy(nombreFichero, nombre);
    strcat(nombreFichero, ".metricas");

    FILE* fp = fopen(nombreFichero, "w");

    if(TIEMPO_BATCH != 0) {
        M_SANOS /= TIEMPO_BATCH+1;
        M_CONTAGIADOS /= TIEMPO_BATCH+1;
        M_RECUPERADOS /= TIEMPO_BATCH+1;
        M_FALLECIDOS /= TIEMPO_BATCH+1;
        R0 /= TIEMPO_BATCH; //Esto probablemente no sea asi
    }

    fprintf(fp, "SANOS: %f\n", M_SANOS);
    fprintf(fp, "CONTAGIADOS: %f\n", M_CONTAGIADOS);
    fprintf(fp, "RECUPERADOS: %f\n", M_RECUPERADOS);
    fprintf(fp, "FALLECIDOS: %f\n", M_FALLECIDOS);
    fprintf(fp, "R0: %f\n", R0);
    
    M_SANOS = 0.0;
    M_CONTAGIADOS = 0.0;
    M_RECUPERADOS = 0.0;
    M_FALLECIDOS = 0.0;
    R0 = 0.0; //Esto probablemente no sea asi
  
    fclose(fp);
    free(nombreFichero);
}

void GuardarDatos(int id_metricas) {
    char* ruta = (char*) malloc(sizeof(char)*16);
    strcpy(ruta, "datos/");

    char* nombre = (char*) malloc(sizeof(char)*10);
    sprintf(nombre, "%d", id_metricas);

    strcat(ruta, nombre);
    free(nombre);

    GuardarPosiciones(ruta);
    GuardarMetricas(ruta);

    free(ruta);
}