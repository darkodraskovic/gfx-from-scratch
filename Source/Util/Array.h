#ifndef ARRAY_H
#define ARRAY_H

#include <string.h>

#define ARRAY_SIZE(array) ((int*)array)[-1]

#define arrPush(array, value)                  \
  do {                                         \
    array = arrAlloc(array, 1, sizeof(value)); \
    array[ARRAY_SIZE(array)] = value;          \
    ARRAY_SIZE(array)++;                       \
  } while (0)

#define arrAppend(array, cArray, count)                                 \
  do {                                                                  \
    array = arrAlloc(array, count, sizeof(*cArray));                    \
    memcpy(array + ARRAY_SIZE(array), cArray, sizeof(*cArray) * count); \
    ARRAY_SIZE(array) += count;                                         \
  } while (0)

void* arrAlloc(void* array, int count, int itemSize);
void* arrCreate(int count, int itemSize);
void arrDestroy(void* array);

int arrSize(void* array);
int arrCap(void* array);

#endif
