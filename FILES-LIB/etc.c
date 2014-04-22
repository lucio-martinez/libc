
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

nodo * CargarLista(int vec[], int Tope){
    nodo * Lista=NULL;
    nodo * NuevoNodo=NULL;
    int j;
    for (j=0; j<Tope; j++){
        NuevoNodo=CrearNodo(vec[j]);
        //AgregarPri(&Lista,NuevoNodo);
        AgregarFin(&Lista,NuevoNodo);
    }
    return Lista;
}


void Guardar(char dir[], nodo *lista){
    int N=0;
    FILE *arc=fopen(dir,"wb");
    while (lista!=NULL) {
        N=lista->dato;
        fwrite(&N,sizeof(int),1,arc);
        lista=lista->ste;
    }
    fclose(arc);
}


void GenerarArchivos(char dir[], char dirDos[], nodo * lista,
                        nodo * listaDos){
    int vec[]={5,0,9,3,5};
    int vec2[]={6,3,1,4};
    lista=CargarLista(vec,5);
    listaDos=CargarLista(vec2,4);
    Guardar(dir,lista);
    Guardar(dirDos,listaDos);
}

nodo * Leer(char dir[]){
    nodo * Lista=NULL;
    nodo * NuevoNodo=NULL;
    int num=0;
    FILE *arc=fopen(dir,"rb");
    while (fread(&num,sizeof(int),1,arc)>0) {
        NuevoNodo=CrearNodo(num);
        AgregarPri(&Lista,NuevoNodo);
        //AgregarOrd(&Lista,NuevoNodo);
    }
    fclose(arc);
    return Lista;
}



int main(int argc, char *argv[])
{
    char dir[]="archivo.bin";
    char dirDos[]="archivoDos.bin";
    nodo * lista,*listaDos;
    iniclista(&lista);
    iniclista(&listaDos);

	GenerarArchivos(dir,dirDos,lista,listaDos);

    lista=Leer(dir);
    listaDos=Leer(dirDos);

    return 0;
}

