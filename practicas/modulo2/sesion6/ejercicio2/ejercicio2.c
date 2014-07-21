/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca

Practica Sistemas Operativos: Modulo 2 - Sesion 6
Version:0.1

EJERCICIO 2
Reescribir el programa que implemente un encauzamiento de dos órdenes pero
utilizando fcntl. Este programa admitirá tres argumentos. El primer argumento y el tercero
serán dos órdenes de Linux. El segundo argumento será el carácter “|”. El programa deberá
ahora hacer la redirección de la salida de la orden indicada por el primer argumento hacia el
cauce, y redireccionar la entrada estándar de la segunda orden desde el cauce.
Por ejemplo, para simular el encauzamiento ls|sort, ejecutaríamos nuestro programa como:
$ ./mi_programa2 ls “|” sort


Programa ilustrativo del uso de pipes y la redirección de entrada y
salida estándar.
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t PID;
    if (argc<4) {//comprobamos los argumentos
        printf("Error falta de argumentos\n");
    }
    pipe(fd); // Llamada al sistema para crear un pipe

	//Creamos un hijo
    if ( (PID= fork())<0) {
        perror("fork");
        exit(1);
    }
    if (PID == 0) {//en la ejecucion del hijo
		//Establecer la dirección del flujo de datos en el cauce cerrando
        // el descriptor de escritura en el cauce del proceso padre.
        close(fd[0]);
		//Redirigir la salida estándar para tomar los datos del cauce.
    	//Cerrar la salida estándar del proceso hijo
        close(STDOUT_FILENO);

		//hacemos la redireccion hacia el archivo.
        if(fcntl(fd[1],T_DUPFD,STDOUT_FILENO)==-1) {
            perror("error fcntl");
            exit(-1);
        }
        execlp(argv[1],argv[1],NULL);//ejecutamos el primer subprograma, del argumento 1
		//de esta maner lo que saldria por pantalla se escribira en fd[1](cauce)
    }
    else {
		//Establecer la dirección del flujo de datos en el cauce cerrando
        // el descriptor de escritura en el cauce del proceso padre.
        close(fd[1]);
		//Redirigir la entrada estándar para tomar los datos del cauce.
   		//Cerrar la entrada estándar del proceso padre
        close(STDIN_FILENO);
	
		//hacemos la redireccion hacia el archivo.
        if(fcntl(fd[0],STDIN_FILENO)==-1) {
            error("error fcntl");
            exit(-1);
        }
        execlp(argv[2],argv[2],NULL);//ejecutamos el segundo subprograma, del argumento 2
		//de esta maner lo que toma lo cogeria del cauce en fd[0]
    }

    return(0);
}


