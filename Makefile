PROPAG = propagacion/propagacion.c
MOVE = move/move.c
METRIC = metricas/metricas.c
LISTA = listaEnlazadaSimple.c
PERSONA = persona.c 

compil:
	gcc -o main main.c $(PROPAG) $(MOVE) $(METRIC) $(LISTA) $(PERSONA) -lm -lgsl -lgslcblas 
