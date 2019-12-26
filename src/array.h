#ifndef LOWG_ARRAY_H
#define LOWG_ARRAY_H

#define DEFAULT_SIZE 10

typedef struct lowg_array_t {
  unsigned int alloc;
  unsigned int size;
  void **array;
} lowg_array_t;

lowg_array_t* lowg_array_new();
void lowg_array_add(lowg_array_t* array, void* value);
void lowg_array_remove(lowg_array_t *array, unsigned int idx);
unsigned int lowg_array_size(lowg_array_t *array);
void* lowg_array_get(lowg_array_t *array, unsigned int idx);
void lowg_array_free(lowg_array_t* array);

#endif
