nodo * IntercalarRec(nodo *L1, nodo *L2){
    nodo * NuevaLista=NULL;

    if (L1!=NULL && L2!=NULL) {
        if (L1->dato < L2->dato) {
            NuevaLista=L1;
            L1=L1->ste;
            NuevaLista->ste=NULL;
            NuevaLista->ste=IntercalarRec(L1,L2);
            return NuevaLista;
        } else {
            NuevaLista=L2;
            L2=L2->ste;
            NuevaLista->ste=NULL;
            NuevaLista->ste=IntercalarRec(L1,L2);
            return NuevaLista;
        }
    } else {
        if (L1!=NULL) {
            NuevaLista=L1;
            return NuevaLista;
        } else {
            NuevaLista=L2;
            return NuevaLista;
        }
    }
}


nodo * BorrarNodoRec(nodo * lista, int N){
    nodo * rta=lista;
    if (lista!=NULL) {
        if (lista->dato==N) {
            nodo * aux=lista;
            rta=rta->ste;
            free(aux);
        } else {
            rta->ste=BorrarNodoRec(lista->ste,N);
        }
    }
    return rta;
}



nodo * InvertirRec(nodo * lista){
    nodo * rta=NULL;
    nodo * Anterior=NULL;
    nodo * Actual=NULL;
    if (lista!=NULL) {
        Actual=lista;
        Anterior=Actual->ste;
        Actual->ste=NULL;
        rta=AgregarAlFinal(InvertirRec(Anterior),Actual);
    }
    return rta;
}

void MostrarPar(nodo * lista){
    if (lista!=NULL) {
        printf("| %d |",lista->dato);
        lista=lista->ste;
        if (lista!=NULL) MostrarPar(lista->ste);
    }
}


/*
nodo * Insercion(nodo * lista){
    nodo * NuevaLista=lista;
    nodo * aux=NULL;
    if (lista!=NULL) {
        aux=lista;
        lista=lista->ste;
        aux->ste=NULL;
        free(aux);
        NuevaLista->ste=Insercion(AgregarOrd(&NuevaLista,aux));
    }
    return NuevaLista;
}
*/
