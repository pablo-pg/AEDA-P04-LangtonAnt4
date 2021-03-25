#
# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Algoritmia y Estrucuta de Datos Avanzada 2020/21
#
# Autor: Pablo Pérez González
# Fecha: Marzo de 2021
# e-mail: alu0101318318@ull.edu.es
# 
# Makefile para la Práctica 3: El Mundo Hormiga.
#


CC=g++
CFLAGS=-O0 -g
DEPS = universe.h ant.h infinity_world.h finit_world.h world.h expand.h ant_a.h
OBJ = main.o universe.o ant.o infinity_world.o finit_world.o expand.o ant_a.o

%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

langton_ant: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


run: clean langton_ant
	./langton_ant

clean:
	rm -f *.o langton_ant

clear: clean
