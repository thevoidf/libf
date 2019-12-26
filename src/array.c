#include "array.h"

#include <stdio.h>
#include <stdlib.h>

lowg_array_t* lowg_array_new()
{
  lowg_array_t *array = malloc(sizeof(lowg_array_t));

  array->size = 0;
  array->alloc = sizeof(void*) * DEFAULT_SIZE;
  array->array = malloc(array->alloc);

  return array;
}

void lowg_array_add(lowg_array_t* array, void* value)
{
  unsigned int mem_size = array->alloc / sizeof(void*);
  if (array->size == mem_size) {
    array->alloc = array->alloc * 2;
    array->array = realloc(array->array, array->alloc);
  }
  array->array[array->size++] = value;
}

void lowg_array_remove(lowg_array_t *array, unsigned int idx)
{
  array->array[idx] = NULL;

  void **new_array = malloc(array->alloc);
  int j = 0;
  for (int i = 0; i < array->size; i++) {
    if (array->array[i] != NULL) {
      new_array[j] = array->array[i];
      j++;
    }
  }

  free(array->array);
  array->array = new_array;
  array->size--;
}

unsigned int lowg_array_size(lowg_array_t *array)
{
  return array->size;
}

void* lowg_array_get(lowg_array_t *array, unsigned int idx)
{
  if (idx >= array->size) {
    fprintf(stderr, "Error: array out of index. size: %d, index: %d\n", array->size, idx);
    return NULL;
  }
  return array->array[idx];
}

void lowg_array_free(lowg_array_t* array)
{
  free(array->array);
  free(array);
}
