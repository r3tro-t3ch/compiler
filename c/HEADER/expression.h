#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "token.h"
#include <stdlib.h>
#include "error.h"
#include "symbol_table.h"

//check if given token in an expression token or not
int is_expression_token(token *t);

//check if is operand
int is_operator(token *t);

//check if operator is a logical operator
int is_logical_operator(token *t);

typedef struct TOKEN_LIST{

	token *first_token;
	token *last_token;
	size_t token_count;

} token_list;

typedef struct STACK{

	token *top;
	size_t stack_size;

} stack;

//new token list
token_list* new_token_list();

//add new token
void add_new_token (token_list *list, token *t);

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

//check if a string is present in in given expression
int string_present(token *list, symbol_table *table);

//check if the string expression only contains + ot T_PLUS
int is_valid_string_expr(token *list);

//evaluate expression tree and return the answer
char* evaluate_expression_ast(token_list *node, error_list *err_list, symbol_table *table , size_t line, int *STRING_FLAG);

//check precedence of operator
int check_precedence(token *t);

//infix to prefix
token_list* infix_to_postfix(token_list *list);

//check if postfix expression is valid or not
int is_postfix_valid(token_list* list);

//print token list
void print_token_list(token_list *list);

#endif
