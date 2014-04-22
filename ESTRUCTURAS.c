//      source.c Creado en Agosto del 2012
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


struct alu{
	int legajo;
	char nombre[30];
	int sexo;
};


void mostrar(int x,struct alu RegAlumnos[]) {
	int j;
	system("clear");
	for (j=0; j<x; j++) {
		printf("\n\nALUMNO N %d\n",1+j);

		printf("Legajo del alumno --> %d",RegAlumnos[j].legajo);
		printf("\nNombre del alumno --> %s",RegAlumnos[j].nombre);
		printf("\nSexo del alumno (0=M 1=F) --> %d",RegAlumnos[j].sexo);
	}
}


int FCargar(struct alu RegAlumnos[]) {
	int j,x;

	printf("Ingrese la cantidad de alumnos --> ");
	fflush(stdin);
	scanf("%d",&x);

	for (j=0; j<x; j++) {
		system("clear");
		printf("ALUMNO N %d\n",1+j);

		printf("Ingrese el legajo del alumno --> ");
		fflush(stdin);
		scanf("%d",&RegAlumnos[j].legajo);

		printf("\nIngrese el nombre del alumno --> ");
		fflush(stdin);
		scanf("%s",RegAlumnos[j].nombre);

		printf("\nIngrese el sexo del alumno (0=M 1=F) --> ");
		fflush(stdin);
		scanf("%d",&RegAlumnos[j].sexo);
	}

	return x;
}

//Intercambia los datos en Struct[X] con Struct[Y]
void FIntercambio(struct alu RegAlumnos[],int X,int Y) {
	int Naux; char Caux[30];

	Naux=RegAlumnos[X].legajo;
	RegAlumnos[X].legajo=RegAlumnos[Y].legajo;
	RegAlumnos[Y].legajo=Naux;

	strcpy(Caux,RegAlumnos[X].nombre);
	strcpy(RegAlumnos[X].nombre,RegAlumnos[Y].nombre);
	strcpy(RegAlumnos[Y].nombre,Caux);

	Naux=RegAlumnos[X].sexo;
	RegAlumnos[X].sexo=RegAlumnos[Y].sexo;
	RegAlumnos[Y].sexo=Naux;
}
int FMenor(struct alu RegAlumnos[],int Limite,int Posicion) {
	int PosMenor=Posicion,j;
	//int Menor=RegAlumnos[Posicion].legajo;
	char Menor[32];
	strcpy(Menor,RegAlumnos[Posicion].nombre);

	for (j=Posicion+1; j<Limite; j++) {
		if (RegAlumnos[j].nombre<Menor) {
		    printf("HOLA");
			//Menor=RegAlumnos[j].legajo;
			strcpy(Menor,RegAlumnos[j].nombre);
			PosMenor=j;
		}
	}

	return PosMenor;
}
void FOrdenSelec(struct alu RegAlumnos[],int Limite) {
	int PosMenor=0,j;

	for (j=0; j<Limite-1; j++) {
		PosMenor=FMenor(RegAlumnos,Limite,j);

		if (PosMenor!=j) FIntercambio(RegAlumnos,j,PosMenor);
	}
}

void FGuardar(struct alu RegAlumnos[],char dir[],int Cant) {
	FILE *arc;

	if ((arc=fopen(dir,"wb"))==NULL) {
		printf("ERROR al abrir archivo %s en modo WB.",dir);
		exit(1);
	}

	if (fwrite(RegAlumnos,sizeof(struct alu),Cant,arc)==Cant)
		printf("Los datos se han escrito correctamente en el archivo %s.",dir);
	fclose(arc);
}

void FLeer(struct alu RegAlumnos[],char dir[],int Cant) {
	FILE *arc;

	if ((arc=fopen(dir,"rb"))==NULL) {
		printf("ERROR al abrir archivo %s en modo RB.",dir);
		exit(1);
	}

	fread(RegAlumnos,sizeof(struct alu),Cant,arc);
	fclose(arc);
}



//Intercambia los datos en Struct[X] con Struct[Y]
void FIntercambioDirecta(FILE *arc,int X,int Y) {
	struct alu RegAlumnos[2];

	fseek(arc,X*sizeof(struct alu),SEEK_SET);
	fread(&RegAlumnos[0],sizeof(struct alu),1,arc);

	fseek(arc,Y*sizeof(struct alu),SEEK_SET);
	fread(&RegAlumnos[1],sizeof(struct alu),1,arc);

	fseek(arc,X*sizeof(struct alu),SEEK_SET);
	fwrite(&RegAlumnos[1],sizeof(struct alu),1,arc);

	fseek(arc,Y*sizeof(struct alu),SEEK_SET);
	fwrite(&RegAlumnos[0],sizeof(struct alu),1,arc);
}
int FMenorDirecta(FILE *arc,int Limite,int Posicion) {
	int PosMenor=Posicion,j;
	int Menor,Numero;
	//Se toma el primer numero para comparar
	fseek(arc,Posicion*sizeof(struct alu),SEEK_SET);
	fread(&Menor,sizeof(int),1,arc);

	for (j=Posicion+1; j<Limite; j++) {
		fseek(arc,j*sizeof(struct alu),SEEK_SET);
		fread(&Numero,sizeof(int),1,arc);

		if (Numero<Menor) {
			Menor=Numero;
			PosMenor=j;
		}
	}

	return PosMenor;
}
void FOrdenSelecDirecta(char dir[],int Limite) {
	int PosMenor,j;
	FILE *arc;

	if ((arc=fopen(dir,"r+b"))==NULL) {
		printf("ERROR al abrir el archivo %s en modo RB.",dir);
		exit(1);
	}

	for (j=0; j<Limite-1; j++) {
		PosMenor=FMenorDirecta(arc,Limite,j);

		if (PosMenor!=j) FIntercambioDirecta(arc,j,PosMenor);
	}

	fclose(arc);
}


//Agrega 1 dato al fin del archivo
void fagreg_dat(char dir[],int N) {
	FILE *arc;

	if ((arc=fopen(dir,"a+b"))==NULL) {
		printf("NO se pudo abrir el archivo para agregar el dato.");
		exit(1);
	}

	if (fwrite(&N,sizeof(int),1,arc) != 1) printf("NO se pudo escribir el dato.");
	fclose(arc);
}


//Cantidad de struct alumno
int fcant_strc(char dir[]) {
	int x=0;
	FILE *arc;

	if ((arc=fopen(dir,"rb"))==NULL) {
		printf("NO se pudo abrir el archivo.");
		exit(1);
	}

	fseek(arc,0,SEEK_END);
	x=(ftell(arc)/sizeof(struct alumno));

	fclose(arc);

	return x;
}


//Retorna la cantidad de mayores
int fcant_mays(char dir[]) {
	int x=0;
	struct alumno A;

	FILE *arc;

	if ((arc=fopen(dir,"rb"))==NULL) {
		printf("NO se pudo abrir el archivo.");
		exit(1);
	}

	while (fread(&A,sizeof(struct alumno),1,arc)>0) {
		if (A.edad>17) x++;
	}
	fclose(arc);

	return x;
}



int FBusqueda(char dir[],char Alumno[]) {
	char Dato[30];
	struct alu A;
	int x=0;
	FILE *arc;

	if ((arc=fopen(dir,"r+b"))==NULL) {
		printf("ERROR al abrir el archivo %s en modo RB.",dir);
		exit(1);
	}

	fseek(arc,sizeof(int),SEEK_SET);

	while (fread(&Dato,sizeof(char[30]),1,arc)>0) {
		printf("%s and %s.",Alumno,Dato);
		x++;
		if (strcmp(&Dato,Alumno)==0) return 1;
		//fseek(arc,x*sizeof(struct alu)+sizeof(int),SEEK_SET);
		fseek(arc,2*sizeof(int)+sizeof(char[2]),SEEK_CUR);
	}
	/*while (fread(&A,sizeof(struct alu),1,arc)>0)
	    if (strcmp(A.nombre,Alumno)==0) return 1;*/


	return 0;
}


//Muestra los nombre
void fimp_ns_mays(char dir[]) {
	struct alumno A;

	FILE *arc;
	if ((arc=fopen(dir,"rb"))==NULL) {
		printf("NO se pudo abrir el archivo.");
		exit(1);
	}

	while (fread(&A,sizeof(struct alumno),1,arc)>0) {
		if (16<A.edad && A.edad<26) printf("%s",A.nombre);
	}
	fclose(arc);
}



//Muestra el nombre del mayor
void fimp_n_may(char dir[]) {
	struct alumno A;
	char n_may[30]="asdf";
	int may;

	FILE *arc;
	if ((arc=fopen(dir,"rb"))==NULL) {
		printf("NO se pudo abrir el archivo.");
		exit(1);
	}

	if (fread(&A,sizeof(struct alumno),1,arc)!=1) {
		printf("El archivo esta vacio.");
		exit(1);
	}

	may=A.edad;
	//strcpy(n_may,A.nombre);

	while (fread(&A,sizeof(struct alumno),1,arc)>0) {
		if (may<A.edad) {
			may=A.edad;
			//strcpy(n_may,A.nombre);
		}
	}

	printf("\n\n%s",n_may);
	fclose(arc);
}


//Ir a la registro N y mostrarlo
void fgo_reg(char dir[],int N) {
	struct alumno A;
	FILE *arc;

	if ((arc=fopen(dir,"rb"))==NULL) {
		printf("NO se pudo abrir el archivo.");
		exit(1);
	}

	fseek(arc,N*sizeof(struct alumno),SEEK_SET);

	if (fread(&A,sizeof(struct alumno),1,arc)!=1) {
		printf("ERROR al leer estructura.");
		exit(1);
	}

	printf("\n\nRegistro N%d:",N+1);
	printf("\nLegajo.. %d",A.legajo);
	printf("\nEdad.. %d",A.edad);
	printf("\nNombre.. %s",A.nombre);

	fclose(arc);
}



//Intercambia primero por último
void finver_strc(char dir[]) {
	struct alumno A,B;
	int beg=0,limit=0;

	//LIMIT es la mitad (-1 si impar) del total de estr.
	limit=fcant_strc(dir)/2;

	FILE *arc;
	if ((arc=fopen(dir,"r+b"))==NULL) {
		printf("NO se pudo abrir para lecto/escritura el archivo.");
		exit(1);
	}

	while (beg<limit) {
		fseek(arc,beg*sizeof(struct alumno),SEEK_SET);
		fread(&A,sizeof(struct alumno),1,arc);
		fseek(arc,(beg+1)*-1*sizeof(struct alumno),SEEK_END);
		fread(&B,sizeof(struct alumno),1,arc);

		fseek(arc,beg*sizeof(struct alumno),SEEK_SET);
		fwrite(&B,sizeof(struct alumno),1,arc);
		fseek(arc,(beg+1)*-1*sizeof(struct alumno),SEEK_END);
		fwrite(&A,sizeof(struct alumno),1,arc);

		beg++;
	}
	fclose(arc);
}


int main(int argc, char **argv)
{
	char dir[]="archivo.bin";
	struct alu RegAlumnos[50];
	int Cant=3;

	//Devuelve la cantidad de alumnos ingresados
	//Cant=FCargar(RegAlumnos);

	//FOrdenSelec(RegAlumnos,Cant);  //Ordena la estructura

	//FGuardar(RegAlumnos,dir,Cant);

	//FOrdenSelecDirecta(dir,Cant);  //Ordena el archivo

	//FLeer(RegAlumnos,dir,Cant);

	//mostrar(Cant,RegAlumnos);


	//n=fcant_strc(dir);
	//printf("PRIMERO ->%dK ",n);

	//n=fcant_mays(dir);
	//printf("\n\n%d",n);

	//fimpr_ns_mays(dir);

	//fimpr_n_may(dir);

	//fgoto_strc(dir,n);

	//finver_strc(dir);


	printf("%d",FBusqueda(dir,"tres"));

	return 0;
}

