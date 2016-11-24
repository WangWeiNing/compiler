#include <stddef.h>
#include <stdlib.h>
#include "m_list.h"

void list_init(m_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
}

lnode* list_nxt(lnode *node)
{
	return node->next;
}

lnode* list_int(m_list *list, lnode *node, void *data)
{
	lnode *newNode = (lnode*)(malloc(sizeof(lnode)));
	newNode->data = data;
	if(node == NULL)
	{
		list->head = newNode;
		list->tail = newNode;
		list->count++;
	}else
	{
		node->next = newNode;
		list->tail = newNode;
		list->count++;
	}

	return newNode;
}

lnode* list_int_t(m_list *list, void *data)
{
	if(LHEAD(list) == NULL)
		return list_int(list, NULL, data);
	else
		return list_int(list, LTAIL(list), data);
}

void list_rem(m_list *list, lnode *node)
{
	if(node == NULL)
	{
		list->head = NULL;
		list->tail = NULL;
		list->count = 0;
	}else
	{
		lnode *rem_node = node->next;
		node->next = rem_node->next;
		list->tail = node->next;
		list->count--;
		free(rem_node);
	}
}