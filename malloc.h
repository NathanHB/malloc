#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>

struct chunk {
  struct chunk *next, *prev;
  size_t        size;
  long          free;
  void         *data;
};

void zerofill(void *ptr, size_t len);
void *malloc(size_t size);
void wordcpy(void *dst, void *src, size_t len);

#endif /* ifndef MALLOC_H
 */
