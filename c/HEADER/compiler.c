#include "compiler.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

char *BUILTIN_FUNCTION[BUILTIN_FUN_COUNT] = {

	"output",
	"input",
	"wait"

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

//get next token
token* get_next_token(parser *p){

	token *t = calloc(1, sizeof(struct TOKEN));

	if(p->l->current_char == SPACE){
		
		while(p->l->current_char == SPACE)
			next_char(p->l);
		
	}
	if(p->l->current_char == '\n' ){
		
			t = new_token("T_NEWLINE", "NEWLINE");
			p->current_token = t;
			next_char(p->l);
			return t;
		
	}


	if( isalnum( p->l-> current_char) ){

		char *identifier = get_identifier(p->l);

		if( isdigit(*identifier) ){
				
			t = new_token("T_CONSTANT", identifier);
			p->current_token = t;
			return t;

		}else if( is_keyword(identifier) ){

			t =  new_token("T_KEYWORD", identifier);
			p->current_token = t;
			return t;

		}else{

			t = new_token("T_IDENTIFIER", identifier);
			p->current_token = t;
			return t;

		}

	}

	switch(p->l->current_char){

		case '(':{
				t = new_token("T_LPAREN", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
		 	}
		case ')':{
				t =  new_token("T_RPAREN", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '{':{
				t = new_token("T_LBRACE", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '}':{
				t = new_token("T_RBRACE", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '+':{
				t = new_token("T_PLUS", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '-':{
				t = new_token("T_MINUS", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '*':{
				t = new_token("T_ASTERIX", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '/':{
				t = new_token("T_FSLASH", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '%':{
				t = new_token("T_MOD", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '=':{
				t = new_token("T_EQUAL", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '>':{
				t = new_token("T_GREATER", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '<':{
				t = new_token("T_LESSER", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case ',':{
				t = new_token("T_COMMA", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '\0':{
				t = new_token("T_NULL", "NULL");
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
		case '"':{

				char *identifier = get_string(p->l);
											
				t = new_token("T_STRING", identifier);
				p->current_token = t;
				next_char(p->l);
				return t;
				break;
			 }
	}	

	return NULL;

}

//get next token
token* peek_next_token(parser *p){

	lexer* l = new_lexer(p->l->code); 
	l->current_char = p->l->current_char;
	l->index = p->l->index;

	parser *temp_p = new_parser(l);
	temp_p->current_token = p->current_token;

	token *t = calloc(1, sizeof(struct TOKEN));

	if(temp_p->l->current_char == SPACE){
		
		while(temp_p->l->current_char == SPACE)
			next_char(temp_p->l);
		
	}
	if(temp_p->l->current_char == '\n' ){
		
			t = new_token("T_NEWLINE", "NEWLINE");
			next_char(temp_p->l);
			return t;
		
	}


	if( isalnum( temp_p->l-> current_char) ){

		char *identifier = get_identifier(temp_p->l);

		

		if( isdigit(*identifier) ){
				
			t = new_token("T_CONSTANT", identifier);
			return t;

		}else if( is_keyword(identifier) ){

			t =  new_token("T_KEYWORD", identifier);
			return t;

		}else{

			t = new_token("T_IDENTIFIER", identifier);
			return t;

		}

	}

	switch(temp_p->l->current_char){

		case '(':{
				t = new_token("T_LPAREN", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
		 	}
		case ')':{
				t =  new_token("T_RPAREN", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '{':{
				t = new_token("T_LBRACE", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '}':{
				t = new_token("T_RBRACE", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '+':{
				t = new_token("T_PLUS", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '-':{
				t = new_token("T_MINUS", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '*':{
				t = new_token("T_ASTERIX", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '/':{
				t = new_token("T_FSLASH", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '%':{
				t = new_token("T_MOD", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '=':{
				t = new_token("T_EQUAL", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '>':{
				t = new_token("T_GREATER", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '<':{
				t = new_token("T_LESSER", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case ',':{
				t = new_token("T_COMMA", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '\0':{
				t = new_token("T_NULL", "NULL");
				next_char(temp_p->l);
				return t;
				break;
			 }
		case '"':{

				char *identifier = get_string(p->l);
											
				t = new_token("T_STRING", identifier);
				next_char(temp_p->l);
				return t;
				break;
			 }
	}	

	return NULL;

}


//creates new ast
ast* new_ast(char *type){

	ast* _ast = calloc(1, sizeof(ast));

	_ast->type = type;
	
	_ast->code_size = 0;
	_ast->next = NULL;

	//function call
	_ast->function_name = (void *) 0;
	_ast->args = (void *) 0;
	_ast->args_count = 0;

	//variable definition and assignment
	_ast->var_def_var_name = (void *) 0;
	_ast->var_def_var_content = (void *) 0;

	//variable assignment
	_ast->var_name = (void *) 0;
	_ast->var_content = (void *) 0;

	return _ast;

}

//creating a new parser
parser* new_parser(lexer *l){

	parser *p = calloc(1, sizeof( struct PARSER));
	p->l = l;
	p->current_token = (void*) 0;
	return p;

}

//gets the current token
token* get_current_token(parser *p){

	return p->current_token;

}

//parser eat function
void parser_eat(token *t, char *type, error_list *err_list, ast *a){

	size_t token_len = strlen(type);

	if(strncmp(t->type, type, token_len ) != 0){

		fprintf(stdout, "%td", a->code_size);

		size_t err_msg_len = strlen(t->content) + strlen(t->type) + ERR_MSG_LEN; 

		char *err_msg = calloc( err_msg_len ,sizeof(char));

		snprintf(err_msg, err_msg_len,
			"unexpected token %s of %s type\n",			
			t->content,
			t->type
		);

		error* e = new_error(err_msg ,a->code_size+1);

		add_new_error(err_list, e);
	}

}

