#ifndef LEXER
#define LEXER

// token tag
#define NUMBER 100
#define WORD 101
#define SYMBOL 102
#define KEYWORD 103

#define ISDIGIT(N) (N >= '0' && N <= '9')
#define ISLETTER(N) ((N >= 'a' && N <= 'z') || (N >= 'A' && N <= 'Z'))
typedef struct token_
{
	void *context;
	void (*proc)();
	int tag;
}token;

typedef struct word_
{
	char lexeme;
}word;

typedef struct number_
{
	int value;
}number;

void proc_number(void* context);
void proc_word(void *context);
void proc_symbol(void *context);
#endif