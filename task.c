#include "task.h"
#include <stdio.h>
#include <stdlib.h>

Book *createVetorBooks(char *filename, int size) {

  Book *vetor;
  FILE *arq;
  arq = fopen(filename, "rb");
  if (arq == NULL) {
    exit(1);
  }
  vetor = (Book *)malloc(sizeof(Book) * size);
  Book bookAux;
  for (int i = 0; i < size; i++) {
    fread(&bookAux, sizeof(Book), 1, arq);
    vetor[i] = bookAux;
  }

  return vetor;
}

Book *createVetorBooksTxt(char *filename, int size) {
  Book *vetor;
  FILE *arq;
  arq = fopen(filename, "r");
  if (arq == NULL) {
    exit(1);
  }
  vetor = (Book *)malloc(sizeof(Book) * size);
  Book bookAux;

  for (int i = 0; i < size; i++) {
    fscanf(arq, "%d,%d,%[^,],%[^,],%[^,],%f,%d\n", &bookAux.id,
           &bookAux.qtdPag, bookAux.title, bookAux.genre, bookAux.author,
           &bookAux.price, &bookAux.active);
    vetor[i] = bookAux;
  }
  fclose(arq);
  return vetor;
}

int compfunc(const void *t1, const void *t2) {
  return ((Book *)t1)->id - ((Book *)t2)->id;
}

int randomId() {
  int n = rand();
  return n;
}

int get_file_sizeBin(char *filename) {
  int contador;
  FileManager manager;
  FILE *arq;
  int size = 0;
  Book placeholder;

  arq = fopen(filename, "rb");
  if (arq == NULL)
    return -1;

  while (fread(&placeholder, sizeof(Book), 1, arq) == 1)
    size++;

  fclose(arq);
  return size;
}

int get_file_sizeTxt(char *filename) {
  int size = 0;
  Book bookAux;

  FILE *arq = fopen(filename, "r");
  if (arq == NULL)
    return -1;

  while (fscanf(arq, "%d,%d,%[^,],%[^,],%[^,],%f,%d\n", &bookAux.id,
                &bookAux.qtdPag, bookAux.title, bookAux.genre, bookAux.author,
                &bookAux.price, &bookAux.active) == 7)
    size++;

  fclose(arq);
  return size;
}