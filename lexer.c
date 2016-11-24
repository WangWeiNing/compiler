#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "m_hash.h"

token* m_scan();
char peek;
int line;
m_hash* words;

int strhash(m_hash* hash, char* str);

int main()
{
	line = 0;
	words = (m_hash*)malloc(sizeof(m_hash));
	hash_init(words, 31);
	char* trueWord = "true";
	hash_int(words, strhash(words, trueWord), trueWord);
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
		memset(temp, 0, 17);
		int i = 0;
		do
		{
			temp[i] = peek;
			peek = getchar();	
			i++;
		}while(ISLETTER(peek));

		void* keyword;
		if((keyword = hash_look(words, strhash(words, temp))) != NULL)
		{
			token *word = (token*)malloc(sizeof(token));
			word->context = keyword;
			word->proc = &proc_word;
			word->tag = KEYWORD;
			return word;
		}
		token *word = (token*)malloc(sizeof(token));
		word->context = temp;
		word->proc = &proc_word;
		word->tag = WORD;
		return word;
	}

	token *symbol = (token*)malloc(sizeof(token));
	symbol->context = &peek;
	symbol->proc = &proc_symbol;
	symbol->tag = SYMBOL;
	peek = ' ';
	return symbol;
}

void proc_number(void* context){}
void proc_word(void* context){}
void proc_symbol(void* context){}
