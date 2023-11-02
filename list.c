#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "objalloc.h"


struct list
{
  char **entry;
  int size;
  int last_index;
  struct objalloc *memory;
};

struct list* list_create(int size)
{
  struct list *ret = malloc(sizeof(struct list));
  if (ret == NULL)
    return NULL;

  ret->size = size;
  ret->last_index = -1;
  ret->memory = objalloc_create();
  ret->entry = objalloc_alloc(ret->memory, sizeof(void*) * size);
  return ret;
}

bool list_append(struct list *l, const char* str)
{
  if (l->last_index == l->size-1)
    return false;

  l->last_index ++;
  l->entry[l->last_index] = objalloc_alloc(l->memory, strlen(str));
  strcpy(l->entry[l->last_index], str);
  return true;
}

void list_print(struct list *l)
{
  int i;
  for (int i = 0; i <= l->last_index; i++)
    printf("list[%d] = %s\n", i, l->entry[i]);
}

void list_free(struct list *l)
{
  objalloc_free(l->memory);
  free(l);
}


int main()
{
  struct list *l = list_create(5);
  list_append(l, "hello");
  list_append(l, "world");
  list_print(l);
  list_free(l);
}
