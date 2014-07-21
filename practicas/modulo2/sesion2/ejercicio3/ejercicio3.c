/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca

Practica Sistemas Operativos: Modulo 2 - Sesion 2
Version:0.1

EJERCICIO 3:
Programa una nueva orden que recorra la jerarquía de subdirectorios
existentes a partir de uno dado como argumento y devuelva la cuenta de todos aquellos
archivos regulares que tengan permiso de ejecución para el grupo y para otros. 
Además del nombre de los archivos encontrados, deberá devolver sus números de inodo y la suma total de
espacio ocupado por dichos archivos.

El formato de la nueva orden será:
$ ./buscar <pathname>

donde <pathname> especifica la ruta del directorio a partir del cual queremos que empiece a
analizar la estructura del árbol de subdirectorios.
En caso de que no se le de argumento,tomará como punto de partida el directorio actual. 
Ejemplo de la salida después de ejecutar el programa:

Los i-nodos son:
./a.out 55
./bin/ej 123
./bin/ej2 87
...
Existen 24 archivos regulares con permiso x para grupo y otros
El tamaño total ocupado por dichos archivos es 2345674 bytes
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<dirent.h>
int func(char *dir) {
    DIR *directorio;
    struct dirent *file;//estructura directorio
    int fd;//descriptor de archivo 
    int tamanototal=0;//almacena el tamaño total
    long int permisos,permisosa;
    struct stat atributos;//estructura de los atributos de un archivo
    directorio = opendir(dir);//abrimos el directorio
    file = readdir(directorio);//almacenamso en file el primer archivo del directorio
    chdir(dir);//abrimos el directorio.
    while(file != NULL) {//mientras el archivo no sea nulo
        if(strcmp(file->d_name,".")==1 && strcmp(file->d_name,"..")==1) {//si el nombre del archivo es diferente a ".." o "."
            if(stat(file->d_name,&atributos) < 0) {//almacenamos sus atributos
                printf("\nError al intentar acceder a los atributos");
                perror("\nstat Fail");
                exit(-1);
            }
            if(S_ISDIR(atributos.st_mode)) {//si es un directorio
                tamanototal+=func(file->d_name);//llamamaos recursivamente a la funcion
                chdir("..");//volvemos al directorio al que estabamos.
            } else if((atributos.st_mode & S_IXGRP)&& (atributos.st_mode & S_IXOTH)) {
					//si el archivo tiene perimos de ejecucion para grupo y otros.
                printf("%s  ",file->d_name);//mostramos el archivo
                printf("%d\n",(int)atributos.st_ino);//mostramos su numero de inodos
                tamanototal+=(int)atributos.st_size;//le sumamso el tamaño del archivo al tamaño total
            }
        }
        file = readdir(directorio);//abrimos el proximo archivo
    }
    if(closedir(directorio)<0) {//cerramos el directorio
        printf("\nclosedir Fail \n\n");
        exit(-1);
    }
    return tamanototal;//devolvemso el tamaño total
}



int main(int numarg,char* arg[]) {
    printf("Numero de i-nodos\n");
    printf("Total size:%d\n", func(arg[1]));//llamamos a la funcion
    return 0;
}
