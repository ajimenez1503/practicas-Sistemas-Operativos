/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca

Practica Sistemas Operativos: Modulo 2 - Sesion 3
Version:0.1

EJERCICIO 6:
Escribe un programa que acepte como argumentos el nombre de un programa,
sus argumentos si los tiene, y opcionalmente la cadena “bg”. Nuesto programa deberá
ejecutar el programa pasado como primer argumento en foreground si no se especifica la
cadena “bg” y en background en caso contrario. Si el programa tiene argumentos hay que
ejecutarlo con éstos.

Ejemplo de ejecucion:
./a.out ls -la /home/antonio/Escritorio/Sesion3 
*/

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int numarg,isbg=0,i,estado;
    char *direccion;
    if(argc<2){//salimos de la ejecucion si no tiene argumentos
	printf("Error faltan argumentos\n");
	exit(-1);
    }
    direccion=argv[1];
    if(!strcmp(argv[argc-1],"bg")) {//comprobamos si el ultimo argumento es "bg"
        numarg=argc-2;
        isbg=1;//esta en BG
    }
    else {
        numarg=argc-1;
        isbg=0;//no esta en BG
    }

	//creamos la cadena de ejecucion del subprograma en argv2
    char *argv2[numarg];
    for(i=0; i<numarg-1; i++){
        argv2[i]=argv[i+2];// le mtemos tmabn argv[1];
    }
    argv2[numarg-1]= (char *)NULL;//le ponemos null al final
	//creamos la cadena de ejecucion del subprograma en argv2
    sleep(1);
    if(isbg==0) {//si no estamso en BG
        if((execvp(direccion,argv2))<0) {//lanzamos el subprograma
            perror("\nError en el execv");
            exit(-1);
        }
    }
    else {//si estamso en BG
        if((pid=fork())<0) {//creamos un hijo
            perror("\nError en el fork");
            exit(-1);
        }
        else if(pid==0) {//el hijo lanza el subprograma
            if((execvp(direccion,argv2))<0) {
                perror("\nError en el execv");
                exit(-1);
            }
        }
        printf("Identificador de proceso: %d\n",pid);//mostramos el identificador del proceso del hijo
    }
    exit(0);
}
