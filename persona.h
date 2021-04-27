#ifndef _PERSONA_H_
#define _PERSONA_H_

struct Posicion {
    int x, y;
};

struct Velocidad {
    int modulo;
    float ux, uy; //Vector unitario de dirección
};

struct Persona {
    int id;
    int edad;
    int estado;
    float p_muerte; //Probabilidad de muerte
    struct Posicion pos;
    struct Velocidad vel;
} typedef Persona;

struct Persona* NuevaPersona(int id, int edad, int estado, float p_muerte);
void PrintPersona(struct Persona* persona);

#endif
