#ifndef _ESTADO_H_
#define _ESTADO_H_

#include "../listaEnlazadaSimple.h"

void EstadosPersonas(ListaEnlazadaRef lista);
int ActualizarEstado(tipoNodoRef nodo,int *flag);
void VacunarPersonas(ListaEnlazadaRef lista);
void PersonaSana(int id);
#endif

