#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>

struct chunk {
  struct chunk *next, *prev;
  size_t        size; // size of the data stored.
  long          free; // free <= 0 if not free.
  void         *data; // pointer to where the actual data of the pointer is stocked.
};

void zerofill(void *ptr, size_t len);
void *malloc(size_t size);
void wordcpy(void *dst, void *src, size_t len);

#endif /* ifndef MALLOC_H
 */
