#include "Array.h"

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_RAW_DATA(array) ((int*)(array)-2)
#define ARRAY_CAPACITY(array) ((int*)array)[-2]

void* arrAlloc(void* array, int count, int itemSize) {
  if (array == NULL) {
    int* base = (int*)malloc(sizeof(int) * 2 + itemSize * count);
    base[0] = count;  // capacity
    base[1] = 0;      // size
    return base + 2;  // logical index 0
  } else if (ARRAY_SIZE(array) + count <= ARRAY_CAPACITY(array)) {
    return array;
  } else {
    int demandedSize = ARRAY_SIZE(array) + count;
    int doubleSize = ARRAY_CAPACITY(array) * 2;
    int capacity = demandedSize > doubleSize ? demandedSize : doubleSize;
    int* base = (int*)realloc(ARRAY_RAW_DATA(array),
                              sizeof(int) * 2 + itemSize * capacity);
    base[0] = capacity;
    return base + 2;
  }
}

void* arrCreate(int capacity, int itemSize) {
  return arrAlloc(NULL, capacity, itemSize);
};

void arrDestroy(void* array) {
  if (array != NULL) {
    free(ARRAY_RAW_DATA(array));
  }
}

int arrSize(void* array) { return (array != NULL) ? ARRAY_SIZE(array) : 0; }

int arrCap(void* array) { return (array != NULL) ? ARRAY_CAPACITY(array) : 0; }
