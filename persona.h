#ifndef _PERSONA_H_
#define _PERSONA_H_

typedef struct Posicion {
    int x, y;
};

typedef struct Velocidad {
    int modulo;
    float ux, uy; //Vector unitario de dirección
};

typedef struct Persona {
    int id;
    int edad;
    int estado;
    int cont_incu; //contador para el tiempo de incubacion
    int  cont_recu; //contador para el tiepo de recuperacion
    float p_muerte; //Probabilidad de muerte
    struct Posicion pos;
    struct Velocidad vel;
}Persona;

Persona* NuevaPersona(int id, int edad, int estado, float p_muerte);
void PrintPersona(Persona* persona);
int calcular_edad();
float calcular_p_morir(int edad);

#endif
