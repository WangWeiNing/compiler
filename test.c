#include <stdio.h>
#include <stdlib.h>
#include "m_list.h"
#include "m_hash.h"

#define ISDIGIT(N) (N >= 48 && N <= 57)
#define true 1

char lookahead;
int line;
// int main()
// {
// 	m_hash *table = (m_hash*)(malloc(sizeof(m_hash)));
// 	hash_init(table, 4);
// 	int data1 = 10;
// 	int data2 = 20;
// 	int data3 = 30;
// 	int data4 = 40;
// 	int data5 = 50;
// 	int data6 = 60;
// 	int data7 = 70;
// 	int data8 = 80;
// 	int data9 = 90;
// 	int data10 = 100;
// 	hash_int(table, 1, &data1);
// 	hash_int(table, 2, &data2);
// 	printf("hash count %d\n", table->count);
// 	hash_int(table, 3, &data3);
// 	hash_int(table, 4, &data4);
// 	hash_int(table, 5, &data5);
// 	hash_int(table, 6, &data6);
// 	hash_int(table, 7, &data7);
// 	hash_int(table, 8, &data8);
// 	hash_int(table, 9, &data9);
// 	hash_int(table, 10, &data10);
// 	printf("hash count %d\n", table->count);
// 	printf("key 1 data %d\n", *((int*)(hash_look(table, 1))));
// 	printf("key 2 data %d\n", *((int*)(hash_look(table, 2))));
// 	printf("key 3 data %d\n", *((int*)(hash_look(table, 3))));
// 	printf("key 4 data %d\n", *((int*)(hash_look(table, 4))));
// 	printf("key 5 data %d\n", *((int*)(hash_look(table, 5))));
// 	printf("key 6 data %d\n", *((int*)(hash_look(table, 6))));
// 	printf("key 7 data %d\n", *((int*)(hash_look(table, 7))));
// 	printf("key 8 data %d\n", *((int*)(hash_look(table, 8))));
// 	printf("key 9 data %d\n", *((int*)(hash_look(table, 9))));
// 	printf("key 10 data %d\n", *((int*)(hash_look(table, 10))));
// 	printf("key 5 data %d\n", *((int*)(hash_look(table, 5))));
// 	hash_rem(table, 5);
// 	if(hash_look(table, 5) == NULL) printf("ok\n");
// 	printf("hash count %d\n", table->count);

// 	// m_list *list = (m_list*)(malloc(sizeof(m_list)));
// 	// list_init(list);
// 	// int n1 = 10;
// 	// int n2 = 11;
// 	// int n3 = 12;
// 	// int n4 = 13;
// 	// int n5 = 14;
// 	// lnode *node1 = list_int(list, NULL, &n1);
// 	// lnode *node2 = list_int(list, node1, &n2);
// 	// lnode *node3 = list_int(list, node2, &n3);
// 	// lnode *node4 = list_int(list, node3, &n4);
// 	// printf("Node count %d\n", list->count);
// 	// printf("head data %d\n", *((int*) (LHEAD(list)->data)));
// 	// printf("tail data %d\n", *((int*) (LTAIL(list)->data)));
// 	// printf("Node count %d\n", list->count);
// 	// list_rem(list, node3);
// 	// list_int_t(list, &n5);
// 	// printf("tail data %d\n", *((int*) (LTAIL(list)->data)));
// 	// printf("Node count %d\n", list->count);
// 	// lookahead = getchar();
// 	// line = 0;
// 	// expr();
// 	return 0;
// }

void term()
{
	if(ISDIGIT(lookahead))
	{
		putchar(lookahead);
		m_match(lookahead);
	}else
		exit(2);
}

// void rest()
// {
// 	switch(lookahead)
// 	{
// 		case '+':
// 			m_match('+');
// 			term();
// 			putchar('+');
// 			rest();
// 			break;
// 		case '-':
// 			m_match('-');
// 			term();
// 			putchar('-');
// 			rest();
// 			break;
// 		default:
// 			return;
// 	}
// }

void expr()
{
	term();
	while(true)
	{
		switch(lookahead)
		{
			case '+':
				m_match('+');
				term();
				putchar('+');
				continue;
			case '-':
				m_match('-');
				term();
				putchar('-');
				continue;
			default:
				return;
		}
	}
}

void m_match(char t)
{
	if(t == lookahead)
	{
		while(true)
		{
			lookahead = getchar();
			if(lookahead == ' ' || lookahead == '\t')
				continue;
			else if(lookahead == '\n')
				line++;
			else
				break;
		}
	}
	else exit(2);
}
