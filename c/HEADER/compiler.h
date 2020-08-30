#ifndef COMPILER_H
#define COMPILER_H

#include <stdlib.h>

#define true 1
#define false 0
#define KEYWORD_LEN 15
#define SPACE ' '
#define NEWLINE '\n'


typedef struct LEXER{

	char current_char;
	int index;
	char *code;

} lexer;

//creating a lexer
lexer* new_lexer(char *code);

//next char in the code
void next_char(lexer *l);

//search keyword
int search_keyword(char *identifier, size_t len);

//to check id identidier is keyword or not
int is_keyword(char *identifier);

//to get string
char* get_string(lexer *l);

//to get identifier
char* get_identifier(lexer *l);


typedef struct TOKEN{

	char *type;
	char *content;
	
} token;

//creating a new token
token* new_token(char *type, char *content);

//char to string
char* char_to_str(char a);



#endif
