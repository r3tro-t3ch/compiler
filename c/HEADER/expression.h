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

//check if given token in a logical expression token or not
int is_logical_expression_token(token *t);

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

typedef struct OPERAND{

	char *value;
	char *data_type;

} operand;

//new token list
token_list* new_token_list();

//add new token
void add_new_token (token_list *list, token *t);

//reverse token list
void reverse_token_list(token_list *list);

//create new operand
operand *new_operand(char *value, char *data_type);

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

//check for undeclared var in expr
int is_undeclared_var_present(token_list *list, symbol_table *table, error_list *err_list, int ast_node_index);

//checking if given expression is a simple expression or not
int is_simple_expr(token_list *list);

//checking if there is any var defined inside asm
int is_DSEG(token_list *t, symbol_table *table);

//evaluate expression tree and return the answer
char* evaluate_expression_ast(token_list *node, error_list *err_list, symbol_table *table , size_t line, int *STRING_FLAG);

//evaluate expression tree and return the answer
char* evaluate_predetermined_logical_expression(token_list *node, error_list *err_list, symbol_table *table , size_t line);

//evaluate expression tree and return the answer
char* evaluate_logical_expression(token_list *node, error_list *err_list, symbol_table *table , size_t line, int *STRING_FLAG);

//check precedence of operator
int check_precedence(token *t);

//infix to postfix
token_list* infix_to_postfix(token_list *list);

//postfix to infix
token_list* postfix_to_infix(token_list *list);

//check if postfix expression is valid or not
int is_postfix_valid(token_list* list);

//get identifer from string list
char* get_identifier_from_string(char *expr);

//convert string to token list
token_list* str_to_token_list(char *expr);

//print token list
void print_token_list(token_list *list);

#endif
