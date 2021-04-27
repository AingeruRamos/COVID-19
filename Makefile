MOVE = move/move.c
METRIC = metricas/metricas.c
LISTA = listaEnlazadaSimple.c
PERSONA = persona.c

compil:
	gcc -o main main.c $(MOVE) $(METRIC) $(LISTA) $(PERSONA) -lm 
