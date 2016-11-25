#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lexer.h"
#include "m_hash.h"

char peek;
int line;
m_hash* words;

char next();
char prev();
token* m_scan();
int strhash(m_hash* hash, char* str);
void init_keyword();

int main()
{

	line = 0;
	words = (m_hash*)malloc(sizeof(m_hash));
	hash_init(words, 31);
	init_keyword();
	peek = getchar();
	token* t = m_scan();
	printf("Tag %d\n", t->tag);
	token* t2 = m_scan();
	printf("Tag %d\n", t2->tag);
	token* t3 = m_scan();
	printf("Tag %d\n", t3->tag);
	char* data = (char*)t3->context;
	return 0;
}

int strhash(m_hash* hash, char* str)
{
	int temp = 0;
	while(*str)
		temp = temp * 32 + *str++;

	return temp % hash->buckets;
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

	if(peek == '/')
	{
		printf("2");
		if((peek = getchar()) == '/')
		{
			for(; ; peek = getchar())
				if(peek == '\n')
				{
					peek = getchar();
					break;
				}else
					continue;
		}else
			lseek(0, -1, SEEK_CUR);
	}
	printf("3");

	if(ISDIGIT(peek))
	{
		printf("4");
		int *v = malloc(sizeof(int));
		*v = 0;
		do
		{
			*v = 10 * (*v) + (peek - '0');
			peek = getchar();
		}while(ISDIGIT(peek));
		token *number = (token*)malloc(sizeof(token));
		number->context = v;
		number->proc = &proc_num;
		number->tag = NUM;
		return number;
	}
	if(ISLETTER(peek))
	{
		char *temp = (char*)malloc(sizeof(char) * 17);
		memset(temp, 0, 17);
		int i = 0;
		do
		{
			temp[i] = peek;
			peek = getchar();	
			i++;
		}while(ISLETTER(peek));

		int* keyword;
		if((keyword = (int*)hash_look(words, strhash(words, temp))) != NULL)
		{
			token *word = (token*)malloc(sizeof(token));
			word->context = keyword;
			word->proc = &proc_word;
			word->tag = *keyword;
			return word;
		}
		token *word = (token*)malloc(sizeof(token));
		hash_int(words, strhash(words, temp), ID);
		word->context = temp;
		word->proc = &proc_word;
		word->tag = ID;
		return word;
	}

	token *symbol = (token*)malloc(sizeof(token));
	memset(symbol, 0, sizeof(token));
	symbol->context = &peek;
	symbol->proc = &proc_id;
	symbol->tag = peek;
	peek = ' ';
	return symbol;
}


void init_keyword()
{
	token* trueK = (token*)malloc(sizeof(token));
	trueK->tag = TRUE;
	trueK->context = "true";
	trueK->proc = &proc_id;
	hash_int(words, strhash(words, "false"), &trueK);

	token* falseK = (token*)malloc(sizeof(token));
	falseK->tag = FALSE;
	falseK->context = "false";
	falseK->proc = &proc_id;
	hash_int(words, strhash(words, "false"), &falseK);
}


void proc_num(void* context){}
void proc_word(void* context){}
void proc_id(void* context){}
