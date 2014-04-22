#include <stdio.h>
#include <stdlib.h>

struct str{
    int dato;
    struct str * ste;
};
typedef struct str nodo;

void InicLista(nodo ** lista){
    *lista=NULL;
}

nodo * CrearNodo(int N){
    nodo * NuevoNodo=NULL;
    NuevoNodo=(nodo*)malloc(sizeof(nodo));
    NuevoNodo->dato=N;
    NuevoNodo->ste=NULL;
    return NuevoNodo;
}

void Mostrar(nodo * lista){
    if (lista!=NULL) {
        printf("| %d |",lista->dato);
        Mostrar(lista->ste);
    }
}

int ListaVacia(nodo * lista){
    if (lista==NULL) return 1;
    else return 0;
}

int Tope(nodo * lista){
    if (lista!=NULL) {
        return lista->dato;
    }
}

int Desapilar(nodo ** lista){
    if (*lista!=NULL) {
        nodo * aux=*lista;
        *lista=(*lista)->ste;
        aux->ste=NULL;
        int N=aux->dato;
        free(aux);
        return N;
    }
}

void AgregarPri(nodo ** lista, nodo * NuevoNodo){
    if (*lista==NULL) {
        *lista=NuevoNodo;
    } else {
        NuevoNodo->ste=*lista;
        *lista=NuevoNodo;
    }
}


void Apilar(nodo ** lista, int N){
    if (*lista==NULL) {
        *lista=(nodo*)malloc(sizeof(nodo));
        (*lista)->dato=N;
        (*lista)->ste=NULL;
    } else {
        nodo * NuevoNodo=CrearNodo(N);
        AgregarPri(lista,NuevoNodo);
    }
}


int main()
{
    nodo * lista;
    
    InicLista(&lista);
    printf("\nPILAVACIA: %d\n",ListaVacia(lista));
    Apilar(&lista,5);
    Mostrar(lista);
    Desapilar(&lista);
    printf("\nPILAVACIA: %d\n",ListaVacia(lista));
    printf("TOPE: %d",Tope(lista));
    
    return 0;
}
