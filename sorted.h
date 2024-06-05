#ifndef sortedH
#define sortedH
#include "task.h"

int listSortedBin(char *filename, int size);
int listSortedTxt(char *filename, int size);
int readSortedTxt(char *filename, int id, int size);
int readSortedBin(char *filename, int id, int size);
int createSortedBin(char *filename, int size, Book newTask);
int createSortedTxt(char *filename, int size, Book newTask);
int createSortedBinTest(char *filename, int size, Book newTask);
int createSortedTxtTest(char *filename, int size, Book newTask);
int deleteSortedBin(char *filename, int id, int size);
int deleteSortedTxt(char *filename, int id, int size);
int updateSorted(char *filename, Book update, int size);
int updateSortedTxt(char *filename, Book update, int size);

#endif