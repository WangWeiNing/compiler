#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
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
token* scan_digit();
token* scan_letter();

int main()
{

	line = 0;
	words = (m_hash*)malloc(sizeof(m_hash));
	hash_init(words, 31);
	init_keyword();
	peek = getchar();
	token* t = m_scan();
	printf("Tag %f\n", *(double*)(t->context));
	token* t2 = m_scan();
	printf("Tag %d\n", t2->tag);
	token* t4 = m_scan();
	printf("Tag %f\n", *(double*)(t4->context));
	// char* data = (char*)t3->context;
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
	// comment
	if(peek == '/')
	{
		peek = getchar();
		if(peek == '/')
		{
			for(; ; peek = getchar())
				if(peek == '\n')
				{
					peek = getchar();
					break;
				}else
					continue;
		}
		else if(peek == '*')
		{
			for(;;peek = getchar())
				if(peek == '*' && (peek = getchar()) == '/')
					break;
				else
					continue;
		}
		else 
		{
			printf("syntax error line:%d %c\n", line, peek);
			exit(1);
		}
		peek =  getchar();
	}

	if(ISDIGIT(peek))
		return scan_digit();
	else if(ISLETTER(peek))
		return scan_letter();

	char* id = (char*)malloc(sizeof(char));
	*id = peek;
	token *symbol = (token*)malloc(sizeof(token));
	memset(symbol, 0, sizeof(token));
	symbol->context = id;
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

token* scan_digit()
{
	int *v = malloc(sizeof(int));
	*v = 0;
	do
	{
		*v = 10 * (*v) + (peek - '0');
		peek = getchar();
	}while(ISDIGIT(peek));
	if(peek == '.')
	{
		double* decimal = malloc(sizeof(double));
		*decimal = 0;
		int count = 0;
		for(peek = getchar(); ISDIGIT(peek); peek = getchar())
		{
			count++;
			*decimal = 10 * (*decimal) + (peek - '0');
		}
		*decimal = *decimal * pow(0.1, count) + *v;
		token *number = (token*)malloc(sizeof(token));
		number->context = decimal;
		number->proc = &proc_num;
		number->tag = FLOAT;
		return number;
	}
	token *number = (token*)malloc(sizeof(token));
	number->context = v;
	number->proc = &proc_num;
	number->tag = NUM;
	return number;
}

token* scan_letter()
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
	hash_int(words, strhash(words, temp), word);
	word->context = temp;
	word->proc = &proc_word;
	word->tag = ID;
	return word;
}

void proc_num(void* context){}
void proc_word(void* context){}
void proc_id(void* context){}
