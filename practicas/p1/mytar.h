#ifndef _MYTAR_H
#define _MYTAR_H

#include <limits.h>

typedef enum{
  NONE,
  ERROR,
  CREATE,
  EXTRACT,
  REVERSE,
  EXTRACTREVERSE
} flags;

typedef struct {
  char* name;
  unsigned int size;
} stHeaderEntry;

int createTar(int nFiles, char *fileNames[], char tarName[]);
int extractTar(char tarName[]);
int createReverseTar(int nFiles, char *fileNames[], char tarName[]);
int extractReverse(char tarName[]);
#endif /* _MYTAR_H */
