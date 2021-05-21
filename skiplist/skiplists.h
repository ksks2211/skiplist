#pragma once

#define MAX_LEVEL 16

struct sl_node {
	int key;
	int value;
	struct sl_node* forward[1];//포인터 배열 , 가변 struct  메모리 할당 1번만 하면 된다. 
};

struct skiplists {
	int level;
	struct sl_node* header;
};


struct skiplists* skiplists_init();
struct sl_node* skiplists_search(struct skiplists* slist, int key);
int random_level();
int skiplists_insert(struct skiplists* slist, int key, int value);
int skiplists_delete(struct skiplists* slist, int key);
void skiplists_free(struct skiplists* slist);
void skiplists_print(struct skiplists* slist);