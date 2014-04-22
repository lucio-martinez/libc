//
//      Copyright 2012 Lionel Guccione. Todos los derechos reservados
//



#include <stdio.h>
#include <stdlib.h>
typedef struct nodo
{
    char nombre[20];
    int edad;
    struct nodo * siguiente;
} nodo;


//DECLARACION DE FUNCIONES:

//FUNCIONES BASICAS PARA EL MANEJO DE LISTAS:
nodo * inicLista();
nodo * crearNodo(char nombre[20], int edad);
nodo * buscarNodo(char nombre[20], nodo * lista);
nodo * borrarNodo(char nombre[20], nodo * lista);
nodo * agregarPpio(nodo * lista, nodo * nuevoNodo);
nodo * buscarUltimo(nodo * lista);
nodo * agregarFinal(nodo * lista, nodo * nuevoNodo);
nodo * agregarEnOrden(nodo * lista, nodo * nuevoNodo);
nodo * borrarTodaLaLista(nodo * lista);
int sumarEdadesLista(nodo * lista);

//FUNCIONES QUE USAN A LAS FUNCIONES DE LA LISTA, SIRVEN PARA ARMAR EL SISTEMA:

void escribir(nodo * aux);
void recorrerYmostrar(nodo * lista);
nodo * SubprogramaIngresarDatosAlFinal(nodo * lista);
nodo * SubprogramaingresarDatosAlPpio(nodo * lista);
nodo * SubprogramaAgregarUnNodoEnOrden(nodo * lista);
nodo * SubprogramaCrearListaOrdenada(nodo * lista);
void SubprogramaBusquedaDeUnNodo(nodo * lista);
nodo * SubprogramaBorrarNodo(nodo * lista);
void menu();


nodo * inicLista()
{
    return NULL;
}

nodo * crearNodo(char nombre[20], int edad)
{
    nodo * aux = (nodo*)malloc(sizeof(nodo));
    aux->edad = edad;
    strcpy(aux->nombre, nombre);
    aux->siguiente = NULL;
    return aux;
}

nodo * buscarNodo(char nombre[20], nodo * lista)
//busca un nodo por nombre y retorna su posici¢n de memoria
//si no lo encuentra retorna NULL.
{
    nodo * seg;		//apunta al nodo de la lista que est  siendo leido.
    seg = lista;  	//con esto evito cambiar el valor de la variable
    //lista, que contiene un puntero al primer nodo de la
    //lista vinculada
    while ((seg != NULL) && ( strcmp(nombre, seg->nombre)!=0 ))
        //busco mientras me quede lista por recorrer y no haya encontrado el nombre
    {
        seg=seg->siguiente;	//avanzo hacia el siguiente nodo.
    }
    //en este punto puede ha fallado alguna de las dos condiciones del while
    //si fall¢ la primera es debido a que no encontr lo que buscaba (seg es NULL)
    //si fall¢ la segunda es debido a que se encontr¢ el nodo buscado.
    return seg;
}

nodo * borrarNodo(char nombre[20], nodo * lista)
// elimino un nodo de la lista y retorno un puntero al primer elemento de la misma.
// esto ultimo es necesario para el caso en que se elimina el primer elemento de la lista,
// se modifica el contenido de la variable lista, y eso no se puede hacer de la forma en
// que esta declarada. Para poder hacerlo deber¡a poner **lista. :)
{
    nodo * seg;
    nodo * ante;	//apunta al nodo anterior que seg.

    if((lista != NULL) && (strcmp(nombre, lista->nombre)==0 ))
    {
        nodo * aux = lista;
        lista = lista->siguiente; //salteo el primer nodo.
        free(aux); //elimino el primer nodo.
    }
    else
    {
        seg = lista;
        while((seg != NULL) && (strcmp(nombre, seg->nombre)!=0 ))
        {
            ante = seg;	//adelanto una posicion la var ante.
            seg = seg->siguiente; //avanzo al siguiente nodo.
        }
        //en este punto tengo en la variable ante la direccion de memoria del
        //nodo anterior al buscado, y en la variable seg, la dir de memoria del
        //nodo que quiero borrar.
        if( seg!= NULL)
        {
            ante->siguiente = seg->siguiente; //salteo el nodo que quiero eliminar.
            free(seg); //elimino el nodo.
        }
    }
    return lista; //debo retornar el puntero al primer nodo, por el tipo de pasaje de parametros.
    //No puedo modificar el contenido de la var lista, que no es lo mismo
    //que modificar *lista (contenido de la direccion de memoria apuntada
    //por lista.
    //Otra forma de resolverlo es poner el par metro **lista. :)
}

nodo * agregarPpio(nodo * lista, nodo * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

//supongo una lista distinta de NULL.
nodo * buscarUltimo(nodo * lista)
{
    nodo * seg = lista;
    while(seg->siguiente != NULL)
    {
        seg = seg->siguiente;
    }
    return seg;
}

nodo * agregarFinal(nodo * lista, nodo * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodo * ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

nodo * agregarEnOrden(nodo * lista, nodo * nuevoNodo)
// agrega un nuevo nodo a la lista manteniendo el orden.
{
    //Si la lista esta vacia agrego el primer elemento.
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        // si el nuevo elemento es menor que el primero de la lista,
        // agrego al principio.
        if(strcmp(nuevoNodo->nombre,lista->nombre)<0)
            lista = agregarPpio(lista, nuevoNodo);
        else
        {
            // busco el lugar en donde insertar el nuevo elemento.
            // necesito mantener la direccion de memoria del nodo anterior
            // al nodo que tiene un nombre mayor al del nuevo nodo.
            nodo * ante = lista;
            nodo * seg = lista;
            while( (seg != NULL)&&(strcmp(nuevoNodo->nombre,seg->nombre)>0) )
            {
                ante = seg;
                seg = seg->siguiente;
            }
            // inserto el nuevo nodo en el lugar indicado.
            nuevoNodo->siguiente = seg;
            ante->siguiente = nuevoNodo;
        }
    }
    return lista;

}

nodo * borrarTodaLaLista(nodo * lista)
{
    nodo * proximo;
    nodo * seg;
    seg = lista;
    while(seg != NULL)
    {
        proximo = seg->siguiente;//tomo la dir del siguiente.
        free(seg);//borro el actual.
        seg = proximo;//actualizo el actual con la dir del siguiente, para avanzar
    }
    return seg;
}

int sumarEdadesLista(nodo * lista)
//recorro la lista y sumo las edades de los socios.
{
    int suma =  0;
    nodo * seg = lista;
    while (seg != NULL)
    {
        suma = suma + seg->edad;
        seg = seg->siguiente;
    }
    return suma;
}

//FUNCIONES QUE USAN A LAS FUNCIONES DE LA LISTA
//SIRVEN PARA ARMAR EL SISTEMA.

nodo * SubprogramaIngresarNuevoDato()
{
    int edad;
    char nombre[20];
    nodo * nuevoNodo;
    fflush(stdin);
    printf("ingrese nombre: ");
    scanf("%s", nombre);
    fflush(stdin);
    printf("ingrese edad:");
    scanf("%d", &edad);
    nuevoNodo = crearNodo(nombre, edad);
    return nuevoNodo;
}

void escribir(nodo * aux)
{
    printf("nombre: %s \n", aux->nombre);
    printf("edad: %d \n\n", aux->edad);
}


void recorrerYmostrar(nodo * lista)
{
    nodo * seg = lista;
    while (seg != NULL)
    {
        escribir(seg);
        seg= seg->siguiente;
    }
}
nodo * SubprogramaIngresarDatosAlFinal(nodo * lista)
//subprograma para ingresar los datos en una lista en forma de fila, o sea
//al final de la lista.
{
    nodo * nuevoNodo;
    char cont = 's';
    while (cont=='s')
    {
        //pide los datos por pantalla y crea un nuevo nodo.
        nuevoNodo = SubprogramaIngresarNuevoDato();
        // agrega a la fila un nuevo nodo al final.
        lista = agregarFinal(lista, nuevoNodo);
        printf("desea continuar s/n: ");
        fflush(stdin);
        scanf("%c", &cont);
        printf("\n");
    }
    return lista;
}



nodo * SubprogramaingresarDatosAlPpio(nodo * lista)
//subprograma para ingresar los datos en una lista en forma de pila
{
    nodo * nuevoNodo;
    char cont = 's';
    while (cont=='s')
    {
        //pide los datos por pantalla y crea un nuevo nodo.
        nuevoNodo = SubprogramaIngresarNuevoDato();
        // agrega a la fila un nuevo nodo al final.
        lista = agregarPpio(lista, nuevoNodo);
        printf("desea continuar s/n: ");
        fflush(stdin);
        scanf("%c", &cont);
        printf("\n");
    }
    return lista;
}

nodo * SubprogramaAgregarUnNodoEnOrden(nodo * lista)
{

    nodo * nuevoNodo = SubprogramaIngresarNuevoDato();
    lista = agregarEnOrden(lista, nuevoNodo);
    return lista;
}

nodo * SubprogramaCrearListaOrdenada(nodo * lista)
{

    char cont = 's';
    while (cont=='s')
    {
        lista = SubprogramaAgregarUnNodoEnOrden(lista);
        printf("desea continuar s/n: ");
        fflush(stdin);
        scanf("%c", &cont);
        printf("\n");
    }
    return lista;
}

void SubprogramaBusquedaDeUnNodo(nodo * lista)
//subprograma de busqueda y muestra de un nodo
{
    //clrscr();
    char nombre[20];	//nombre a buscar
    nodo * nodoBuscado;	//contiene el nodo encontrado o NULL;
    printf("Ingrese nombre:");
    scanf("%s",nombre);
    printf("\n");
    nodoBuscado = buscarNodo(nombre, lista);
    if(nodoBuscado != NULL)
        escribir(nodoBuscado);
    else
        printf("No se ha encontrado ese nodo\n");
}

nodo * SubprogramaBorrarNodo(nodo * lista)
// pide al usuario un apellido, que es el criterio de busqueda para eliminar
// el nodo. Con este dat, invoca a la funci¢n borrarNodo().
{
    char nombre[20];
    //clrscr();
    printf("ingrese un nombre para eliminarlo de la lista:");
    scanf("%s",nombre);
    lista = borrarNodo(nombre,lista);
    return lista;
}

void menu()
{

    printf("LISTAS VINCULADAS CON PUNTEROS\n\n");
    printf("1: ingresar como pila\n");
    printf("2: ingresar como fila\n");
    printf("3: ingresar como lista ordenada por nombre(muchos nodos)\n");
    printf("4: buscar un nodo\n");
    printf("5: borrar un nodo\n");
    printf("6: insertar un nodo nuevo en orden alfabetico\n");
    printf("7: recorrer la lista\n");
    printf("8: sumar todas las edades de la lista\n");
    printf("\n");
    printf("0: salir\n\n");
}

int main()
{
    nodo * lista;
    int continuar;
    fflush(stdin);
    scanf("%i", &continuar);
    lista = inicLista();
    do
    {
        menu();
        fflush(stdin);
        printf("ingrese opcion:");
        scanf("%i", &continuar);
        printf("\n");
        switch(continuar)
        {
        case 1:
            lista = SubprogramaingresarDatosAlPpio(lista);
            break;
        case 7:
            recorrerYmostrar(lista);
            break;
        case 4:
            SubprogramaBusquedaDeUnNodo(lista);
            break;
        case 5:
            lista = SubprogramaBorrarNodo(lista);
            break;
        case 2:
            lista = SubprogramaIngresarDatosAlFinal(lista);
            break;
        case 3:
            lista = borrarTodaLaLista(lista);
            lista = SubprogramaCrearListaOrdenada(lista);
            break;
        case 6:
            lista = SubprogramaAgregarUnNodoEnOrden(lista);
            break;
        case 8:
        {
            int suma = sumarEdadesLista(lista);
            printf("suma de edades : %d \n",suma);
            //fflush(stdin);
            //getch();
            break;
        }
        }
        if(continuar!=0)
        {
            printf("\npresione cualquier tecla para continuar\n");
            fflush(stdin);
            scanf("%i", &continuar);
        }
    }
    while(continuar!=0);
    fflush(stdin);
    scanf("%i", &continuar);
    return 0;
}

