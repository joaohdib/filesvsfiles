#include "heap.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listHeapTxt(char *filename, int size) {
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  for (int i = 0; i < size; i++) { // percorre o vetor exibindo todos os livros
    printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
           "autor: %s\n",
           vetorBooks[i].id, vetorBooks[i].qtdPag, vetorBooks[i].price,
           vetorBooks[i].title, vetorBooks[i].genre, vetorBooks[i].author);
  }
  return;
}

void listHeapBin(char *filename, FileManager *manager) {
  FILE *file;
  for (int record_pos = 0; record_pos < manager->record_count; record_pos++) {

    int curr_page_id =
        record_pos / PAGE_SIZE; // calcula a pagina do livro desejado
    // printf("Page Num: %d\n", curr_page_id);
    int page_offset =
        curr_page_id * PAGE_SIZE *
        sizeof(Book); // calcula o offset em bytes da pagina do livro desejado
    // printf("Page Offset: %d\n", page_offset);
    int record_offset =
        record_pos % PAGE_SIZE *
        sizeof(Book); // calcula o offset em bytes do livro desejado na pagina
                      // calculada anteriormente
    // printf("Record Offset: %d\n", record_offset);

    Book *aux_record = (Book *)malloc(sizeof(Book));

    file = fopen(filename, "rb+");

    fseek(file, page_offset + record_offset,
          0); // posiciona o ponteiro na parte certa em bytes do arquivo
    fread(aux_record, sizeof(Book), 1, file);
    printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
           "autor: %s\n",
           aux_record->id, aux_record->qtdPag, aux_record->price,
           aux_record->title, aux_record->genre, aux_record->author);
  }

  fclose(file);
  return;
}

void createHeapBin(char *filename, FileManager *manager, Book *record) {
  FILE *file;
  int curr_page_id =
      manager->available_page_id; // pega o numero da pagina atual disponivel
  int curr_record_count =
      manager
          ->record_count; // pega quantos registros ja tem (livros existentes)

  file = fopen(filename, "rb+");
  record->id = manager->record_count;
  int page_offset = curr_page_id * PAGE_SIZE *
                    sizeof(Book); // calcula o offset da pagina em bytes
  int record_offset =
      (curr_record_count % PAGE_SIZE) *
      sizeof(Book); // calcula o offset dentro da pagina em bytes
  fseek(file, page_offset + record_offset, 0);
  fwrite(record, sizeof(Book), 1, file);

  manager->record_count += 1;
  if (manager->record_count % PAGE_SIZE == 0)
    manager->available_page_id += 1; // aumenta a pagina se precisar

  fclose(file);
}

void createHeapTxt(char *filename, int size, Book newBook) {
  FILE *arq;
  arq = fopen(filename, "a");
  if (arq == NULL) {
    return;
  }
  newBook.id = randomId();
  newBook.active = 1; // cria o livro com id aleatorio e adiciona ao arquivo
  fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", newBook.id, newBook.qtdPag,
          newBook.title, newBook.genre, newBook.author, newBook.price,
          newBook.active);
  fclose(arq);
  return;
}

void createHeapTxtTest(char *filename, int size, Book newBook) {
  FILE *arq;
  arq = fopen(filename, "a");
  if (arq == NULL) {
    return;
  }
  newBook.id = 2023;
  newBook.active = 1; // cria o livro com id fixo para testes e add no arquivo
  fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", newBook.id, newBook.qtdPag,
          newBook.title, newBook.genre, newBook.author, newBook.price,
          newBook.active);
  fclose(arq);
  return;
}

Book *readHeapBin(char *filename, FileManager *manager, int record_pos) {
  FILE *file;
  if (record_pos >= manager->record_count)
    return NULL; // se a record_pos for maior que o numero existentes de livro
                 // retorna nulo pra indicar problema

  int curr_page_id =
      record_pos / PAGE_SIZE; // calcula a pagina do livro desejado
  // printf("Page Num: %d\n", curr_page_id);
  int page_offset =
      curr_page_id * PAGE_SIZE *
      sizeof(Book); // calcula o offset em bytes da pagina do livro desejado
  // printf("Page Offset: %d\n", page_offset);
  int record_offset =
      record_pos % PAGE_SIZE *
      sizeof(Book); // calcula o offset em bytes do livro desejado na pagina
                    // calculada anteriormente
  // printf("Record Offset: %d\n", record_offset);

  Book *aux_record = (Book *)malloc(sizeof(Book));

  file = fopen(filename, "rb+");

  fseek(file, page_offset + record_offset,
        0); // posiciona o ponteiro na parte certa em bytes do arquivo
  fread(aux_record, sizeof(Book), 1, file);
  printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
         "autor: %s\n",
         aux_record->id, aux_record->qtdPag, aux_record->price,
         aux_record->title, aux_record->genre, aux_record->author);

  fclose(file);

  return aux_record;
}

void readHeapTxt(char *filename, int id, int size) {
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  for (int i = 0; i < size; i++) {
    if (vetorBooks[i].id == id &&
        vetorBooks[i].active ==
            1) { // percorre vetor procurando livro com id desejado
      printf("Id: %d, qtdPaginas: %d, preco: %f, titulo: %s, genero: %s, "
             "autor: %s\n",
             vetorBooks[i].id, vetorBooks[i].qtdPag, vetorBooks[i].price,
             vetorBooks[i].title, vetorBooks[i].genre, vetorBooks[i].author);
      return;
    }
  }
  printf("Livro nao encontrada\n");
  return;
}

Book *updateHeapBin(char *filename, FileManager *manager, int record_pos,
                    Book *updated_task) {
  FILE *file;
  if (record_pos >= manager->record_count)
    return NULL;

  int curr_page_id = record_pos / PAGE_SIZE; // calcula num da pagina
  // printf("Page Num: %d\n", curr_page_id);
  int page_offset = curr_page_id * PAGE_SIZE *
                    sizeof(Book); // calcula offset em bytes da pagina
  // printf("Page Offset: %d\n", page_offset);
  int record_offset =
      record_pos % PAGE_SIZE *
      sizeof(Book); // calcula offset em bytes do livro na pagina calculada
  // printf("Record Offset: %d\n", record_offset);

  Book *aux_record = (Book *)malloc(sizeof(Book));

  file = fopen(filename, "rb+");

  fseek(file, page_offset + record_offset, 0);
  fwrite(updated_task, sizeof(Book), 1, file);

  fclose(file);
  printf("Livro atualizada com sucesso no arquivo heap.\n");

  return aux_record;
}

void updateHeapTxt(char *filename, Book update, int size) {
  FILE *arq;
  int id = update.id;
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  for (int i = 0; i < size; i++) { // percorre vetor procurando id desejado
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
        printf("Livro atualizado com sucesso no arquivo heap.\n");
        return;
      } else { // nao tem como existir outra Livro com esse id e como o id ja
               // nao ta ativo, nao vale a pena continuar buscando
        printf("Livro nao encontrado ou inativo.\n");
        return;
      }
    }
  }
  printf("Livro nao encontrada\n");
  return;
}

Book *deleteHeapBin(char *filename, FileManager *manager, int record_pos) {
  FILE *file;
  if (record_pos >= manager->record_count)
    return NULL;

  int curr_page_id = record_pos / PAGE_SIZE; // calcula num da pagina
  // printf("Page Num: %d\n", curr_page_id);
  int page_offset = curr_page_id * PAGE_SIZE *
                    sizeof(Book); // calcula offset da pagina em bytes
  // printf("Page Offset: %d\n", page_offset);
  int record_offset = record_pos % PAGE_SIZE *
                      sizeof(Book); // calcula offset do livro dentro da pagina
  // printf("Record Offset: %d\n", record_offset);

  Book *aux_record = (Book *)malloc(sizeof(Book));

  file = fopen(filename, "rb+");

  fseek(file, page_offset + record_offset, 0);
  fread(aux_record, sizeof(Book), 1, file);
  fseek(file, page_offset + record_offset, 0);
  aux_record->id = -1;
  aux_record->active = 0;
  fwrite(aux_record, sizeof(Book), 1, file);

  fclose(file);
  printf("Livro deletada com sucesso no arquivo Heap.\n");

  return aux_record;
}

void deleteHeapTxt(char *filename, int id, int size) {
  Book *vetorBooks = createVetorBooksTxt(filename, size);
  int encontrado = 0;
  FILE *arq;
  for (int i = 0; i < size; i++) { // percorre vetor para achar livro com id
                                   // desejado e mudar o atributo active
    if (vetorBooks[i].id == id) {
      if (vetorBooks[i].active == 0) {
        printf("Livro nao encontrada\n");
        return;
      }
      vetorBooks[i].active = 0;
      encontrado = 1;
      arq = fopen(filename, "w");
      for (int i = 0; i < size; i++) {
        fprintf(arq, "%d,%d,%s,%s,%s,%f,%d\n", vetorBooks[i].id,
                vetorBooks[i].qtdPag, vetorBooks[i].title, vetorBooks[i].genre,
                vetorBooks[i].author, vetorBooks[i].price,
                vetorBooks[i].active);
      }
      fclose(arq);
      printf("Livro deletada com sucesso no arquivo heap.\n");
      return;
    }
  }
  if (encontrado == 0) {
    printf("Livro nao encontrada\n");
  }

  return;
}
