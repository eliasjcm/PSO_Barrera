/* 
    Trabajo en Clases: Estructuras de Sincronización
    -Johan Calvo Vargas 2020297388
    -Elías Castro Montero 2020098930
    -Abiel Porras Garro 2020209597
    -Fabián Rojas Arguedas 2019380107

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// suma de todos los tiempos esperados por los 3 hilos creados
int num = 0;
// Barrera que utilizaran todos los hilos
pthread_barrier_t barrier;

/*
    - Los hilos se duermen r segundos y luego se esperan en la barrera
    - La variable num posee el valor total de la suma de los tiempos que los hilos esperan
    - La variable num debe ser igual a la suma de los tiempos independientemente de cual hilo se ejecute primero
    - Cada uno de los 3 hilos suma r a num
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
    // Array que almacena los 3 hilos por utilizar
    pthread_t t[3];
    srand(time(NULL));

    // Inicializar el barrier, recibe como tercer parametro la cantiddad de hilos que deben llamar pthread_barrier_wait
    // en este caso 4, uno por cada hilo y el que ejecuta el main
    pthread_barrier_init(&barrier, NULL, 4);

    // Se corren los 3 hilos
    pthread_create(&t[0], NULL, thread_0, NULL);
    pthread_create(&t[1], NULL, thread_1, NULL);
    pthread_create(&t[2], NULL, thread_2, NULL);

    // El hilo que ejecuta el main, se sincroniza con los otros hilos
    pthread_barrier_wait(&barrier);

    // Se ejecuta cuando la barrera termina, despues de que todos los hilos hayan pasado la barrera
    printf("Barrera Finalizada, sleep - suma total: %d\n", num);

    // Se destruye la barrera para liberar memoria.
    pthread_barrier_destroy(&barrier);
    return 0;
}