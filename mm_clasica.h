/**************************************************************
Pontificia Universidad Javeriana
Facultad de Ingeniería - Ingeniería de Sistemas
Materia: Sistemas Operativos
Autor original: J. Corredor
Autor edición: Jair Santiago Vargas Saenz
Fecha: Febrero 2024
Fecha edicion: 3 de abril 2025
Tema: Taller de Evaluación de Rendimiento
Fichero: Funciones de multiplicación de matrices NxN por hilos.
Descripción:
Evaluar el tiempo de ejecución del algoritmo clásico
de multiplicación de matrices.
Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/
#ifndef MM_CLASICA_H
#define MM_CLASICA_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DATA_SIZE (1024*1024*64*3)

extern double MEM_CHUNK[DATA_SIZE];
extern pthread_mutex_t MM_mutex;
extern double *mA, *mB, *mC;
extern struct timeval start, stop;


// Estructura que contiene los parámetros que se pasarán a cada hilo
struct parametros {
    int nH;
    int idH;
    int N;
};

// Rellena mA y mB con valores secuenciales y mC con ceros
void llenar_matriz(int SZ);
// Imprime en consola la matriz si es pequeña (NxN < 12)
void print_matrix(int sz, double *matriz);
// Captura el tiempo inicial antes del cálculo
void inicial_tiempo();
// Captura el tiempo final y muestra la diferencia con el inicial
void final_tiempo();
// Lógica que ejecuta cada hilo para multiplicar una porción de las matrices
void *mult_thread(void *variables);

#endif

