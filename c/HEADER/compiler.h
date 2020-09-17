#ifndef COMPILER_H
#define COMPILER_H

#include <stdlib.h>
#include "error.h"
#include "symbol_table.h"
#include "token.h"
#include "expression.h"

#define true 1
#define false 0
#define KEYWORD_LEN 15
#define SPACE ' '
#define NEWLINE '\n'
#define BUILTIN_FUN_COUNT 3


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
int search_keyword(char *identifier);

//to check id identidier is keyword or not
int is_keyword(char *identifier);

//is builtin function
int is_builtin_function(char *identifier);

//to get string
char* get_string(lexer *l);

//to get identifier
char* get_identifier(lexer *l);

//char to string
char* char_to_str(char a);

typedef struct FUNCTION_ARGS{

	struct FUNCTION_ARGS *next_arg;

	char *arg_name;
	char *arg_type;


} function_args;

typedef struct FUNCTION_ARGS_LIST{

	function_args *first_arg;
	function_args *last_arg;

} function_args_list;

//create new funciton argurment list
function_args_list* new_function_arg_list();

//create new function argument
function_args* new_function_argument(char *name, char *type);

//add new function argument to args list
void add_new_arg(function_args_list *args_list, function_args *arg);

typedef struct AST{

	struct AST *previous_ast_node;
	struct AST *next_ast_node;

	char *type;
	size_t ast_node_index;

	//function call
	char *function_name;
	function_args_list *args_list;
	size_t args_count;

	//variable definition and assignment
	char *var_def_var_name;
	char *var_def_var_type;
	expr_ast *var_def_var_expr;
	
	//variable assignment
	char *var_name;
	char *var_type;
	expr_ast *var_expr;

} ast;

//creates new ast
ast* new_ast(char *type);

typedef struct AST_LIST{

	size_t ast_index;
	size_t line_count;
	ast *root_node;
	ast *last_node;

} ast_l;

//create new ast list
ast_l* new_ast_list();

//add new ast
void add_new_ast(ast_l *ast_list, ast *node);

//print ast
void print_ast(ast_l *ast_list);

typedef struct PARSER{

	token *current_token;
	lexer *l;

} parser;

//creating a new parser
parser *new_parser(lexer *l);

//gets the current token
token* get_current_token(parser *p);

//get next token
token* get_next_token(parser *p);

//peek next token
token* peek_next_token(parser *p);

//skip line
void skip_current_line(parser *p);

//parser eat function
int parser_eat(token *t, char *type, error_list *err_list, size_t code_size);

//parse given statements

//parse expressions
void *parse_expressions(parser *p,/* error_list *err_list,*/ ast_l *ast_list);

//parse variable declaration and definition
ast* parse_var_def(parser *p,error_list *err_list,  ast_l *ast_list);

//parse newline character
void parse_newline(parser* p, error_list *err_list, ast_l *ast_list);

//parse var assignment
ast* parse_var_assignment(parser *p,error_list *err_list,  ast_l *ast_list);

//parse function call
ast* parse_function_call(parser *p,error_list *err_list,  ast_l *ast_list);

#endif
