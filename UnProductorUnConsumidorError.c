/*
  Archivo: UnProductorUnConsumidorError.c
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
#define TAMANHOBUFFER 5
#define TOTALINTERACCIONES 20

int buffer[TAMANHOBUFFER];
int casillaActualEnBuffer = 0;
int interacciones = 0;

void estado(){
  printf("Interacciones: %d \t Documentos en buffer: %d\n\n", interacciones, casillaActualEnBuffer);
}

void *producir(void *arg){
  while(interacciones < TOTALINTERACCIONES){
    if(casillaActualEnBuffer < TAMANHOBUFFER){
      printf("COMPUTADOR: enviando un documento al espacio %d del buffer...\n", casillaActualEnBuffer+1);

      // Llamada al método que envía un documento al buffer de impresión. 

      casillaActualEnBuffer++;
      interacciones++;
      estado();
    }
  }
}

int *consumir(void *arg){
  while(interacciones < TOTALINTERACCIONES){
    if(casillaActualEnBuffer > 0){
      printf("IMPRESORA: imprimiendo el documento del espacio %d...\n", casillaActualEnBuffer);

    // Llamada al método que imprime un documento desde el buffer de impresión.

      casillaActualEnBuffer--;
      interacciones++;
      estado();
    }
  }
}

int main(int argc, char *argv[]) {
  pthread_t productor, consumidor;

  pthread_create(&productor, NULL, (void *) producir, NULL);
  pthread_create(&consumidor, NULL, (void *) consumir, NULL);

  pthread_join(productor, NULL);
  pthread_join(consumidor, NULL);

  return 0;
}
