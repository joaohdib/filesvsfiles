#include "normal.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int listBin(char *filename, int size) {
  Book *vetorBooks = createVetorBooks(filename, size);
  for (int i = 0; i < size; i++) { // percorre o vetor com os livros e os exibe
    if (vetorBooks[i].active == 1) {
      printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
             "autor: %s\n",
             vetorBooks[i].id, vetorBooks[i].qtdPag, vetorBooks[i].price,
             vetorBooks[i].title, vetorBooks[i].genre, vetorBooks[i].author);
    }
  }
  return 0;
}

int readBin(char *filename, int id, int size) {
  Book *vetorBooks = createVetorBooks(filename, size);
  for (int i = 0; i < size; i++) { // percorre o vetor com os livros e os exibe
    if (vetorBooks[i].id == id) {
      printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
             "autor: %s\n",
             vetorBooks[i].id, vetorBooks[i].qtdPag, vetorBooks[i].price,
             vetorBooks[i].title, vetorBooks[i].genre, vetorBooks[i].author);
      return 0;
    }
  }
  printf("Livro nao encontrada\n");
  return 0;
}

int createBin(char *filename, int size, Book newBook) {
  FILE *arq;
  arq = fopen(filename, "ab+"); // abre o arquivo no modo concatenacao, pega o
                                // id aleatorio e adiciona o livro neke
  if (arq == NULL) {
    return -1;
  }
  newBook.id = randomId();
  newBook.active = 1;
  fwrite(&newBook, sizeof(Book), 1, arq);
  fclose(arq);
  return 0;
}

int createTestBin(char *filename, int size, Book newBook) {
  FILE *arq;
  arq = fopen(filename, "ab+"); // abre o arquivo no modo concatenacao, pega o
                                // id fixo (para testes) e adiciona o livro nele
  if (arq == NULL) {
    return -1;
  }
  newBook.id = 2023;
  newBook.active = 1;
  fwrite(&newBook, sizeof(Book), 1, arq);
  fclose(arq);
  return 0;
}

int deleteeBin(char *filename, int id, int size) {
  Book *vetorBooks = createVetorBooks(filename, size);
  int encontrado = 0;
  FILE *arq;
  for (int i = 0; i < size; i++) { // percorre o vetor com os livros e muda o
                                   // atributo active do livro
    if (vetorBooks[i].id == id) {
      if (vetorBooks[i].active == 0) {
        printf("Livro nao encontrada\n");
        return 0;
      }
      vetorBooks[i].active = 0;
      encontrado = 1;
      arq = fopen(filename, "wb");
      fwrite(vetorBooks, sizeof(Book), size, arq);
      fclose(arq);
      printf("Livro deletada com sucesso no arquivo normal.\n");
      return 0;
    }
  }
  if (encontrado == 0) {
    printf("Livro nao encontrada\n");
  }

  return 0;
}

int updateBin(char *filename, Book update, int size) {
  FILE *arq;
  int id = update.id;
  Book *vetorBooks = createVetorBooks(filename, size);
  for (int i = 0; i < size; i++) { // percorre o vetor com os livros e muda o
                                   // atributo active do livro
    if (vetorBooks[i].id == id) {
      if (vetorBooks[i].active == 1) {
        strcpy(vetorBooks[i].title, update.title);
        strcpy(vetorBooks[i].author, update.author);
        strcpy(vetorBooks[i].genre, update.genre);
        vetorBooks[i].qtdPag = update.qtdPag;
        vetorBooks[i].price = update.price;
        arq = fopen(filename, "rb+");
        fseek(arq, i * sizeof(Book), 0);
        fwrite(&vetorBooks[i], sizeof(Book), 1, arq);
        free(vetorBooks);
        fclose(arq);
        printf("Livro atualizado com sucesso no arquivo normal.\n");
        return 0;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrado ou inativo.\n");
        return 0;
      }
    }
  }
  printf("Livro nao encontrada\n");
  return 0;
}

int listTxt(char *filename, int size) {
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  for (int i = 0; i < size; i++) { // percorre o vetor e lista os livros
    printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
           "autor: %s\n",
           vetorBooks[i].id, vetorBooks[i].qtdPag, vetorBooks[i].price,
           vetorBooks[i].title, vetorBooks[i].genre, vetorBooks[i].author);
  }
  return 0;
}

int readTxt(char *filename, int id, int size) {
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  for (int i = 0; i < size; i++) { // percorre o vetor e lista os livros
    if (vetorBooks[i].id == id && vetorBooks[i].active == 1) {
      printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
             "autor: %s\n",
             vetorBooks[i].id, vetorBooks[i].qtdPag, vetorBooks[i].price,
             vetorBooks[i].title, vetorBooks[i].genre, vetorBooks[i].author);
      return 0;
    }
  }
  printf("Livro nao encontrada\n");
  return 0;
}

int createTxt(char *filename, int size, Book newBook) {
  FILE *arq;
  arq = fopen(filename, "a"); // abre o arquivo no modo concatenacao e adiciona
                              // o livro a ele com id aleatorio
  if (arq == NULL) {
    return -1;
  }
  newBook.id = randomId();
  newBook.active = 1;
  fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", newBook.id, newBook.qtdPag,
          newBook.title, newBook.genre, newBook.author, newBook.price,
          newBook.active);
  fclose(arq);
  return 0;
}

int createTestTxt(char *filename, int size, Book newBook) {
  FILE *arq;
  arq = fopen(filename, "a"); // abre o arquivo no modo concatenacao e adiciona
                              // o livro a ele com id fixo (para testes)
  if (arq == NULL) {
    return -1;
  }
  newBook.id = 2023;
  newBook.active = 1;
  fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", newBook.id, newBook.qtdPag,
          newBook.title, newBook.genre, newBook.author, newBook.price,
          newBook.active);
  fclose(arq);
  return 0;
}

int updateTxt(char *filename, Book update, int size) {
  FILE *arq;
  int id = update.id;
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  for (int i = 0; i < size;
       i++) { // percorre o vetor e quando achar o livro com o id desejado
              // atualiza ele para o novo livro
    if (vetorBooks[i].id == id) {
      if (vetorBooks[i].active == 1) {
        strcpy(vetorBooks[i].title, update.title);
        strcpy(vetorBooks[i].author, update.author);
        strcpy(vetorBooks[i].genre, update.genre);
        vetorBooks[i].qtdPag = update.qtdPag;
        vetorBooks[i].price = update.price;
        arq = fopen(filename, "w");
        for (int i = 0; i < size; i++) {
          fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", vetorBooks[i].id,
                  vetorBooks[i].qtdPag, vetorBooks[i].title,
                  vetorBooks[i].genre, vetorBooks[i].author,
                  vetorBooks[i].price, vetorBooks[i].active);
        }
        free(vetorBooks);
        fclose(arq);
        printf("Livro atualizado com sucesso no arquivo normal.\n");
        return 0;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrado ou inativo.\n");
        return 0;
      }
    }
  }
  printf("Livro nao encontrada\n");
  return 0;
}

int deleteeTxt(char *filename, int id, int size) {
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  int encontrado = 0;
  FILE *arq;
  for (int i = 0; i < size;
       i++) { // percorre o vetor e quando achar o livro com o id desejado
    // deleta ele mudando o atributo active
    if (vetorBooks[i].id == id) {
      if (vetorBooks[i].active == 0) {
        printf("Livro nao encontrada\n");
        return 0;
      }
      vetorBooks[i].active = 0;
      encontrado = 1;
      arq = fopen(filename, "w");
      for (int i = 0; i < size; i++) {
        fprintf(arq, "%d,%d,%s,%s,%s,%f\n", vetorBooks[i].id,
                vetorBooks[i].qtdPag, vetorBooks[i].title, vetorBooks[i].genre,
                vetorBooks[i].author, vetorBooks[i].price);
      }
      fclose(arq);
      printf("Livro deletada com sucesso no arquivo normal.\n");
      return 0;
    }
  }
  if (encontrado == 0) {
    printf("Livro nao encontrada\n");
  }

  return 0;
}