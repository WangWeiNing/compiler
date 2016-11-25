#ifndef LEXER
#define LEXER

// token tag
#define NUM 256
#define ID 257
#define TRUE 258
#define FALSE 259
#define FLOAT 260

#define ISDIGIT(N) (N >= '0' && N <= '9')
#define ISLETTER(N) ((N >= 'a' && N <= 'z') || (N >= 'A' && N <= 'Z'))
typedef struct token_
{
	void *context;
	void (*proc)();
	int tag;
}token;

void proc_num(void* context);
void proc_word(void *context);
void proc_id(void *context);
#endif