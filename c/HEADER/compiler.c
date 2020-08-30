#include "compiler.h"
#include <stdlib.h>
#include <string.h>
//#include <stdio.h>
#include <ctype.h>


char *KEYWORD[KEYWORD_LEN] =  {
	"var",
	"loop",
	"if",
	"else",
	"in",
	"or",
	"and",
	"serial",
	"HIGH",
	"LOW",
	"return",
	"fun",
	"break",
	"true",
	"false"
};



//creating a lexer
lexer* new_lexer(char *code){

	lexer *l = calloc(1, sizeof(struct LEXER));
	l->code = code;
	l->index = 0;
	l->current_char = l->code[l->index];
	return l;
}

//next char in the code
void next_char(lexer *l){
	l->index++;
	l->current_char = l->code[l->index];
}

//search keyword
int search_keyword(char *identifier, size_t len){

	int SEARCH_FLAG = false;

	for(int i = 0; i < KEYWORD_LEN; i++){
		if(strncmp(identifier, KEYWORD[i], len) == 0){
			//fprintf(stdout, " %s , %s \t ", identifier, KEYWORD[i]);
			SEARCH_FLAG = true;
			break;
		}
	}

	return SEARCH_FLAG;

}

//to check id identidier is keyword or not
int is_keyword(char *identifier){
	size_t len =  strlen(identifier);
	//fprintf(stdout, "%s  ->  %lu \n", identifier, len);
	return search_keyword(identifier, len);
}

//to get string
char* get_string(lexer *l){

	next_char(l);
	char *identifier = calloc(1, sizeof(char));
    size_t i = 0;
    identifier[i] = l->current_char;
    i++;
    next_char(l);
    while( l-> current_char != '"' ){
	
		identifier = realloc(identifier, strlen(identifier) + sizeof(char));
	    identifier[i] = l->current_char;
        i++;
        next_char(l);
	}

	identifier = realloc(identifier, strlen(identifier) + sizeof(char));
	identifier[i] = '\0';

	return identifier;
}

//to get identifier
char* get_identifier(lexer *l){

	char *identifier = calloc(1, sizeof(char));
    size_t i = 0;
    identifier[i] = l->current_char;
    i++;
    next_char(l);
    while( isalnum( l-> current_char) ){

	    identifier = realloc(identifier, strlen(identifier) + sizeof(char));
        identifier[i] = l->current_char;
        i++;
        next_char(l);
 
     }
 
     identifier = realloc(identifier, strlen(identifier) + sizeof(char));
     identifier[i] = '\0';

	return identifier;

}


//creating a new token
token* new_token(char *type, char *content){
	token *t = calloc(1, sizeof(token));
	t->type = type;
	t->content = content;
	return t;
}

//char to string
char* char_to_str(char a){
	char *str = calloc(2, sizeof(char));
	str[0] = a;
	str[1] = '\0';
	return str;
}


