#ifndef LEXER
#define LEXER
#define NUMBER 100
#define WORD 101

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
#endif