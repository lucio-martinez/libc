//      main.c
//
//      Copyright 2012 Lucio <lucio@M68MT-S2P>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//
//


#include <stdio.h>
#include <stdlib.h>
#include "pila.h"


void inicPila(struct Pila *p) {
	int *aux;
	aux = (int*)malloc(sizeof(int)*100);
	p->valores=aux;
	p->posTope=-1;
}

void apilar(struct Pila *p, int dato) {
	if (p->posTope==100) exit(1);
	p->valores[++p->posTope]=dato;
}

int pilavacia(struct Pila p) {
	return (p.posTope==-1);
}

void mostrar(struct Pila p) {
	int Limite=p.posTope;
	int j;

	if (pilavacia(p)) exit(1);

	printf("\n");
	for (j=0; j<Limite+1; j++) {
		printf("- - -");
	}
	printf("\n");

	for (j=0; j<Limite+1; j++) {
		printf("| %d |",p.valores[j]);
	}

	printf("\n");
	for (j=0; j<Limite+1; j++) {
		printf("- - -");
	}
	printf("\n");
}

int tope(struct Pila p) {
	if (p.posTope==-1) exit(1);
	return p.valores[p.posTope];
}

void desapilar(struct Pila *p) {
	if (p->posTope==-1)	exit(1);
	int aux = p->valores[--posTope];
	return aux;
}

