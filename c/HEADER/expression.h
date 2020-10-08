#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "token.h"
#include <stdlib.h>

//check if given token in an expression token or not
int is_expression_token(token *t);

//check if is operand
int is_operator(token *t);

typedef struct TOKEN_LIST{

	token *first_token;
	token *last_token;
	size_t token_count;

} token_list;

typedef struct EXPRESSION_NODE{

	char *type;
	char *content;

	struct EXPRESSION_NODE *left_node;
	struct EXPRESSION_NODE *right_node;

} expression_node;

typedef struct EXPRESSION_AST{

	expression_node *root_node;

} expr_ast;

typedef struct STACK{

	token *top;
	size_t stack_size;

} stack;

//new token list
token_list* new_token_list();

//add new token
void add_new_token (token_list *list, token *t);

//new expression node
expression_node* new_expression_node(token *t);

//new expression ast
expr_ast* new_expression_ast();

//reverse token list
void reverse_token_list(token_list *list);

//create a stack
stack* new_stack();

//get top value of stack
token* get_stack_top(stack *s);

//stack pop operation
token* pop(stack *s);

//stack push operation
void push(stack *s, token *t);

//check precedence of operator
int check_precedence(token *t);

//infix to prefix
token_list* infix_to_prefix(token_list *list);

//create expression ast
expr_ast* create_new_expression_ast(token_list *list);

//print token list
void print_token_list(token_list *list);

#endif
