#ifndef M_List
#define M_List
#define LHEAD(list) (list->head)
#define LTAIL(list) (list->tail)
#define LCOUNT(list)  (list->count)

typedef struct m_list_
{
	struct lnode_ *head;
	struct lnode_ *tail;
	int count;
}m_list;

typedef struct lnode_
{
	struct lnode_ *next;
	void *data;
}lnode;

void init_list(m_list *list);
lnode* list_nxt(lnode *node);
lnode* list_int(m_list *list, lnode *node, void *data);
lnode* list_int_t(m_list *list, void *data);
void list_rem(m_list *list, lnode *node);

#endif