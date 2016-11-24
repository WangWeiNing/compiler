#include <stddef.h>
#include <stdio.h>
#include "lexer.h"

char peek;
int line;

int main()
{
	return 0;
}

token* scan()
{
	while(true)
	{
		peek = getchar();
		if(peek == '\t' || peek == ' ')
			continue;
		else if(peek == '\n')
			line++
		else
			break;
	}

	if(isDigit(peek))
	{
		int *v = malloc(sizeof(int));
		do
		{
			*v = 10 * *v + (int)peek;
		}while(isDigit(peek))
		token *number = (token*)malloc(sizeof(token));
		number->context = v;
		number->proc = &proc_number;
		return number;
	}
}