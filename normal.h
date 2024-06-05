#ifndef normalH
#define normalH
#include "task.h"

int readBin(char *filename, int id, int size);
int createBin(char *filename, int size, Book newBook);
int createTestBin(char *filename, int size, Book newBook);
int deleteeBin(char *filename, int id, int size);
int updateBin(char *filename, Book update, int size);
int listBin(char *filename, int size);
int readTxt(char *filename, int id, int size);
int createTxt(char *filename, int size, Book newBook);
int createTestBTxt(char *filename, int size, Book newBook);
int deleteeTxt(char *filename, int id, int size);
int updateTxt(char *filename, Book update, int size);
int listTxt(char *filename, int size);

#endif