#include <stdio.h>
#include <stdlib.h>
#include "m_hash.h"


void hash_init(m_hash *hash, int size)
{
	hash->buckets = size;
	hash->count = 0;
	m_list *tables;
	if((tables = (m_list*)(malloc( size * sizeof(m_list)))) == NULL) exit(2);
	for(int i = 0; i < size; i++)
		list_init(&tables[i]);
	hash->tables = tables;
}

void* hash_look(m_hash *hash, int key)
{
	int h = get_hash(hash, key);
	m_list *table = (hash->tables + h);

	lnode *node = NULL;
	hnode *d = NULL;
	if(LCOUNT(table) > 1)
		for(node = LHEAD(table); node != NULL; node = list_nxt(node))
		{
			d = (hnode *)(node->data);
			if(d->key == key)
				return d->data;
		}
	else
		return ((hnode *)(LHEAD(table)->data))->data;
}

void hash_int(m_hash *hash, int key, void *data)
{
	hnode *node = (hnode*)malloc(sizeof(hnode));
	node->key = key;
	node->data = data;
	int h = get_hash(hash, key);
	m_list *table = (hash->tables + h);
	list_int_t(table, node);
	hash->count++;
}

void hash_rem(m_hash *hash, int key)
{
	if(hash_look(hash, key) == NULL) return NULL;

	int h = get_hash(hash, key);
	m_list *table = (hash->tables + h);
	if(LCOUNT(table) > 1)
	{
		lnode *prev = NULL;
		lnode *node = NULL;
		for(node = LHEAD(table); node != NULL; node = list_nxt(node))
		{
			if( ((hnode*)(node->data))->key == key)
			{
				list_rem(table, prev);
				break;
			}
			prev = node;
		}
	}
	else 
		list_rem(table, NULL);
	hash->count--;
}


int get_hash(m_hash *hash, int number)
{
	return number % hash->buckets;
}
