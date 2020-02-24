#include <stdio.h>
#include "malloc.h"

int main()
{
	char *p = malloc(sizeof(size_t));
	char *str = malloc(sizeof(char) * 100);

	for (size_t i = 0; i < 10; ++i) {
		str[i] = 'a';
	}

	*p = (char)69;

	printf("p: %p, *p: %c\n", p, *(p));
	printf("%s\n", str);

	return 0;
}
