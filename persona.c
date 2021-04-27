#include "persona.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globales.h"

struct Persona* NuevaPersona(int id, int edad, int estado, float p_muerte) {
    struct Persona* persona = (struct Persona*) malloc(sizeof(struct Persona));
    persona->id = id;

    //Hacer lo de la función beta
    persona->edad = edad;
    persona->estado = estado;

    //Debe ser en función de la edad
    persona->p_muerte = p_muerte;
    
    persona->pos.x = rand() % MAX_X;
    persona->pos.y = rand() % MAX_Y;

    persona->vel.modulo = (int) (rand() % MAX_MODULE);
    float r = ((float) rand()/(float) RAND_MAX) * 2; //Número aleatorio entre 0..2
    persona->vel.ux = cos(r*M_PI); //En radianes
    persona->vel.uy = sin(r*M_PI);

    return persona;
}

void PrintPersona(struct Persona* persona) {
    printf("ID: %d\n", persona->id);
    printf("EDAD: %d\n", persona->edad);
    printf("ESTADO: %d\n", persona->estado);
    printf("P_MUERTE: %f\n", persona->p_muerte);
    printf("POS: %d, %d\n", persona->pos.x, persona->pos.y);
    printf("VEL: M %d, UX %f, UY %f\n", persona->vel.modulo, persona->vel.ux, persona->vel.uy);
}