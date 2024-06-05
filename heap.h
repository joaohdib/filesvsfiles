#ifndef normalH
#define normalH
#include "task.h"

void listHeapTxt(char *filename, int size);
void createHeapBin(char *filename, FileManager *manager, Book *record);
void createHeapTxtTest(char *filename, int size, Book newBook);
void createHeapTxt(char *filename, int size, Book newBook);
Book *readHeapBin(char *filename, FileManager *manager, int record_pos);
void readHeapTxt(char *filename, int id, int size);
Book *updateHeapBin(char *filename, FileManager *manager, int record_pos,
                    Book *updated_task);
void updateHeapTxt(char *filename, Book update, int size);
Book *deleteHeapBin(char *filename, FileManager *manager, int record_pos);
void deleteHeapTxt(char *filename, int id, int size);
void listHeapBin(char *filename, FileManager *manager);

#endif