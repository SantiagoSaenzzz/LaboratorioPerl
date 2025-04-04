/**************************************************************
Pontificia Universidad Javeriana
Facultad de Ingeniería - Ingeniería de Sistemas
Materia: Sistemas Operativos
Autor original: J. Corredor
Autor edición: Jair Santiago Vargas Saenz
Fecha: Febrero 2024
Fecha edicion: 3 de abril 2025
Tema: Taller de Evaluación de Rendimiento
Fichero: Menu de multiplicación de matrices NxN por hilos.
Descripción:
Evaluar el tiempo de ejecución del algoritmo clásico
de multiplicación de matrices.
Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/
#include "mm_clasica.h"

// Función principal: permite ejecutar con argumentos o menú interactivo
int main(int argc, char *argv[]) {
    int SZ, n_threads;

    if (argc < 3) {
        printf("No se ingresaron argumentos.\n");
        printf("¿Desea introducirlos manualmente? (1 = sí / 0 = no): ");
        int opcion;
        scanf("%d", &opcion);
        if (opcion == 1) {
            printf("Ingrese el tamaño de la matriz (NxN): ");
            scanf("%d", &SZ);
            printf("Ingrese el número de hilos: ");
            scanf("%d", &n_threads);
        } else {
            printf("Uso correcto:\n$ ./matriz tamMatriz numHilos\n");
            return -1;
        }
    } else {
        SZ = atoi(argv[1]);
        n_threads = atoi(argv[2]);
    }

        // Arreglo de hilos a crear
    pthread_t p[n_threads];
        // Atributos de los hilos
    pthread_attr_t atrMM;

        // Asignación de punteros a bloques de MEM_CHUNK
    mA = MEM_CHUNK;
    mB = mA + SZ * SZ;
    mC = mB + SZ * SZ;

        // Rellenar matrices con datos iniciales
    llenar_matriz(SZ);
    print_matrix(SZ, mA);
    print_matrix(SZ, mB);

        // Iniciar conteo de tiempo
    inicial_tiempo();

        // Inicializar mutex y atributos de los hilos
    pthread_mutex_init(&MM_mutex, NULL);
    pthread_attr_init(&atrMM);
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

        // Crear los hilos para procesar segmentos de la multiplicación
        // Esperar a que todos los hilos terminen su ejecución
    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros));
        datos->idH = j;
        datos->nH  = n_threads;
        datos->N   = SZ;
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos);
    }

        // Esperar a que todos los hilos terminen su ejecución
    for (int j = 0; j < n_threads; j++)
        pthread_join(p[j], NULL);

        // Finalizar conteo de tiempo y mostrar resultado
    final_tiempo();

    print_matrix(SZ, mC);

    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);
    pthread_exit(NULL);
}

