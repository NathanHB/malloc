#include <stdio.h>
#include "malloc.h"

int main()
{
	size_t *p = malloc(sizeof(size_t));
	char *str = malloc(sizeof(char) * 100);

	for (size_t i = 0; i < 1000; ++i) {
		str[i] = 'a';
	}

	*p = 1000000000000;

	printf("p: %p, *p: %lu\n", p, *p);
	printf("%s\n", str);

	return 0;
}
