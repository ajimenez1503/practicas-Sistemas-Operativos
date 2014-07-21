/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca

Practica Sistemas Operativos: Modulo 2 - Sesion 4
Version:0.1

EJERCICIO 5-PRIMOS
El programa esclavo tiene como argumentos el extremo inferior y superior del
intervalo sobre el que buscará números primos. Para identificar un número primo
utiliza el siguiente método concreto: un número n es primo si no es divisible por
ningún k tal que 2 < k < sqrt(n), donde sqrt corresponde a la función de cálculo de la
raíz cuadrada (consulte dicha función en el manual). El esclavo envía al maestro cada
primo encontrado como un dato entero (4 bytes) que escribe en la salida estándar, la
cuál se tiene que encontrar redireccionada a un cauce sin nombre. Los dos cauces sin
nombre necesarios, cada uno para comunicar cada esclavo con el maestro, los creará
el maestro inicialmente. Una vez que un esclavo haya calculado y enviado (uno a uno)
al maestro todos los primos en su correspondiente intervalo terminará.


compilar:
gcc primos.c -o primo
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>
int es_primo(int x) {
    int b=1;
    int c;
    for(c=2; c<x && b==1; c+=2) {
        if(x%c==0) b=0;
    }
    return b;
}


int main(int argc, char *argv[]) {
    int min,max;
    if(argc>1) {//si los argumentos son correctos
        int i;
        min=strtol(argv[1],NULL,10);//min es el primer argumento
        max=strtol(argv[2],NULL,10);//max es el segundo argumento

        for(i=min; i<=max; i++) {//devuelve los numeros primos entre el intervalo de [min,max]
            if(es_primo(i)==1) {
                printf("%d\n",i);
            }
        }
    }
    else{//si los argumentos no son correctos
		printf("faltan argumentos");
	    exit(0);
	}
	return 0;
}
