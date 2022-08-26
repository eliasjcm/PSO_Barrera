/*
    Trabajo en Clases: Estructuras de Sincronización

    Estructura -> Barrera - Implementación en C

    Estudiantes:
        -Johan Calvo Vargas - 2020297388
        -Elías Castro Montero - 2020098930
        -Abiel Porras Garro - 2020209597
        -Fabián Rojas Arguedas - 2019380107

    Para compilar y correr el programa, basta con ejecutar el makefile (con el siguiente comando):
        make
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// suma de todos los tiempos esperados por los 3 hilos creados
int num = 0;
// Barrera utilizada para sincronizar la ejecución
// que utilizaran todos los hilos
// Es la estructura POSIX para el método de sincronización de barrera
pthread_barrier_t barrier;

/*
    - Los hilos se duermen r segundos y luego se esperan en la barrera
    - La variable num posee el valor total de la suma de los tiempos que los hilos esperan
    - La variable num debe ser igual a la suma de los tiempos independientemente de cual hilo se ejecute primero
    - Cada uno de los 3 hilos suma r a num
    - Cada thread llama a pthread_barrier_wait, para esperar a que todos los hilos lleguen a la barrera
*/

void *thread_0(void *param)
{
    int r = rand() % 4 + 1;
    sleep(r);
    num += r;
    printf("thread_0 ejecutado en %d segundo(s)\n", r);
    pthread_barrier_wait(&barrier);
}
void *thread_1(void *param)
{
    int r = rand() % 4 + 1;
    sleep(r);
    num += r;
    printf("thread_1 ejecutado en %d segundo(s)\n", r);

    pthread_barrier_wait(&barrier);
}
void *thread_2(void *param)
{
    int r = rand() % 4 + 1;
    sleep(r);
    num += r;
    printf("thread_2 ejecutado en %d segundo(s)\n", r);

    pthread_barrier_wait(&barrier);
}

int main(void)
{
    // Array que almacenará los 3 identificadores de los hilos por utilizar
    pthread_t t[3];
    // Utilizado para crear después los números aleatorios utilizados para cada sleep de cada hilo
    srand(time(NULL));

    // Inicializa la barrera, recibe como tercer parametro la cantidad de hilos que deben llamar pthread_barrier_wait
    // en este caso 4, uno por cada hilo y el que ejecuta el main; para abrir la barrera
    pthread_barrier_init(&barrier, NULL, 4);

    // Se corren los 3 hilos, cada uno ejecuta la función correspondiente
    pthread_create(&t[0], NULL, thread_0, NULL);
    pthread_create(&t[1], NULL, thread_1, NULL);
    pthread_create(&t[2], NULL, thread_2, NULL);

    // El hilo que ejecuta el main, se sincroniza con los otros hilos, y espera a que todos llegan a la barrera
    pthread_barrier_wait(&barrier);

    // Se ejecuta cuando la barrera termina, después de que todos los hilos hayan pasado la barrera
    printf("Barrera Finalizada, sleep - suma total: %d\n", num);

    // Se destruye la barrera para liberar memoria.
    pthread_barrier_destroy(&barrier);
    return 0;
}