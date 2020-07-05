#include<stdlib.h>
#include<stdio.h>
#include"skiplists.h"


struct skiplists* skiplists_init() {
	int i;
	struct skiplists *slist;
	struct sl_node* header;

	slist = (struct skiplists*)malloc(sizeof(struct skiplists));
	if (slist == NULL)return NULL;

	header = (struct sl_node*)malloc(sizeof(struct sl_node) + sizeof(struct sl_node*) * MAX_LEVEL);
	if (header == NULL) {
		free(slist);
		return NULL;
	}

	header->key = INT_MAX;
	header->value = INT_MAX;

	slist->header = header;

	struct sl_node* tmp;
	tmp = slist->header;

	for (i = 0; i <= MAX_LEVEL; i++) {
		header->forward[i] = slist->header;
	}

	slist->level = 1;

	return slist;
}

struct sl_node* skiplists_search(struct skiplists* slist, int key) {
	int i;

	struct sl_node* x = slist->header;


	for (i = slist->level; i >= 1; i--) {
		while (x->forward[i]->key < key)
			x = x->forward[i];
	}

	if (x->forward[1]->key == key) {
		return x->forward[1];
	}

	return NULL;
}

int random_level() {
	int level = 1;
	while (rand() < RAND_MAX / 2 && level < MAX_LEVEL)level++;

	return level;
}

int skiplists_insert(struct skiplists* slist, int key, int value) {
	int i, level;


	struct sl_node* update[MAX_LEVEL + 1];
	

	
	struct sl_node *x= (slist->header);
	
	for (i = slist->level; i >= 1; i--) {
		while (x->forward[i]->key < key)
			x = x->forward[i];
		update[i] = x;
	}

	x = x->forward[1];

	if (key == x->key) {
		x->value = value;
		return 1; // value updated
	}


	level = random_level();
	if (level > slist->level) {
		for (i = slist->level + 1; i <= level; i++) {
			update[i] = slist->header;
		}
		slist->level = level;
	}

	x = (struct sl_node*)malloc(sizeof(struct sl_node) + sizeof(struct sl_node*) * level);
	x->key = key;
	x->value = value;
	for (i = 1; i <= level; i++) {
		x->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = x;
	}


	return 0;// new key-value pair inserted
}


int skiplists_delete(struct skiplists* slist, int key) {
	int i;
	struct sl_node* update[MAX_LEVEL + 1];
	struct sl_node* x = slist->header;

	for (i = slist->level; i >= 1; i--) {
		while (x->forward[i]->key < key) {
			x = x->forward[i];
		}
		update[i] = x;
	}

	x = x->forward[1];

	if (x->key == key) {
		for (i = 1; i <= slist->level; i++) {
			if (update[i]->forward[i] != x)break;
			update[i]->forward[i] = x->forward[i];
		}
		free(x);

		while (slist->level > 1 && slist->header->forward[slist->level] == slist->header) {
			slist->level--;
		}
		return 1;
	}


	return 0;

}


void skiplists_free(struct skiplists* slist)
{
	struct sl_node* cur_node = slist->header->forward[1];
	while (cur_node != slist->header) {
		struct sl_node* temp = cur_node->forward[1];
		free(cur_node);
		cur_node = temp;
	}
	free(cur_node);
	free(slist);
}


void skiplists_print(struct skiplists* slist) {
	struct sl_node* x;

	x = slist->header;
	while (x != NULL && x->forward[1] != slist->header) {
		x = x->forward[1];
		printf("(key,value)-(%d,%d) ", x->key,x->value);
	}
	printf("\n");
}