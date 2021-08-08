#ifndef __PROJ07_INTLIST_H__INCLUDED__
#define __PROJ07_INTLIST_H__INCLUDED__
#include <stdio.h>

typedef struct StrList StrList;
struct StrList
{
	char    *val;
	StrList *next;
};


/* ---- YOU MUST IMPLEMENT THESE FUNCTIONS ---- */

StrList *readInput  (         FILE*);
int      getLen     (StrList*);
void     writeOutput(StrList*,FILE*);
void     freeList   (StrList*);
char	*readLongStr(FILE*);
#endif
