#include <stdio.h>
#include <stdlib.h>
#include "carray.h"

CArray *getCArray(int size) {
  CArray *ca = (CArray *) (malloc(sizeof(CArray)));
  ca->array = (int *) malloc(sizeof(int) * size);
  ca->size = size;

  for (int i = 0; i < size; ++i) {
    ca->array[i] = i;
  }
  return ca;
}

int main() {
  int data[10];
  CArray c_array;
  c_array.array = data;
  c_array.size = 10;

  data[0] = 10;
  printf("%d\n", c_array.array[0]);

  int *array = (int *) malloc(sizeof(int) * 4);
  array[0] = 0;
  array[1] = 1;
  array[2] = 2;
  array[3] = 3;
  array[4] = 4;
  array[5] = 5;
  printf("==============\n");
  printf("%d\n", array[0]);
  printf("%d\n", array[1]);
  printf("%d\n", array[5]);

  CArray *cc = getCArray(3);
  printf("%d\n", cc->array[2]);
  printf("%d\n", cc->array[4]);
}