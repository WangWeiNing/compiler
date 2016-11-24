#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

token* m_scan();
char peek;
int line;


int main()
{
	line = 0;
	peek = getchar();
	token* t = m_scan();
	printf("Tag %d\n", t->tag);
	token* t2 = m_scan();
	printf("Tag %d\n", t2->tag);
	char *str = (char*)t2->context;
	while(*str != '\0')
		putchar(*str++);
	printf("%d\n", *((int*)(t->context)));
	return 0;
}

token* m_scan()
{
	for(;;peek = getchar())
	{
		if(peek == '\t' || peek == ' ')
			continue;
		else if(peek == '\n')
			line++;
		else
			break;
	}

	if(ISDIGIT(peek))
	{
		int *v = malloc(sizeof(int));
		*v = 0;
		do
		{
			*v = 10 * (*v) + (peek - '0');
			peek = getchar();
		}while(ISDIGIT(peek));
		token *number = (token*)malloc(sizeof(token));
		number->context = v;
		number->proc = &proc_number;
		number->tag = NUMBER;
		return number;
	}
	if(ISLETTER(peek))
	{
		char *temp = (char*)malloc(sizeof(char) * 17);
		int i = 0;
		do
		{
			temp[i] = peek;
			peek = getchar();	
			i++;
		}while(ISLETTER(peek));
		temp[i] = '\0';
		token *word = (token*)malloc(sizeof(token));
		word->context = temp;
		word->proc = &proc_word;
		word->tag = WORD;
		return word;
	}
}

void proc_number(void* context){}
void proc_word(void* context){}