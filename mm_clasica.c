/**************************************************************
Pontificia Universidad Javeriana
Facultad de Ingeniería - Ingeniería de Sistemas
Materia: Sistemas Operativos
Autor original: J. Corredor
Autor edición: Jair Santiago Vargas Saenz
Fecha: Febrero 2024
Fecha edicion: 3 de abril 2025
Tema: Taller de Evaluación de Rendimiento
Fichero: Fuente de multiplicación de matrices NxN por hilos.
Descripción:
Evaluar el tiempo de ejecución del algoritmo clásico
de multiplicación de matrices.
Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/
#include "mm_clasica.h"

// Espacio contiguo de memoria donde se almacenan mA, mB y mC
double MEM_CHUNK[DATA_SIZE];
// Punteros a las matrices A, B y C en el bloque MEM_CHUNK
double *mA, *mB, *mC;
// Mutex global para sincronización (actualmente no es esencial en este código)
pthread_mutex_t MM_mutex;
// Variables para almacenar los tiempos de inicio y fin
struct timeval start, stop;

void llenar_matriz(int SZ){
    srand48(time(NULL));
    for(int i = 0; i < SZ*SZ; i++){
        mA[i] = 1.1 * i;
        mB[i] = 2.2 * i;
        mC[i] = 0;
    }
}
//imprime la matriz
void print_matrix(int sz, double *matriz){
    if(sz < 12){
        for(int i = 0; i < sz*sz; i++){
            if(i % sz == 0) printf("\n");
            printf(" %.3f ", matriz[i]);
        }
        printf("\n>-------------------->\n");
    }
}

void inicial_tiempo(){
    gettimeofday(&start, NULL);
}

void final_tiempo(){
    gettimeofday(&stop, NULL);
    stop.tv_sec -= start.tv_sec;
    printf("\n:-> %9.0f µs\n", (double)(stop.tv_sec * 1000000 + stop.tv_usec));
}

void *mult_thread(void *variables){
    struct parametros *data = (struct parametros *)variables;
    int idH = data->idH;
    int nH  = data->nH;
    int N   = data->N;

    int ini = (N / nH) * idH;
    int fin = (N / nH) * (idH + 1);

    for (int i = ini; i < fin; i++){
        for (int j = 0; j < N; j++){
            double *pA = mA + (i * N);
            double *pB = mB + j;
            double sumaTemp = 0.0;

            for (int k = 0; k < N; k++, pA++, pB += N){
                sumaTemp += (*pA * *pB);
            }
            mC[i * N + j] = sumaTemp;
        }
    }

    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);
    pthread_exit(NULL);
}

