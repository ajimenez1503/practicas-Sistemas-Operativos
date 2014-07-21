/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca

Practica Sistemas Operativos: Modulo 2 - Sesion 3
Version:0.1

EJERCICIO 1:
Implementa un programa en C que tenga como argumento un número entero.
Este programa debe crear un proceso hijo que se encargará de comprobar si dicho número es
un número par o impar e informará al usuario con un mensaje que se enviará por la salida
estándar. 
A su vez, el proceso padre comprobará si dicho número es divisible por 4,
e informará si lo es o no usando igualmente la salida estándar.

*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    int a;
    pid_t pid;
    if (argc!=2) {//comprobamos el numero de argumetos
        printf("error en los argumentos");
        exit(-1);
    }
    a=strtol(argv[1],NULL,10);//convertimos el argumento a un numero en decimal
    printf("el numero es %d\n",a);//mostrmaos el numero por pantalla
    if ((pid=fork())<0) {//creamos otra hebra
        perror("\nError en el fork");
        exit(-1);
    }
    else if (pid==0) { //proceso hijo ejecutando el programa
        if (a%2==0) printf("Es divisible entre 2\n");
        else printf("No es divisible entre 2\n");
    }
    else {   //proceso padre ejecutando el programa
	sleep(1);//hacemso sleep para apreciar la ejecucuon del padre y del hijo
        if (a%4==0) printf("Es divisible entre 4\n");
        else printf("No es divisible entre 4\n");
    }
    return 0;
}
