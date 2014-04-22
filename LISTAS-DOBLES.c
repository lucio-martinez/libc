//      main.c
//
//      Copyright 2012, 2014 Lucio <luciomartinez at openmailbox dot org>
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


typedef struct str{
	int dato;
	struct str * ante;
	struct str * ste;
}nodo;

void iniclista(nodo ** lista){
    *lista=NULL;
}

nodo * CrearNodo(int N){
    nodo * Nuevo=(nodo*)malloc(sizeof(nodo));
    Nuevo->dato=N;
    Nuevo->ste=NULL;
    Nuevo->ante=NULL;
    return Nuevo;
}

void AgregarPri(nodo ** lista, nodo * NuevoNodo){
    if (*lista==NULL) {
        *lista=NuevoNodo;
    } else {
        NuevoNodo->ste=*lista;
        (*lista)->ante=NuevoNodo;
        *lista=NuevoNodo;
    }
}


nodo * UltimoNodo(nodo * lista){
    if (lista!=NULL) {
        while (lista->ste!=NULL){
            lista=lista->ste;
        }
    }
    return lista;
}

nodo * UltimoNodoRec(nodo * lista){
    nodo * Rta=lista;
    if (lista!=NULL && lista->ste!=NULL) {
        Rta = UltimoNodo(lista->ste);
    }
    return Rta;
}


void AgregarFin(nodo ** lista, nodo * NuevoNodo){
    if (*lista==NULL) {
        *lista=NuevoNodo;
    } else {
        nodo * Ultimo=UltimoNodo(*lista);
        Ultimo->ste=NuevoNodo;
        NuevoNodo->ante=Ultimo;
    }
}

void Mostrar(nodo * lista){
    if (lista==NULL){
        printf("\nLISTA VACIA!\n");
    } else {
        printf("\n");
        while (lista!=NULL) {
            printf("| %d |",lista->dato);
            lista=lista->ste;
        }
        printf("\n");
    }
}

void AgregarOrd(nodo ** lista, nodo * NuevoNodo){
    nodo * Anterior=*lista;
    nodo * Actual=*lista;
    int NUM=NuevoNodo->dato;

    if (*lista==NULL) {
        *lista=NuevoNodo;
    } else {
        if (NUM < (*lista)->dato) {
            NuevoNodo->ste=*lista;
            (*lista)->ante=NuevoNodo->ante;
            *lista=NuevoNodo;
        } else {
            while (Actual!=NULL && Actual->dato<NUM) {
                Anterior=Actual;
                Actual=Actual->ste;
            }
            Anterior->ste=NuevoNodo;
            NuevoNodo->ante=Anterior;
            NuevoNodo->ste=Actual;
            if (Actual!=NULL) Actual->ante=NuevoNodo;
        }
    }
}

void Insercion(nodo ** lista){
    nodo * NuevaLista=NULL;
    nodo * aux=NULL;
    while (*lista!=NULL){
        aux=*lista;
        *lista=(*lista)->ste;
        aux->ante=NULL;
        aux->ste=NULL;
        AgregarOrd(&NuevaLista,aux);
    }
    *lista=NuevaLista;
}



nodo * ExtraerUltimo(nodo ** lista){
    nodo * Ultimo=UltimoNodo(*lista);
    if (Ultimo!=NULL){
        if (Ultimo->ante != NULL) {
            nodo * aux=Ultimo->ante;
            aux->ste=NULL;
        }
        Ultimo->ante=NULL;
    }
    return Ultimo;
}

void MostrarInv(nodo * lista){
    lista=UltimoNodo(lista);
    printf("\n");
    while (lista!=NULL){
        printf("| %d |",lista->dato);
        lista=lista->ante;
    }printf("\n\n");
}

nodo * CrearLista(){
	int res=1, aux;
	nodo * NuevaLista;
	iniclista(&NuevaLista);
	
	while (res==1){
		system("cls");
		printf("Ingrese un numero -> ");
		scanf("%d",&aux);
		nodo * Nuevo = CrearNodo(aux);
		AgregarFin(&NuevaLista,Nuevo);
		
		printf("Si desea agregar otro numero ingrese UNO (1) -> ");
		scanf("%d",&res);
	}
	return NuevaLista;	
}

//Si retorna 1: la lista es capicua
int RetornoCapicua(nodo * primero, nodo * ultimo){
	int Res=0;
	if (primero!=ultimo && ultimo->ste!=primero) {
		if (primero->dato == ultimo->dato) {
			Res = RetornoCapicua(primero->ste,ultimo->ante);
		}
	} else {
		Res=1;
	}	
	return Res;
}

void Capicua(nodo * lista) {
	if (lista!=NULL) {
		nodo * ultimo = UltimoNodo(lista);
		if (RetornoCapicua(lista,ultimo) == 1) {
			printf("\nLa lista es capicua!\n");
		} else {
			printf("\nLa lista NO es capicua!\n");
		}
	}
}

