/*
  Archivo: UnProductorDosConsumidores.c
  Sistemas Operativos - 750001C Grupo 01

  Problemas clásicos de sincronización usando semáforos

  Autores:
    Christian David Vargas Gutiérrez - vargas.christian@correounivalle.edu.co
    Ervin Carabali Ibarra - ervin.caravali@correounivalle.edu.co
    Julian David Rendón - julian.david.rendon@correounivalle.edu.co

  Profesor:
    Ph.D. John Sanabria 

  Licencia: GNU-GPL
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define TAMANHOBUFFER 5
#define TOTALINTERACCIONES 98

int buffer[TAMANHOBUFFER];
int casillaActualEnBuffer = 0;
int interacciones = 0;
sem_t espaciosVacios;
sem_t espaciosLlenos;
sem_t mutex;

void estado(){
  printf("Interacciones: %d \t Documentos en buffer: %d\n\n", interacciones, casillaActualEnBuffer);
}

void *producir(void *arg){
  while(interacciones < TOTALINTERACCIONES){
    sem_wait(&espaciosVacios);
    sem_wait(&mutex);

    printf("COMPUTADOR: enviando un documento al espacio %d del buffer...\n", casillaActualEnBuffer+1);

    // Llamada al método que envía un documento al buffer de impresión. 

    casillaActualEnBuffer++;
    interacciones++;
    estado();

    sem_post(&mutex);
    sem_post(&espaciosLlenos);
  }
}

int *consumir(void *arg){
  int *numeroImpresora = arg;

  while(interacciones < TOTALINTERACCIONES){
    sem_wait(&espaciosLlenos);
    sem_wait(&mutex);

    printf("IMPRESORA %d: imprimiendo el documento del espacio %d...\n", *numeroImpresora, casillaActualEnBuffer);

    // Llamada al método que imprime un documento desde el buffer de impresión.

    casillaActualEnBuffer--;
    interacciones++;
    estado();

    sem_post(&mutex);
    sem_post(&espaciosVacios);
  }
}

int main(int argc, char *argv[]) {
  pthread_t productor, consumidor1, consumidor2;
  int identificadorConsumidor1 = 1;
  int identificadorConsumidor2 = 2;
  sem_init(&espaciosVacios, 0, TAMANHOBUFFER);
  sem_init(&espaciosLlenos, 0, 0);
  sem_init(&mutex, 0, 1);

  pthread_create(&productor, NULL, (void *) producir, NULL);
  pthread_create(&consumidor1, NULL, (void *) consumir, &identificadorConsumidor1);
  pthread_create(&consumidor2, NULL, (void *) consumir, &identificadorConsumidor2);

  pthread_join(productor, NULL);
  pthread_join(consumidor1, NULL);
  pthread_join(consumidor2, NULL);

  sem_destroy(&espaciosVacios);
  sem_destroy(&espaciosLlenos);
  sem_destroy(&mutex);

  return 0;
}
