
#ifndef MATH_H
#define MATH_H

#include "linkedList.h"

typedef struct {
    double distance;
    char* name1;
    char* name2;
    int combinedCount;
} JSDResult;

void wfd(List** ,int);
void looper(List**, int);
void jsd(List* , List* );
int compareResults(const void* a, const void* b);

#endif