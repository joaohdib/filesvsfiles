#ifndef taskH
#define taskH
#define PAGE_SIZE 5

typedef struct book {
  int id;
  int qtdPag;
  float price;
  char title[64];
  char genre[32];
  char author[32];
  int active;

} Book;

struct fileManager {
  int available_page_id;
  int record_count;
};

typedef struct fileManager FileManager;

Book *createVetorBooks(char *filename, int size);
Book *createVetorBooksTxt(char *filename, int size);
int compfunc(const void *t1, const void *t2);
int randomId();
int get_file_sizeBin(char *filename);
int get_file_sizeTxt(char *filename);

#endif