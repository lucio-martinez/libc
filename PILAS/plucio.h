#include <stdlib.h>
#include <stdio.h>

#define Pila S_Pila

struct S_Pila
{
	int *valores;
	int posTope;
};

void inicPila(struct Pila *p);
void apilar(struct Pila *p, int dato);
int pilavacia(struct Pila p);
void mostrar(struct Pila p);
int tope(struct Pila p);
void desapilar(struct Pila *p);
