#ifndef _GLOBALES_H_
#define _GLOBALES_H_

#include "listaEnlazadaSimple.h"

//CONSTANTES
#define MAX_MODULE 5
#define RADIO_CONTAGIO 5
#define P_CAMBIO_VEL 0.5

//PARAMETROS DE ENTRADA
int N_PERSONAS;
int MAX_X;
int MAX_Y;
int TIEMPO_SIMULACION;
float ALFA;
float BETA;
float PORCENT_VACUNACION;
int TIEMPO_BATCH;

//GLOBALES
ListaEnlazadaRef sanos;
ListaEnlazadaRef contagiados;

int N_SANOS;
int N_CONTAGIADOS;
int N_RECUPERADOS;
int N_FALLECIDOS;

//METRICAS
float M_SANOS;
float M_CONTAGIADOS;
float M_RECUPERADOS;
float M_FALLECIDOS;
float R0;

#endif