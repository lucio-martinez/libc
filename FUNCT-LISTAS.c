#include <stdio.h>
#include <stdlib.h>


typedef struct str{
    int dato;
    struct str * ste;
}nodo;


void iniclista(nodo ** lista){
    *lista=NULL;
}

nodo * CrearNodo(int N){
    nodo * Nuevo=(nodo*)malloc(sizeof(nodo));
    Nuevo->dato=N;
    Nuevo->ste=NULL;
    return Nuevo;
}

void AgregarPri(nodo ** lista, nodo * NuevoNodo){
    if (*lista==NULL) {
        *lista=NuevoNodo;
    } else {
        NuevoNodo->ste=*lista;
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

void AgregarFin(nodo ** lista, nodo * NuevoNodo){
    if (*lista==NULL) {
        *lista=NuevoNodo;
    } else {
        nodo * Ultimo=UltimoNodo(*lista);
        Ultimo->ste=NuevoNodo;
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

int CantidadNodos(nodo * lista) {
    int Cant=0;
    while (lista!=NULL) {
        Cant++;
        lista=lista->ste;
    }
    return Cant;
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
            *lista=NuevoNodo;
        } else {
            while (Actual!=NULL && Actual->dato<NUM) {
                Anterior=Actual;
                Actual=Actual->ste;
            }
            Anterior->ste=NuevoNodo;
            NuevoNodo->ste=Actual;
        }
    }
}

int Buscar(nodo * lista, int Dato){
    while (lista->ste!=NULL && lista->dato!=Dato) {
        lista=lista->ste;
    }
    if (lista->dato==Dato) {
        return 1;
    } else return 0;
}


void Insercion(nodo ** lista){
    nodo * NuevaLista=NULL;
    nodo * aux=NULL;
    while (*lista!=NULL){
        aux=*lista;
        *lista=(*lista)->ste;
        aux->ste=NULL;
        AgregarOrd(&NuevaLista,aux);
    }
    *lista=NuevaLista;
}


nodo * Intercalar(nodo * L1, nodo * L2){
    nodo * NuevaLista=NULL;
    nodo * aux=NULL;
    while (L1!=NULL && L2!=NULL) {
        if (L1->dato < L2->dato) {
            aux=L1;
            L1=L1->ste;
            aux->ste=NULL;
            AgregarFin(&NuevaLista,aux);
        } else {
            aux=L2;
            L2=L2->ste;
            aux->ste=NULL;
            AgregarFin(&NuevaLista,aux);
        }
    }
    while (L2!=NULL) {
        aux=L2;
        L2=L2->ste;
        aux->ste=NULL;
        AgregarOrd(&NuevaLista,aux);
    }
    while (L1!=NULL) {
        aux=L1;
        L1=L1->ste;
        aux->ste=NULL;
        AgregarOrd(&NuevaLista,aux);
    }
    return NuevaLista;
}


nodo * AgregarAlFinal(nodo * lista, nodo * NuevoNodo){
    if (lista==NULL) {
        lista=NuevoNodo;
    } else {
        nodo * Ultimo=UltimoNodo(lista);
        Ultimo->ste=NuevoNodo;
    }
    return  lista;
}

nodo * ExtraerUltimo(nodo ** lista){
    nodo * Anterior=NULL;
    nodo * Seguido=*lista;
    if ((*lista)==NULL || (*lista)->ste==NULL){
        *lista=NULL;
    } else{
        while (Seguido->ste!=NULL) {
            Anterior=Seguido;
            Seguido=Seguido->ste;
        }
        Anterior->ste=NULL;
    }
    return Seguido;
}

nodo * Invertir(nodo * lista){
    nodo * NuevaLista=NULL;
    nodo * Ultimo=NULL;
    while (lista!=NULL){
        Ultimo=ExtraerUltimo(&lista);
        AgregarFin(&NuevaLista,Ultimo);
    }
    return NuevaLista;
}


nodo * BorrarNodo(nodo * lista, int N){
    if (lista!=NULL) {
        if (lista->dato==N){
            nodo * aux=lista;
            lista=lista->ste;
            free(aux);
        } else{
            nodo * ante=lista;
            nodo * seg=lista;
            while (seg!=NULL && seg->dato!=N) {
                ante=seg;
                seg=seg->ste;
            }
            if (seg!=NULL) {
                ante->ste=seg->ste;
                seg->ste=NULL;
            }
        }
    }
    return lista;
}

