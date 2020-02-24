#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

/* align n so that it is a multiple of the size of a pointer (sizeof(size_t)) */
static inline size_t word_aligne(size_t n)
{
    return ((n &= ~(sizeof(size_t) - 1)) + sizeof(size_t));
}

/* zerofill(ptr, len): write len 0 bytes at the address ptr */
void zerofill(void *ptr, size_t len)
{
    for (size_t *i = ptr; i - (size_t *)ptr < (long int)len; ++i)
        i = 0;
}

/* wordcpy(dst, src, len) copy len bytes from src to dst */
void wordcpy(void *dst, void *src, size_t len)
{
    // We dont know what type we work with but we only work with len
    // divisible by sizeof(size_t). thats why we cast the void * into
    // size_t *
    for (size_t i = 0; i < len; ++i)
        ((size_t *)dst)[i] = ((size_t *)src)[i];
}

/* Get the sentinel of the chunks */
static struct chunk* get_base(void)
{
    static struct chunk *base = NULL;

    if (base == NULL) {
        base = (struct chunk *)sbrk(0);
        sbrk(sizeof(struct chunk));
        base->next = NULL;
        base->prev = NULL;
        base->size = 0;
        base->free = -1;
    }

    return base;
}

/* extend_heap(last, size) extends the heap with a new chunk containing a data
 * block of size bytes.
 * Return 1 in case of success, and return 0 if sbrk(2) fails. */
static int extend_heap(struct chunk *last, size_t size)
{
    last->next = (struct chunk *)sbrk(sizeof(struct chunk));
    struct chunk *new = last->next;

    if (last->next == (void *) -1)
        return 0;

    new->data = (void *)sbrk(size);
    if (new->data == (void *) -1)
        return 0;

    new->next = NULL;
    new->prev = last;
    new->size = size;
    new->free = -1;

    return 1;
}

/* returns the first free chunck with size >= size */
static struct chunk* find_chunk(size_t size)
{
    struct chunk *previous = get_base();

    while (previous -> next != NULL) {
        if (previous->next->size >= size && previous->next->free > 0)
            return previous;
        previous = previous->next;
    }

    return previous;
}

/* return the chunk corresponding to the data pointer passed in argument or NULL
 * if none is find */
static struct chunk* get_chunk(void *p)
{
    if (p == NULL || (size_t)p != word_aligne((size_t)p))
        goto end;
    if ((struct chunk *)p < get_base() || p > sbrk(0))
        goto end;

    struct chunk *current = get_base();

    while (current != NULL) {
        if (current->data == p)
            return current;
    }

end:
    return NULL;
}

/* allign the size to be workable try and find a free chunk or extend the heap
 * andmark it as not free (free > 0) then return the data pointer of the chunk */
void *malloc(size_t size)
{
    size = word_aligne(size);
    struct chunk *place = find_chunk(size);

    if (place->next == NULL) {
        if (extend_heap(place, size) == 0)
            return NULL;
        return place->next->data;
    }

    return place->data;
}

/* finds the chunk corresponding to the pointer and marks it as free */
void free(void *pointer)
{
    struct chunk *pointerChunk = get_chunk(pointer);
    pointerChunk->free = 1;
}
