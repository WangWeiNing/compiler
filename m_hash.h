#ifndef M_HASH
#define M_HASH
#include "m_list.h"

typedef struct m_hash_
{
	int count;
	int buckets;
	m_list *tables;
}m_hash;

typedef struct hnode_
{
	int key;	
	void *data;
} hnode;

void hash_init(m_hash *hash, int size);
void hash_int(m_hash *hash, int key, void *data);
void* hash_look(m_hash *hash, int key);
void hash_rem(m_hash *hash, int key);
int get_hash(m_hash *hash, int number);

#endif