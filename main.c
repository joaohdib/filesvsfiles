#include "heap.h"
#include "normal.h"
#include "sorted.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Book *deletaBooksVetor(Book *vetorBooks, int size) {
  int contadorAtivas = 0;
  Book *vetorBooksAtivos;
  int contadorBooks = 0;
  for (int i = 0; i < size; i++) {
    if (vetorBooks[i].active == 1) {
      contadorAtivas++;
    }
  }

  vetorBooksAtivos = (Book *)malloc(sizeof(Book) * contadorAtivas);
  for (int j = 0; j < size; j++) {
    if (vetorBooks[j].active == 1) {
      vetorBooks[contadorBooks] = vetorBooks[j];
      contadorBooks++;
    }
  }
  return vetorBooksAtivos;
}

void salvaManager(FileManager *manager) {
  FILE *arq = fopen("manager.dat", "wb");
  fwrite(manager, sizeof(FileManager), 1, arq);
  fclose(arq);
}

void compararTempos(double tempoTxt, double tempoBin, double tempoSortedTxt,
                    double tempoSortedBin, double tempoHeapTxt,
                    double tempoHeapBin) {

  if (tempoTxt < tempoBin && tempoTxt < tempoSortedTxt &&
      tempoTxt < tempoSortedBin && tempoTxt < tempoHeapTxt &&
      tempoTxt < tempoHeapBin) {
    printf("O método de texto (tempoTxt) foi o mais rápido.\n");
  } else if (tempoBin < tempoSortedTxt && tempoBin < tempoSortedBin &&
             tempoBin < tempoHeapTxt && tempoBin < tempoHeapBin) {
    printf("O método binário (tempoBin) foi o mais rápido.\n");
  } else if (tempoSortedTxt < tempoSortedBin && tempoSortedTxt < tempoHeapTxt &&
             tempoSortedTxt < tempoHeapBin) {
    printf("O método de texto ordenado (tempoSortedTxt) foi o mais rápido.\n");
  } else if (tempoSortedBin < tempoHeapTxt && tempoSortedBin < tempoHeapBin) {
    printf("O método binário ordenado (tempoSortedBin) foi o mais rápido.\n");
  } else if (tempoHeapTxt < tempoHeapBin) {
    printf("O método heap de texto (tempoHeapTxt) foi o mais rápido.\n");
  } else {
    printf("O método heap binário (tempoHeapBin) foi o mais rápido.\n");
  }
}

FILE *create_fileBin(char *filename) {
  FILE *arq;
  arq = fopen(filename, "wb");
  fclose(arq);
  return arq;
}

FILE *create_fileTxt(char *filename) {
  FILE *arq;
  arq = fopen(filename, "w");
  fclose(arq);
  return arq;
}

int main() {

  FILE *arqBin, *arqTxt, *arqSortedBin, *arqSortedTxt, *arqHeapBin, *arqHeapTxt;
  clock_t start, end, diff;
  double tempoTxt, tempoBin, tempoSortedTxt, tempoSortedBin, tempoHeapTxt,
      tempoHeapBin;
  FileManager manager = {0, 0};

  Book livro1, livro2, livro3, livro4, livro5, livro6;

  livro1.id = 1;
  livro1.qtdPag = 200;
  livro1.price = 29.99;
  strcpy(livro1.title, "Livro 1");
  strcpy(livro1.genre, "Ficcao");
  strcpy(livro1.author, "Autor 1");
  livro1.active = 1;

  livro2.id = 2;
  livro2.qtdPag = 250;
  livro2.price = 34.99;
  strcpy(livro2.title, "Livro 2");
  strcpy(livro2.genre, "Aventura");
  strcpy(livro2.author, "Autor 2");
  livro2.active = 1;

  livro3.id = 3;
  livro3.qtdPag = 180;
  livro3.price = 27.50;
  strcpy(livro3.title, "Livro 3");
  strcpy(livro3.genre, "Misterio");
  strcpy(livro3.author, "Autor 3");
  livro3.active = 1;

  livro4.id = 4;
  livro4.qtdPag = 300;
  livro4.price = 39.99;
  strcpy(livro4.title, "Livro 4");
  strcpy(livro4.genre, "Fantasia");
  strcpy(livro4.author, "Autor 4");
  livro4.active = 1;

  livro5.id = 5;
  livro5.qtdPag = 220;
  livro5.price = 31.50;
  strcpy(livro5.title, "Livro 5");
  strcpy(livro5.genre, "Romance");
  strcpy(livro5.author, "Autor 5");
  livro5.active = 1;

  livro6.id = 6;
  livro6.qtdPag = 260;
  livro6.price = 36.75;
  strcpy(livro6.title, "Livro 6");
  strcpy(livro6.genre, "Suspense");
  strcpy(livro6.author, "Autor 6");
  livro6.active = 1;

  //                                       ======== CREATE ========
  create_fileTxt("livros.txt");
  start = clock();
  createTxt("livros.txt", get_file_sizeTxt("livros.txt"), livro1);
  createTxt("livros.txt", get_file_sizeTxt("livros.txt"), livro2);
  createTxt("livros.txt", get_file_sizeTxt("livros.txt"), livro3);
  createTxt("livros.txt", get_file_sizeTxt("livros.txt"), livro4);
  createTxt("livros.txt", get_file_sizeTxt("livros.txt"), livro5);
  createTestTxt("livros.txt", get_file_sizeTxt("livros.txt"), livro6);
  end = clock();
  diff = end - start;
  tempoTxt = (double)diff / CLOCKS_PER_SEC;

  create_fileBin("livrosBin.dat");
  start = clock();
  createBin("livrosBin.dat", get_file_sizeBin("livrosBin.dat"), livro1);
  createBin("livrosBin.dat", get_file_sizeBin("livrosBin.dat"), livro2);
  createBin("livrosBin.dat", get_file_sizeBin("livrosBin.dat"), livro3);
  createBin("livrosBin.dat", get_file_sizeBin("livrosBin.dat"), livro4);
  createBin("livrosBin.dat", get_file_sizeBin("livrosBin.dat"), livro5);
  createTestBin("livrosBin.dat", get_file_sizeBin("livrosBin.dat"), livro6);
  end = clock();
  diff = end - start;
  tempoBin = (double)diff / CLOCKS_PER_SEC;

  create_fileTxt("livrosSortedTxt.txt");

  start = clock();
  createSortedTxt("livrosSortedTxt.txt",
                  get_file_sizeTxt("livrosSortedTxt.txt"), livro1);
  createSortedTxt("livrosSortedTxt.txt",
                  get_file_sizeTxt("livrosSortedTxt.txt"), livro2);
  createSortedTxt("livrosSortedTxt.txt",
                  get_file_sizeTxt("livrosSortedTxt.txt"), livro3);
  createSortedTxt("livrosSortedTxt.txt",
                  get_file_sizeTxt("livrosSortedTxt.txt"), livro4);
  createSortedTxt("livrosSortedTxt.txt",
                  get_file_sizeTxt("livrosSortedTxt.txt"), livro5);
  createSortedTxtTest("livrosSortedTxt.txt",
                      get_file_sizeTxt("livrosSortedTxt.txt"), livro6);
  end = clock();
  diff = end - start;
  tempoSortedTxt = (double)diff / CLOCKS_PER_SEC;

  create_fileBin("livrosSortedBin.dat");

  start = clock();
  createSortedBin("livrosSortedBin.dat",
                  get_file_sizeBin("livrosSortedBin.dat"), livro1);
  createSortedBin("livrosSortedBin.dat",
                  get_file_sizeBin("livrosSortedBin.dat"), livro2);
  createSortedBin("livrosSortedBin.dat",
                  get_file_sizeBin("livrosSortedBin.dat"), livro3);
  createSortedBin("livrosSortedBin.dat",
                  get_file_sizeBin("livrosSortedBin.dat"), livro4);
  createSortedBin("livrosSortedBin.dat",
                  get_file_sizeBin("livrosSortedBin.dat"), livro5);
  createSortedBinTest("livrosSortedBin.dat",
                      get_file_sizeBin("livrosSortedBin.dat"), livro6);
  end = clock();
  diff = end - start;
  tempoSortedBin = (double)diff / CLOCKS_PER_SEC;

  create_fileTxt("livrosHeapTxt.txt");

  start = clock();
  createHeapTxt("livrosHeapTxt.txt", get_file_sizeTxt("livrosHeapTxt.txt"),
                livro1);
  createHeapTxt("livrosHeapTxt.txt", get_file_sizeTxt("livrosHeapTxt.txt"),
                livro2);
  createHeapTxt("livrosHeapTxt.txt", get_file_sizeTxt("livrosHeapTxt.txt"),
                livro3);
  createHeapTxt("livrosHeapTxt.txt", get_file_sizeTxt("livrosHeapTxt.txt"),
                livro4);
  createHeapTxt("livrosHeapTxt.txt", get_file_sizeTxt("livrosHeapTxt.txt"),
                livro5);
  createHeapTxtTest("livrosHeapTxt.txt", get_file_sizeTxt("livrosHeapTxt.txt"),
                    livro6);
  end = clock();
  diff = end - start;
  tempoHeapTxt = (double)diff / CLOCKS_PER_SEC;

  create_fileBin("livrosHeapBin.dat");

  start = clock();
  createHeapBin("livrosHeapBin.dat", &manager, &livro1);
  createHeapBin("livrosHeapBin.dat", &manager, &livro2);
  createHeapBin("livrosHeapBin.dat", &manager, &livro3);
  createHeapBin("livrosHeapBin.dat", &manager, &livro4);
  createHeapBin("livrosHeapBin.dat", &manager, &livro5);
  createHeapBin("livrosHeapBin.dat", &manager, &livro6);
  end = clock();
  diff = end - start;
  tempoHeapBin = (double)diff / CLOCKS_PER_SEC;

  printf("========= TESTE DE CRIACAO DE 6 LIVROS: =========\n");
  printf("Tempo do arquivo normal txt: %f\n", tempoTxt);
  printf("Tempo do arquivo normal binario: %f\n", tempoBin);
  printf("Tempo do arquivo sorted txt: %f\n", tempoSortedTxt);
  printf("Tempo do arquivo sorted bin: %f\n", tempoSortedBin);
  printf("Tempo do arquivo heap txt: %f\n", tempoHeapTxt);
  printf("Tempo do arquivo heap bin: %f\n", tempoHeapBin);
  compararTempos(tempoTxt, tempoBin, tempoSortedTxt, tempoSortedBin,
                 tempoHeapTxt, tempoHeapBin);
  printf("============================\n");

  //                                       ======== LIST ========
  printf("========= TESTE PARA LISTAR OS LIVROS: =========\n");
  printf("-- ARQUIVO NORMAL: -- \n");
  start = clock();
  listTxt("livros.txt", get_file_sizeTxt("livros.txt"));
  end = clock();
  diff = end - start;
  tempoTxt = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO BINARIO: -- \n");
  start = clock();
  listBin("livrosBin.dat", get_file_sizeBin("livrosBin.dat"));
  end = clock();
  diff = end - start;
  tempoBin = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO SORT TXT: -- \n");
  start = clock();
  listSortedTxt("livrosSortedTxt.txt", get_file_sizeTxt("livrosSortedTxt.txt"));
  end = clock();
  diff = end - start;
  tempoSortedTxt = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO SORT BINARIO: -- \n");
  start = clock();
  listSortedBin("livrosSortedBin.dat", get_file_sizeBin("livrosSortedBin.dat"));
  end = clock();
  diff = end - start;
  tempoSortedBin = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO HEAP TXT: -- \n");
  start = clock();
  listHeapTxt("livrosHeapTxt.txt", get_file_sizeTxt("livrosHeapTxt.txt"));
  end = clock();
  diff = end - start;
  tempoHeapTxt = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO HEAP BINARIO: -- \n");
  start = clock();
  listHeapBin("livrosHeapBin.dat", &manager);
  end = clock();
  diff = end - start;
  tempoHeapBin = (double)diff / CLOCKS_PER_SEC;

  printf("========= TESTE DE LIST DE 6 LIVROS: =========\n");
  printf("Tempo do arquivo normal txt: %f\n", tempoTxt);
  printf("Tempo do arquivo normal binario: %f\n", tempoBin);
  printf("Tempo do arquivo sorted txt: %f\n", tempoSortedTxt);
  printf("Tempo do arquivo sorted bin: %f\n", tempoSortedBin);
  printf("Tempo do arquivo heap txt: %f\n", tempoHeapTxt);
  printf("Tempo do arquivo heap bin: %f\n", tempoHeapBin);
  compararTempos(tempoTxt, tempoBin, tempoSortedTxt, tempoSortedBin,
                 tempoHeapTxt, tempoHeapBin);
  printf("============================\n");

  //                                       ======== LIST ========
  printf("========= TESTE PARA LER O LIVRO: =========\n");
  printf("-- ARQUIVO NORMAL: -- \n");
  start = clock();
  readTxt("livros.txt", 2023, get_file_sizeTxt("livros.txt"));
  end = clock();
  diff = end - start;
  tempoTxt = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO BINARIO: -- \n");
  start = clock();
  readBin("livrosBin.dat", 2023, get_file_sizeBin("livrosBin.dat"));
  end = clock();
  diff = end - start;
  tempoBin = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO SORT TXT: -- \n");
  start = clock();
  readSortedTxt("livrosSortedTxt.txt", 2023,
                get_file_sizeTxt("livrosSortedTxt.txt"));
  end = clock();
  diff = end - start;
  tempoSortedTxt = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO SORT BINARIO: -- \n");
  start = clock();
  readSortedBin("livrosSortedBin.dat", 2023,
                get_file_sizeBin("livrosSortedBin.dat"));
  end = clock();
  diff = end - start;
  tempoSortedBin = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO HEAP TXT: -- \n");
  start = clock();
  readHeapTxt("livrosHeapTxt.txt", 2023, get_file_sizeTxt("livrosHeapTxt.txt"));
  end = clock();
  diff = end - start;
  tempoHeapTxt = (double)diff / CLOCKS_PER_SEC;

  printf("-- ARQUIVO HEAP BINARIO: -- \n");
  start = clock();
  readHeapBin("livrosHeapBin.dat", &manager, 5);
  end = clock();
  diff = end - start;
  tempoHeapBin = (double)diff / CLOCKS_PER_SEC;

  printf("========= TESTE DE READ DE 1 LIVRO: =========\n");
  printf("Tempo do arquivo normal txt: %f\n", tempoTxt);
  printf("Tempo do arquivo normal binario: %f\n", tempoBin);
  printf("Tempo do arquivo sorted txt: %f\n", tempoSortedTxt);
  printf("Tempo do arquivo sorted bin: %f\n", tempoSortedBin);
  printf("Tempo do arquivo heap txt: %f\n", tempoHeapTxt);
  printf("Tempo do arquivo heap bin: %f\n", tempoHeapBin);
  compararTempos(tempoTxt, tempoBin, tempoSortedTxt, tempoSortedBin,
                 tempoHeapTxt, tempoHeapBin);
  printf("============================\n");

  //                                       ======== UPDATE ========
  Book livro7;
  livro7.id = 2023;
  livro7.qtdPag = 300;
  livro7.price = 45.99;
  strcpy(livro7.title, "Livro 7");
  strcpy(livro7.genre, "Aventura");
  strcpy(livro7.author, "Autor 7");
  livro7.active = 1;

  printf("========= TESTE PARA ATUALIZAR O LIVRO: =========\n");

  start = clock();
  updateTxt("livros.txt", livro7, get_file_sizeTxt("livros.txt"));
  end = clock();
  diff = end - start;
  tempoTxt = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  updateBin("livrosBin.dat", livro7, get_file_sizeBin("livrosBin.dat"));
  end = clock();
  diff = end - start;
  tempoBin = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  updateSortedTxt("livrosSortedTxt.txt", livro7,
                  get_file_sizeTxt("livrosSortedTxt.txt"));
  end = clock();
  diff = end - start;
  tempoSortedTxt = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  updateSorted("livrosSortedBin.dat", livro7,
               get_file_sizeBin("livrosSortedBin.dat"));
  end = clock();
  diff = end - start;
  tempoSortedBin = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  updateHeapTxt("livrosHeapTxt.txt", livro7,
                get_file_sizeTxt("livrosHeapTxt.txt"));
  end = clock();
  diff = end - start;
  tempoHeapTxt = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  updateHeapBin("livrosHeapBin.dat", &manager, 5, &livro7);
  end = clock();
  diff = end - start;
  tempoHeapBin = (double)diff / CLOCKS_PER_SEC;

  printf("========= TESTE DE UPDATE DE LIVRO: =========\n");
  printf("Tempo do arquivo normal txt: %f\n", tempoTxt);
  printf("Tempo do arquivo normal binario: %f\n", tempoBin);
  printf("Tempo do arquivo sorted txt: %f\n", tempoSortedTxt);
  printf("Tempo do arquivo sorted bin: %f\n", tempoSortedBin);
  printf("Tempo do arquivo heap txt: %f\n", tempoHeapTxt);
  printf("Tempo do arquivo heap bin: %f\n", tempoHeapBin);
  compararTempos(tempoTxt, tempoBin, tempoSortedTxt, tempoSortedBin,
                 tempoHeapTxt, tempoHeapBin);
  printf("============================\n");

  //                                       ======== DELETE ========

  printf("========= TESTE PARA DELETAR O LIVRO: =========\n");

  start = clock();
  deleteeTxt("livros.txt", 2023, get_file_sizeTxt("livros.txt"));
  end = clock();
  diff = end - start;
  tempoTxt = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  deleteeBin("livrosBin.dat", 2023, get_file_sizeBin("livrosBin.dat"));
  end = clock();
  diff = end - start;
  tempoBin = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  deleteSortedTxt("livrosSortedTxt.txt", 2023,
                  get_file_sizeTxt("livrosSortedTxt.txt"));
  end = clock();
  diff = end - start;
  tempoSortedTxt = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  deleteSortedBin("livrosSortedBin.dat", 2023,
                  get_file_sizeBin("livrosSortedBin.dat"));
  end = clock();
  diff = end - start;
  tempoSortedBin = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  deleteHeapTxt("livrosHeapTxt.txt", 2023,
                get_file_sizeTxt("livrosHeapTxt.txt"));
  end = clock();
  diff = end - start;
  tempoHeapTxt = (double)diff / CLOCKS_PER_SEC;

  start = clock();
  deleteHeapBin("livrosHeapBin.dat", &manager, 5);
  end = clock();
  diff = end - start;
  tempoHeapBin = (double)diff / CLOCKS_PER_SEC;

  printf("========= TESTE DE DELETE DE LIVRO: =========\n");
  printf("Tempo do arquivo normal txt: %f\n", tempoTxt);
  printf("Tempo do arquivo normal binario: %f\n", tempoBin);
  printf("Tempo do arquivo sorted txt: %f\n", tempoSortedTxt);
  printf("Tempo do arquivo sorted bin: %f\n", tempoSortedBin);
  printf("Tempo do arquivo heap txt: %f\n", tempoHeapTxt);
  printf("Tempo do arquivo heap bin: %f\n", tempoHeapBin);
  compararTempos(tempoTxt, tempoBin, tempoSortedTxt, tempoSortedBin,
                 tempoHeapTxt, tempoHeapBin);
  printf("============================\n");

  return 0;
}