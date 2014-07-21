/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca

Practica Sistemas Operativos: Modulo 2 - Sesion 1
Version:0.1

EJERCICIO 2:
Implementa un programa que acepte como argumento un ''pathname'', abra el
archivo correspondiente y utilizando un tamaño de lectura en bloques de 80 Bytes cree un
archivo de salida en el que debe aparecer lo siguiente:

		Bloque 1
		//los primeros 80 Bytes
		Bloque 2
		//los siguientes 80 Bytes
		...
		Bloque n
		//los siguientes 80 Bytes
*/


#include<sys/types.h>  	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>


int main(int argc, char *argv[]) {
    int i=1;//contador
    int fd1;//descriptor de archivo del primer archivo
    int fd2;//descriptor de archivo del segundo archivo
    int tam=10;
	char aux[27];
    char buf1[80];
    char *name;
    if(argc>=2) {//en name guardamos el pahtname
        name=argv[1];
    }
    if(argc<2) {//si no se le para un pathname, se debe utilizar la entrada estandar para cogerlo
        char name2[20];
		printf("intruduce el pathname: ");
        scanf("%s",name2);
        name=name2;
    }

    if((fd1=open("salida",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {//abrimos y creamos el salida
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(-1);
    }
    if((fd2=open(name,O_RDONLY,S_IRUSR|S_IWUSR))<0) {//abrimos el archivo que se le ha pasado en a name
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(-1);
    }
	//vamos leyendo el archivo name y vamos escribiendo en salida
    while(read(fd2,buf1,80)>0) {//leemos el archivo name en bloques de 80 bytes y lo almacenamos en el vector de char buf1.
        char bloc[tam];
        sprintf(bloc,"\nBloque %d\n",i);//en el vector de char bloc metemos  Bloque i
										//siendo i un numero que va incrementandose en cada iteracion
        if(write(fd1,bloc,tam) ==-1) {//escribimos el vector de char bloc en salida
            perror("\nError en write");
            exit(-1);
        }
        if(write(fd1,buf1,80) ==-1) {//escribimos el vector de char buf1 en salida
            perror("\nError en write");
            exit(-1);
        }
        if(i>=10 && i<100) tam=11;//gestionamos el tamaño del vector de char para que el numero de bloque entre correctamente.
        if(i>=100) tam=12;
        i++;
    }
	
	if(lseek(fd1,0,SEEK_SET)<0){//movemos el puntero a escritura al principio en el archivo salida.
		perror("\nError en lseek");
		exit(-1);
    } 
	
    i--;//decremnetamso  i
    sprintf(aux,"\nEl numerode bloques es %d\n",i);//escribimos en el vector de char aux el nuemero de bloques.
    if(write(fd1,aux,27) <0) {//escribimos el vector de char aux en salida, al principio dle archivo.
    	perror("\nError en write");
        exit(-1);
    }
}
