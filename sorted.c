#include "sorted.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int listSortedBin(char *filename, int size) {
  Book *vetorBooks = createVetorBooks(filename, size);
  for (int i = 0; i < size; i++) { // percorre o vetor com os livros e os exibe
    printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
           "autor: %s\n",
           vetorBooks[i].id, vetorBooks[i].qtdPag, vetorBooks[i].price,
           vetorBooks[i].title, vetorBooks[i].genre, vetorBooks[i].author);
  }
  return 0;
}

int listSortedTxt(char *filename, int size) {
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  for (int i = 0; i < size; i++) { // percorre o vetor com os livros e os exibe
    printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
           "autor: %s\n",
           vetorBooks[i].id, vetorBooks[i].qtdPag, vetorBooks[i].price,
           vetorBooks[i].title, vetorBooks[i].genre, vetorBooks[i].author);
  }
  return 0;
}

int readSortedTxt(char *filename, int id, int size) {
  Book *vetorBooks;
  vetorBooks = createVetorBooksTxt(filename, size);
  int ini, fim, meio;
  ini = 0;
  fim = size - 1; // considera o fim do vetor como fim
  while (ini <= fim) {
    meio = ini + (fim - ini) / 2; // faz a conta para pegar o meio do vetor
    if (vetorBooks[meio].id == id) {
      if (vetorBooks[meio].active == 1) {
        printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
               "autor: %s\n",
               vetorBooks[meio].id, vetorBooks[meio].qtdPag,
               vetorBooks[meio].price, vetorBooks[meio].title,
               vetorBooks[meio].genre, vetorBooks[meio].author);
        return 0;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrada.\n");
        return -1;
      }
    }
    if (vetorBooks[meio].id <
        id) { // se for menor, pega a metade direita do vetor
      ini = meio + 1;
    } else { // se maior, pega a metade esquerda do vetor
      fim = meio - 1;
    }
  }
  printf("Livro nao encontrada.\n");
  return -1;
}

int readSortedBin(char *filename, int id, int size) {
  Book *vetorBooks;
  vetorBooks = createVetorBooks(filename, size);
  int ini, fim, meio;
  ini = 0;
  fim = size - 1; // considera o fim do vetor como fim
  while (ini <= fim) {
    meio = ini + (fim - ini) / 2; // faz a conta para pegar o meio do vetor
    if (vetorBooks[meio].id == id) {
      if (vetorBooks[meio].active == 1) {
        printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
               "autor: %s\n",
               vetorBooks[meio].id, vetorBooks[meio].qtdPag,
               vetorBooks[meio].price, vetorBooks[meio].title,
               vetorBooks[meio].genre, vetorBooks[meio].author);
        return 0;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrada.\n");
        return -1;
      }
    }
    if (vetorBooks[meio].id <
        id) { // se for menor, pega a metade direita do vetor
      ini = meio + 1;
    } else { // se maior, pega a metade esquerda do vetor
      fim = meio - 1;
    }
  }
  printf("Livro nao encontrada.\n");
  return -1;
}

int createSortedBin(char *filename, int size, Book newTask) {
  FILE *arq;
  Book *vetorBooks;
  arq = fopen(filename, "rb");
  vetorBooks = (Book *)malloc(
      sizeof(Book) *
      (size + 1)); // aloca o vetor de livros, pega os livros existentes,
                   // adiciona o novo, ordena de novo e troca no arquivo binario
  if (arq != NULL) {
    Book taskAux;
    for (int i = 0; i < size; i++) {
      fread(&taskAux, sizeof(Book), 1, arq);
      vetorBooks[i] = taskAux;
    }
    fclose(arq);
  }
  arq = fopen(filename, "wb");
  if (arq == NULL) {
    return -1;
  }
  newTask.id = randomId();
  newTask.active = 1;
  vetorBooks[size] = newTask;
  qsort(vetorBooks, size + 1, sizeof(Book), compfunc);
  fwrite(vetorBooks, sizeof(Book), size + 1, arq);
  fclose(arq);
  return 0;
}

int createSortedTxt(char *filename, int size, Book newTask) {
  FILE *arq;
  Book *vetorBooks = (Book *)malloc(
      sizeof(Book) *
      (size + 1)); // aloca o vetor de livros, pega os livros existentes,
                   // adiciona o novo, ordena de novo e troca no arquivo txt
  Book bookAux;
  arq = fopen(filename, "r");

  for (int i = 0; i < size; i++) {
    fscanf(arq, "%d,%d,%[^,],%[^,],%[^,],%f,%d\n", &bookAux.id, &bookAux.qtdPag,
           bookAux.title, bookAux.genre, bookAux.author, &bookAux.price,
           &bookAux.active);
    vetorBooks[i] = bookAux;
  }
  arq = fopen(filename, "w");
  if (arq == NULL) {
    return -1;
  }
  newTask.id = randomId();
  newTask.active = 1;
  vetorBooks[size] = newTask;
  qsort(vetorBooks, size + 1, sizeof(Book), compfunc);
  for (int i = 0; i < (size + 1); i++) {
    fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", vetorBooks[i].id,
            vetorBooks[i].qtdPag, vetorBooks[i].title, vetorBooks[i].genre,
            vetorBooks[i].author, vetorBooks[i].price, vetorBooks[i].active);
  }
  fclose(arq);
  return 0;
}

int createSortedBinTest(char *filename, int size, Book newTask) {
  FILE *arq;
  Book *vetorBooks;
  arq = fopen(filename, "rb");
  vetorBooks = (Book *)malloc(
      sizeof(Book) *
      (size + 1)); // aloca o vetor de livros, pega os livros existentes,
                   // adiciona o novo, ordena de novo e troca no arquivo binario
                   // (com id fixo para testes)
  if (arq != NULL) {
    Book taskAux;
    for (int i = 0; i < size; i++) {
      fread(&taskAux, sizeof(Book), 1, arq);
      vetorBooks[i] = taskAux;
    }
    fclose(arq);
  }
  arq = fopen(filename, "wb");
  if (arq == NULL) {
    return -1;
  }
  newTask.id = 2023;
  newTask.active = 1;
  vetorBooks[size] = newTask;
  qsort(vetorBooks, size + 1, sizeof(Book), compfunc);
  fwrite(vetorBooks, sizeof(Book), size + 1, arq);
  fclose(arq);
  return 0;
}

int createSortedTxtTest(char *filename, int size, Book newTask) {
  FILE *arq;
  Book *vetorBooks = (Book *)malloc(
      sizeof(Book) *
      (size + 1)); // aloca o vetor de livros, pega os livros existentes,
                   // adiciona o novo, ordena de novo e troca no arquivo txt
                   // (com id fixo para testes)
  Book bookAux;
  arq = fopen(filename, "r");

  for (int i = 0; i < size; i++) {
    fscanf(arq, "%d,%d,%[^,],%[^,],%[^,],%f,%d\n", &bookAux.id, &bookAux.qtdPag,
           bookAux.title, bookAux.genre, bookAux.author, &bookAux.price,
           &bookAux.active);
    vetorBooks[i] = bookAux;
  }
  arq = fopen(filename, "w");
  if (arq == NULL) {
    return -1;
  }
  newTask.id = 2023;
  newTask.active = 1;
  vetorBooks[size] = newTask;
  qsort(vetorBooks, size + 1, sizeof(Book), compfunc);
  for (int i = 0; i < (size + 1); i++) {
    fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", vetorBooks[i].id,
            vetorBooks[i].qtdPag, vetorBooks[i].title, vetorBooks[i].genre,
            vetorBooks[i].author, vetorBooks[i].price, vetorBooks[i].active);
  }
  fclose(arq);
  return 0;
}

int deleteSortedBin(char *filename, int id, int size) {
  Book *vetorBooks;
  FILE *arq;
  vetorBooks = createVetorBooks(filename, size);
  int ini, fim, meio;
  ini = 0;
  fim = size - 1; // pega o fim do vetor
  while (ini <= fim) {
    meio = ini + (fim - ini) / 2; // calcula o meio do vetor
    if (vetorBooks[meio].id == id) {
      if (vetorBooks[meio].active == 1) {
        vetorBooks[meio].active = 0;
        printf("Livro deletada com sucesso no arquivo sorted.\n");
        arq = fopen(filename, "wb");
        fwrite(vetorBooks, sizeof(Book), size, arq);
        fclose(arq);
        return 0;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrada.\n");
        return 0;
      }
    }
    if (vetorBooks[meio].id < id) { // se menor, pega a metade direita do vetor
      ini = meio + 1;
    } else { // do contrario, pega  a metade esquerda
      fim = meio - 1;
    }
  }
  printf("Livro nao encontrada.\n");
  return 0;
}

int deleteSortedTxt(char *filename, int id, int size) {
  Book *vetorBooks;
  FILE *arq;
  vetorBooks = createVetorBooksTxt(filename, size);
  int ini, fim, meio;
  ini = 0;
  fim = size - 1; // pega o fim do vetor

  while (ini <= fim) {
    meio = ini + (fim - ini) / 2; // calcula o meio do vetor
    if (vetorBooks[meio].id == id) {
      if (vetorBooks[meio].active == 1) {
        vetorBooks[meio].active = 0;
        printf("Livro deletada com sucesso no arquivo sorted.\n");
        arq = fopen(filename, "w");
        for (int i = 0; i < size; i++) {
          fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", vetorBooks[i].id,
                  vetorBooks[i].qtdPag, vetorBooks[i].title,
                  vetorBooks[i].genre, vetorBooks[i].author,
                  vetorBooks[i].price, vetorBooks[i].active);
        }
        fwrite(vetorBooks, sizeof(Book), size, arq);
        fclose(arq);
        return 0;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrada.\n");
        return 0;
      }
    }
    if (vetorBooks[meio].id < id) {
      ini = meio + 1; // se menor, pega a metade direita do vetor
    } else {          // do contrario, pega  a metade esquerda
      fim = meio - 1;
    }
  }
  printf("Livro nao encontrada.\n");
  return 0;
}

int updateSorted(char *filename, Book update, int size) {
  FILE *arq;
  Book *vetorBooks = createVetorBooks(filename, size);
  int id = update.id;
  int ini, fim, meio;
  ini = 0;
  fim = size - 1; // pega o fim do vetor
  while (ini <= fim) {
    meio = ini + (fim - ini) / 2; // calcula o meio do vetor
    if (vetorBooks[meio].id == id) {
      if (vetorBooks[meio].active == 1) {
        strcpy(vetorBooks[meio].title, update.title);
        strcpy(vetorBooks[meio].author, update.author);
        strcpy(vetorBooks[meio].genre, update.genre);
        vetorBooks[meio].qtdPag = update.qtdPag;
        vetorBooks[meio].price = update.price;
        arq = fopen(filename, "rb+");
        fseek(arq, meio * sizeof(Book), 0);
        fwrite(&vetorBooks[meio], sizeof(Book), 1, arq);
        fclose(arq);
        printf("Livro atualizada com sucesso no arquivo sorted.\n");
        return 0;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrada.\n");
        return 0;
      }
    }
    if (vetorBooks[meio].id < id) {
      // se menor, pega a metade direita do vetor
    } else { // do contrario, pega  a metade esquerda
      fim = meio - 1;
    }
  }
  printf("Livro nao encontrada.\n");
  return 0;
}

int updateSortedTxt(char *filename, Book update, int size) {
  Book *vetorBooks;
  FILE *arq;
  vetorBooks = createVetorBooksTxt(filename, size);
  int ini, fim, meio;
  ini = 0;
  fim = size - 1; // pega o fim do vetor
  while (ini <= fim) {
    meio = ini + (fim - ini) / 2; // calcula o meio do vetor
    if (vetorBooks[meio].id == update.id) {
      if (vetorBooks[meio].active == 1) {
        strcpy(vetorBooks[meio].title, update.title);
        strcpy(vetorBooks[meio].author, update.author);
        strcpy(vetorBooks[meio].genre, update.genre);
        vetorBooks[meio].qtdPag = update.qtdPag;
        vetorBooks[meio].price = update.price;
        printf("Livro atualizada com sucesso no arquivo sorted.\n");
        arq = fopen(filename, "w");
        for (int i = 0; i < size; i++) {
          fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", vetorBooks[i].id,
                  vetorBooks[i].qtdPag, vetorBooks[i].title,
                  vetorBooks[i].genre, vetorBooks[i].author,
                  vetorBooks[i].price, vetorBooks[i].active);
        }
        fclose(arq);
        return 0;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrada.\n");
        return 0;
      }
    }
    if (vetorBooks[meio].id < update.id) {
      ini = meio + 1; // se menor, pega a metade direita do vetor
    } else {          // do contrario, pega  a metade esquerda
      fim = meio - 1;
    }
  }
  printf("Livro nao encontrada.\n");
  return 0;
}
