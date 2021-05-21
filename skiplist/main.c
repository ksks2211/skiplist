#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skiplists.h"




int main() {
	
	
	int key, value;

	struct skiplists* list = skiplists_init();

	for (int i = 0; i < 5; i++) {
		printf("Key and Value ( e.g. 10 11) :");
		scanf("%d%d", &key, &value);
		skiplists_insert(list, key, value);
	}
	printf("Result : ");
	skiplists_print(list);
	
	skiplists_free(list);
	return 0;
}
