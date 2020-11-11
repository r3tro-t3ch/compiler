#include "compiler.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "symbol_table.h"
#include "token.h"
#include "expression.h"

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

//next char in thee code
void next_char(lexer *l){
	l->index++;
	l->current_char = l->code[l->index];
}

//search keyword
int search_keyword(char *identifier){

	int SEARCH_FLAG = false;

	for(int i = 0; i < KEYWORD_LEN; i++){
		if(strcmp(KEYWORD[i],identifier) == 0){
			//fprintf(stdout, " %s , %s \t ", identifier, KEYWORD[i]);
			SEARCH_FLAG = true;
			break;
		}
	}

	return SEARCH_FLAG;

}

//to check id identidier is keyword or not
int is_keyword(char *identifier){
	//fprintf(stdout, "%s  ->  %lu \n", identifier, len);
	return search_keyword(identifier);
}

//is builtin function
int is_builtin_function(char *identifier){

	int SEARCH_FLAG = false;

	for(int i = 0; i < BUILTIN_FUN_COUNT; i++){
		if(strcmp(BUILTIN_FUNCTION[i],identifier) == 0){
			SEARCH_FLAG = true;
			break;
		}
	}

	return SEARCH_FLAG;

}

//to get string
char* get_string(lexer *l){

	next_char(l);  //skipping the opening "
	char *identifier = calloc(1, sizeof(char));
    size_t i = 0;
    while( l->current_char != '\"' ){
	
		identifier = realloc(identifier, i + sizeof(char));
	    identifier[i] = l->current_char;
        i++;
    	next_char(l);
	}

	identifier = realloc(identifier, i + sizeof(char));
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

	    identifier = realloc(identifier, i + sizeof(char));
        identifier[i] = l->current_char;
        i++;
        next_char(l);
 
     }
 
     identifier = realloc(identifier, i + sizeof(char));
     identifier[i] = '\0';

	return identifier;

}

//char to string
char* char_to_str(char a){
	char *str = calloc(2, sizeof(char));
	str[0] = a;
	str[1] = '\0';
	return str;
}

//create new funciton argurment list
function_args_list* new_function_arg_list(){

	function_args_list *arg_list = calloc(1, sizeof(function_args_list));
	arg_list->first_arg = NULL;
	arg_list->last_arg = NULL;
	return arg_list;

}

//create new function argument
function_args* new_function_argument(char *name, char *type){

	function_args *arg = calloc(1, sizeof(function_args));
	arg->next_arg = NULL;
	arg->arg_name = name;
	arg->arg_type = type;
	return arg;

}

//add new function argument to args list
void add_new_arg(function_args_list *args_list, function_args *arg){

	if(args_list->first_arg == NULL){

		args_list->first_arg = arg;
		args_list->last_arg = arg;

	}else{

		args_list->last_arg->next_arg = arg;
		args_list->last_arg = arg;

	}

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

				char next = p->l->code[p->l->index+1];

				if( next == '=' ){

					t = new_token("T_EE", "==");
					p->current_token = t;
					next_char(p->l);
					next_char(p->l);
					return t;

				}

				t = new_token("T_EQUAL", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;

				break;
			 }
		case '>':{
					 
				char next = p->l->code[p->l->index+1];

				if( next == '=' ){

					t = new_token("T_GE", ">=");
					p->current_token = t;
					next_char(p->l);
					next_char(p->l);
					return t;

				}

				t = new_token("T_GREATER", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;

				break;
				
			}
		case '<':{
			
				char next = p->l->code[p->l->index+1];

				if(next == '='){

					t = new_token("T_LE", "<=");
					p->current_token = t;
					next_char(p->l);
					next_char(p->l);
					return t;

				}

				t = new_token("T_LESSER", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;

				break;
			 }
		case '|':{

				char next = p->l->code[p->l->index+1];

				if( next == '|' ){

					t = new_token("T_LOR", "||");
					p->current_token = t;
					next_char(p->l);
					next_char(p->l);
					return t;

				}

				t = new_token("T_BOR", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;

				break;

				 }
		case '&':{

				char next = p->l->code[p->l->index+1];

				if( next == '&' ){

					t = new_token("T_LAND", "&&");
					p->current_token = t;
					next_char(p->l);
					next_char(p->l);
					return t;

				}

				t = new_token("T_BAND", char_to_str(p->l->current_char));
				p->current_token = t;
				next_char(p->l);
				return t;

				break;

			 }
		case '!':{

				char next = p->l->code[p->l->index+1];

				if( next == '=' ){

					t = new_token("T_NE", "!=");
					p->current_token = t;
					next_char(p->l);
					next_char(p->l);
					return t;

				}

				t = new_token("T_BNOT", char_to_str(p->l->current_char));
				p->current_token = t;	
				next_char(p->l);
				return t;

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
		case '\"':{

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
				
				char next = temp_p->l->code[temp_p->l->index+1];
				
				if( next == '=' ){

					t = new_token("T_EE", "==");
					next_char(temp_p->l);
					next_char(temp_p->l);
					return t;

				}

				t = new_token("T_EQUAL", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;

				break;
			 }
		case '>':{
					
				char next = temp_p->l->code[temp_p->l->index+1];
				
				if( next == '=' ){

					t = new_token("T_GE", ">=");
					next_char(temp_p->l);
					next_char(temp_p->l);
					return t;

				}

				t = new_token("T_GREATER", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				
				break;
			 }
		case '<':{
					
				char next = temp_p->l->code[temp_p->l->index+1];
				
				if( next == '=' ){

					t = new_token("T_LE", "<=");
					next_char(temp_p->l);
					next_char(temp_p->l);
					return t;

				}

				t = new_token("T_LESSER", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;
				
				break;
			 }
		case '|':{

				char next = temp_p->l->code[temp_p->l->index+1];

				if( next == '|' ){

					t = new_token("T_LOR", "||");
					next_char(temp_p->l);
					next_char(temp_p->l);
					return t;

				}

				t = new_token("T_BOR", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;

				break;

			}
		case '&':{

				char next = temp_p->l->code[temp_p->l->index+1];

				if( next == '&' ){

					t = new_token("T_LAND", "&&");
					next_char(temp_p->l);
					next_char(temp_p->l);
					return t;

				}

				t = new_token("T_BAND", char_to_str(p->l->current_char));
				next_char(temp_p->l);
				return t;

				break;

			}
		case '!':{

				char next = temp_p->l->code[temp_p->l->index+1];

				if( next == '=' ){

					t = new_token("T_NE", "!=");
					next_char(temp_p->l);
					next_char(temp_p->l);
					return t;

				}

				t = new_token("T_BNOT", char_to_str(temp_p->l->current_char));
				
				next_char(temp_p->l);
				return t;

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

	_ast->previous_ast_node = NULL;
	_ast->next_ast_node = NULL;

	_ast->type = type;
	_ast->ast_node_index = 0;

	//function call
	_ast->function_name = (void *) 0;
	_ast->args_list = (void *) 0;
	_ast->args_count = 0;

	//variable definition and assignment
	_ast->var_def_var_name = (void *) 0;
	_ast->var_def_var_type = (void *) 0;
	_ast->var_def_var_expr = (void *) 0;

	//variable assignment
	_ast->var_name = (void *) 0;
	_ast->var_type = (void *) 0;
	_ast->var_return_val = (void *) 0;
	_ast->var_expr = (void *) 0;

	//conditional statements
	_ast->conditional_statement_expr = (void *) 0;
	_ast->true_block = (void *)0;
	_ast->false_block = (void *) 0;

	return _ast;

}

//create new ast list
ast_l* new_ast_list(){

	ast_l *ast_list = calloc(1, sizeof(ast_l));
	ast_list->ast_index = 0;
	ast_list->root_node = NULL;
	ast_list->last_node = NULL;
	ast_list->line_count = 0;
	return ast_list;

}

//add new ast
void add_new_ast(ast_l *ast_list, ast *node){

	if(ast_list->ast_index == 0){

		ast_list->root_node = node;
		ast_list->last_node = node;
		ast_list->ast_index++;

	}else{
		
		ast_list->last_node->next_ast_node = node;
		node->previous_ast_node = ast_list->last_node;
		ast_list->last_node = node;
		ast_list->ast_index++;

	}		

}

//print ast
void print_ast(ast_l *ast_list){

	ast *node = ast_list->root_node;

	fprintf(stdout,"%td, %s\n",
			node->ast_node_index,
			node->type);


	while( node->next_ast_node != NULL ){

		node = node->next_ast_node;

		fprintf(stdout,"%td, %s\n", 
				node->ast_node_index,
			node->type);

	}
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

//skip line
void skip_current_line(parser *p){

	while( strncmp(get_current_token(p)->type, "T_NEWLINE",9) != 0){

		get_next_token(p);

	}

}

//parser eat function
int parser_eat(token *t, char *type, error_list *err_list, size_t code_size){

	size_t token_len = strlen(type);

	if(strncmp(t->type, type, token_len ) != 0){

		size_t err_msg_len = strlen(t->content) + strlen(t->type) + strlen(type) + ERR_MSG_LEN; 

		char *err_msg = calloc( err_msg_len ,sizeof(char));

		snprintf(err_msg, err_msg_len,
			"unexpected token %s of %s type expected %s\n",			
			t->content,
			t->type,
			type
		);

		error* e = new_error(err_msg ,code_size);

		add_new_error(err_list, e);
		return 0;

	}else{

		return 1;

	}

}

//parse expressions
token_list* parse_expressions(parser *p ){

	token_list *list = new_token_list();

	get_next_token(p);

	while(is_expression_token(get_current_token(p)) == 1){

		add_new_token(list, get_current_token(p));

		get_next_token(p);

	}

	if(list->token_count == 1){

		return list;

	}

	token_list *postfix = infix_to_postfix(list);

	return postfix;

}

//parse var declaration and definition
ast* parse_var_def( parser *p, error_list *err_list, ast_l* ast_list){

	ast *a = new_ast("AST_VAR_DEF");

	int error_flag = 0;

	if(parser_eat(get_current_token(p), "T_KEYWORD", err_list, ast_list->line_count) == 0){
		error_flag = 1;
		return NULL;
	}

	get_next_token(p);
	
	if (parser_eat(get_current_token(p), "T_IDENTIFIER", err_list, ast_list->line_count) == 0){
		error_flag = 1;
		return NULL;
	}

	a->var_def_var_name = get_current_token(p)->content;	

	token *t = peek_next_token(p);

	if( strncmp(t->type, "T_EQUAL", 7) == 0){
					
		get_next_token(p);

		a->type = "AST_VAR_DEF_ASSIGNMENT";

		if(parser_eat(get_current_token(p), "T_EQUAL", err_list, ast_list->line_count) == 0){
			error_flag = 1;
			return NULL;
		}

		t = peek_next_token(p);

		if( strncmp(t->type,"T_CONSTANT", 10) == 0 ||
			strncmp(t->type,"T_IDENTIFIER", 12) == 0 ||
			strncmp(t->type,"T_STRING", 9) == 0 ){

			if(	strncmp( t->type, "T_IDENTIFIER", 12 ) == 0 ){
	
				if( is_builtin_function(t->content) == 1 ){

					get_next_token(p);

					ast *temp =	parse_function_call(p, err_list, ast_list);

					a->type = "AST_VAR_DEF_ASSIGNMENT_FUNCTION";

					a->function_name = temp->function_name;
					a->args_count = temp->args_count;
					a->args_list = temp->args_list;

					a->ast_node_index = ast_list->line_count;
					return a;

				}
			}

			a->var_def_var_expr = parse_expressions(p);

			if(is_postfix_valid(a->var_def_var_expr) == 0){

				error *e = new_error("Invalid expression", ast_list->line_count);

				add_new_error(err_list, e);

				return NULL;		

			}

			a->type = "AST_VAR_DEF_ASSIGNMENT";

			a->ast_node_index = ast_list->line_count;

			return a;

		}

	}else{
					
		t = peek_next_token(p);

		if(parser_eat(t, "T_NEWLINE", err_list, ast_list->line_count) == 0 ){

			error_flag = 1;
			return NULL;

		}

		a->ast_node_index = ast_list->line_count;

		if(error_flag == 0){
		
			return a;

		}

	}

	return NULL;

}

//parse newline character
void parse_newline(parser* p, error_list *err_list, ast_l *ast_list){

	int error_flag = 0;
	if( parser_eat(get_current_token(p), "T_NEWLINE", err_list, ast_list->line_count) == 0){

		error_flag = 1;

	}

	if(error_flag == 0){
	
		ast_list->line_count++;
	
	}
}

//parse var assignment
ast* parse_var_assignment(parser *p,error_list *err_list,  ast_l *ast_list){

	ast *node = new_ast("AST_VAR_ASSIGNMENT");

	size_t error_flag = 0;

	if( parser_eat(get_current_token(p),"T_IDENTIFIER", err_list, ast_list->line_count) == 0 ){

		error_flag = 1;
		return NULL;

	}

	node->var_name = get_current_token(p)->content;

	get_next_token(p); // = 

	if(parser_eat(get_current_token(p),"T_EQUAL", err_list, ast_list->line_count) == 0){

		error_flag = 1;
		return NULL;

	}

	token *t = peek_next_token(p);

	if( strncmp( t->type, "T_CONSTANT", 10 ) == 0 ||
		strncmp( t->type, "T_STRING", 8 ) == 0 ||
		strncmp( t->type, "T_IDENTIFIER", 12 ) == 0	){


		if(	strncmp( t->type, "T_IDENTIFIER", 12 ) == 0 ){

			if( is_builtin_function(t->content) == 1 ){

				get_next_token(p);

				ast *temp =	parse_function_call(p, err_list, ast_list);

				node->type = "AST_VAR_ASSIGNMENT_FUNCTION";

				node->function_name = temp->function_name;
				node->args_count = temp->args_count;
				node->args_list = temp->args_list;

				node->ast_node_index = ast_list->line_count;
				return node;

			}			

		}

		node->type = "AST_VAR_ASSIGNMENT";
		node->var_expr = parse_expressions(p);

		if(is_postfix_valid(node->var_expr) == 0){

			error *e = new_error("Invalid expression", ast_list->line_count);

			add_new_error(err_list, e);

			error_flag = 1;

			return NULL;		

		}

		node->ast_node_index = ast_list->line_count;


	}/*else{

		parse_function_call(p, err_list, ast_list);

	}*/

	
	if(error_flag == 0){

		return node;

	}

	return NULL;

}

//parse function call
ast* parse_function_call(parser *p,error_list *err_list,  ast_l *ast_list){

	int error_flag = 0 ;
	
	ast *node;

	if( parser_eat(get_current_token(p), "T_IDENTIFIER", err_list, ast_list->line_count) == 0){

		error_flag = 1;
		return NULL;

	}

	if( is_builtin_function(get_current_token(p)->content) == 1 ){

		node = new_ast("AST_BUILTIN_FUNCTION_CALL");

		if( strncmp(get_current_token(p)->content, "output",6) == 0 ){


			node->function_name = get_current_token(p)->content;

			get_next_token(p); // (


			if( parser_eat(get_current_token(p), "T_LPAREN", err_list, ast_list->line_count ) == 0){

				error_flag = 1;
				return NULL;

			}

			token *temp = peek_next_token(p);

			node->args_list = new_function_arg_list();

			if( strncmp(temp->type, "T_CONSTANT", 10) == 0 ){

				get_next_token(p); //first arg


				if( parser_eat(get_current_token(p), "T_CONSTANT", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}

				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}else if( strncmp(temp->type, "T_IDENTIFIER", 12) == 0 ){

				get_next_token(p); // first arg

				if( parser_eat(get_current_token(p), "T_IDENTIFIER", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}
				
				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}else if( strncmp(temp->type, "T_KEYWORD", 9) == 0 ){

				get_next_token(p); // first arg

				if( parser_eat(get_current_token(p), "T_KEYWORD", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}
				
				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}

			get_next_token(p);

			if( parser_eat( get_current_token(p), "T_COMMA", err_list, ast_list->line_count  ) == 0 ){

					error_flag = 1;
					return NULL;

			}

			temp = peek_next_token(p);

			if( strncmp(temp->type, "T_CONSTANT", 10) == 0 ){

				get_next_token(p); //second arg

				if( parser_eat(get_current_token(p), "T_CONSTANT", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}

				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);

				node->args_count++;


			}else if( strncmp(temp->type, "T_STRING", 8) == 0 ){

				get_next_token(p); //second arg

				if( parser_eat(get_current_token(p), "T_STRING", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}

				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}else if( strncmp(temp->type, "T_IDENTIFIER", 12) == 0 ){

				get_next_token(p); //second arg

				if( parser_eat(get_current_token(p), "T_IDENTIFER", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}

				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}else if( strncmp(temp->type, "T_KEYWORD", 9) == 0 ){

				get_next_token(p); //second arg

				if( parser_eat(get_current_token(p), "T_KEYWORD", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}

				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}

		}else if( strncmp(get_current_token(p)->content, "input", 6)== 0){
		

			node->function_name = get_current_token(p)->content;

			get_next_token(p); // (
			
			if( parser_eat(get_current_token(p), "T_LPAREN", err_list, ast_list->line_count ) == 0){

				error_flag = 1;
				return NULL;

			}

			token *temp = peek_next_token(p);

			node->args_list = new_function_arg_list();

			if( strncmp(temp->type, "T_CONSTANT", 10) == 0 ){

				get_next_token(p); //first arg

				if( parser_eat(get_current_token(p), "T_CONSTANT", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}

				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}else if( strncmp(temp->type, "T_IDENTIFIER", 12) == 0 ){

				get_next_token(p); // first arg

				if( parser_eat(get_current_token(p), "T_IDENTIFIER", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}
				
				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}

			//get_next_token(p);

		}else if( strncmp(get_current_token(p)->content, "wait", 4) == 0 ){

			node->function_name = get_current_token(p)->content;

			get_next_token(p); // (

			if( parser_eat(get_current_token(p), "T_LPAREN", err_list, ast_list->line_count ) == 0){

				error_flag = 1;
				return NULL;

			}

			token *temp = peek_next_token(p);

			node->args_list = new_function_arg_list();

			if( strncmp(temp->type, "T_CONSTANT", 10) == 0 ){

				get_next_token(p); //first arg

				if( parser_eat(get_current_token(p), "T_CONSTANT", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}

				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}else if( strncmp(temp->type, "T_IDENTIFIER", 12) == 0 ){

				get_next_token(p); // first arg

				if( parser_eat(get_current_token(p), "T_IDENTIFIER", err_list, ast_list->line_count ) == 0 ){

					error_flag = 1;
					return NULL;

				}
				
				function_args *arg = new_function_argument(get_current_token(p)->content, get_current_token(p)->type);

				add_new_arg(node->args_list, arg);
				node->args_count++;

			}

		}	


		get_next_token(p);

		if( parser_eat(get_current_token(p), "T_RPAREN", err_list, ast_list->line_count) == 0 ){

			error_flag = 1;
			return NULL;

		}

		node->ast_node_index = ast_list->line_count;

	}//implement user defined function


	if( error_flag == 0 ){

		return node;

	}

	return NULL;

}

//parse statements
ast_l* parse_statements(parser *p, error_list *err_list){

	ast_l *ast_list = new_ast_list();

	get_next_token(p);

	while(strncmp(get_current_token(p)->type, "T_NULL", 6) != 0 ){


		if( strncmp(get_current_token(p)->type, "T_KEYWORD", 10) == 0){

			if( strncmp(get_current_token(p)->content, "var", 3) == 0){
	
				ast* node = parse_var_def(p, err_list, ast_list);
			
				if(node != NULL){
				
					add_new_ast(ast_list, node);


				}
			}
		}else if(strncmp(get_current_token(p)->type, "T_IDENTIFIER", 12) == 0){

			token *t = peek_next_token(p);

			if( strncmp(t->type, "T_EQUAL", 7) == 0 ){

				ast *node = parse_var_assignment(p, err_list, ast_list);
	
				if(node != NULL){
				
					add_new_ast(ast_list, node);
			
				}

			}else if( strncmp(t->type, "T_LPAREN", 8) == 0 ){

				ast *node = parse_function_call(p, err_list, ast_list);

				if( node != NULL ){

					add_new_ast(ast_list, node);

				}

			}else{
				parse_newline(p, err_list, ast_list);
			}
		}	
		
		if(strncmp(get_current_token(p)->type, "T_NULL", 6) == 0){

			break;

		}	

		if( strncmp(get_current_token(p)->type, "T_NEWLINE", 10) == 0 ){

			parse_newline(p, err_list, ast_list);

		}

		get_next_token(p);
		
		
	}
	return ast_list;

}
