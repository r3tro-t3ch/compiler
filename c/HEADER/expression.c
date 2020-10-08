#include <stdlib.h>
#include "expression.h"
#include <string.h>
#include <stdio.h>

int is_expression_token(token *t){

	if( strncmp(t->type, "T_IDENTIFIER", 12) == 0 ||
		strncmp(t->type, "T_CONSTANT", 10) == 0 ||
		strncmp(t->type, "T_PLUS", 6) == 0 ||
		strncmp(t->type, "T_MINUS", 7) == 0 ||
		strncmp(t->type, "T_ASTERIX", 9) == 0 ||
		strncmp(t->type, "T_FSLASH", 8) == 0 ||
		strncmp(t->type, "T_MOD", 5) == 0 
		/*strncmp(t->type, "T_GREATER", 9) == 0 ||
		strncmp(t->type, "T_LESSER", 8) == 0*/
	  ){

		return 1;

	}

	return 0;
}

//check if is operand
int is_operator(token *t){

	if(strncmp(t->type, "T_PLUS", 6) == 0 ||
		strncmp(t->type, "T_MINUS", 7) == 0 ||
		strncmp(t->type, "T_ASTERIX", 9) == 0 ||
		strncmp(t->type, "T_FSLASH", 8) == 0 ||
		strncmp(t->type, "T_MOD", 5) == 0 
	  ){

		return 1;

	}

	return 0;

}

//new token list
token_list* new_token_list(){

	token_list *list = calloc(1, sizeof(token_list));
	list->first_token = NULL;
	list->last_token = NULL;
	list->token_count = 0;
	return list;

}

//add new token
void add_new_token(token_list *list, token *t){

	if(list->first_token == NULL){

		list->first_token = t;
		list->last_token = t;
		list->token_count++;

	}else{

		list->last_token->next_token = t;
		t->prev_token = list->last_token;
		list->last_token = t;
		list->token_count++;

	}

}

//new expression node
expression_node* new_expression_node(token *t){

	expression_node *e = calloc(1, sizeof(expression_node));
	e->content = t->content;
	e->type = t->type;
	e->left_node = NULL;
	e->right_node = NULL;
	return e;


}

//new expression ast
expr_ast* new_expression_ast(){

	expr_ast *expr = calloc(1, sizeof(expr_ast));
	expr->root_node = NULL;
	return expr;

}

//reverse token list
void reverse_token_list(token_list *list){

	token *current = list->first_token;
	list->last_token = list->first_token;
	token *temp = NULL;

	while(current != NULL){

		temp = current->prev_token;
		current->prev_token = current->next_token;
		current->next_token = temp;
		current = current->prev_token;

	}

	if(temp != NULL){
		list->first_token = temp->prev_token;
	}

}

//create a stack
stack* new_stack(){

	stack *s = calloc(1, sizeof(stack));
	s->top = NULL;
	s->stack_size = 0;
	return s;

}

//get the top value of stack
token* get_stack_top(stack *s){

	if(s->top == NULL){
		return NULL;
	}

	token *t = calloc(1, sizeof(token));
	t->content = s->top->content;
	t->type = s->top->type;
	t->next_token = NULL;
	t->prev_token = NULL;
	return t;

}

//stack pop operation
token* pop(stack *s){

	if(s->stack_size > 0){
		token *t = s->top;
		s->top = s->top->prev_token;
		s->stack_size--;
		return t;
	}else{
		return NULL;
	}
}

//stack push operation
void push(stack *s, token *t){

	if(s->top == NULL){

		s->top = t;

	}else{
	
		t->prev_token = s->top;
		s->top->next_token = t;
		s->top = t;
		s->stack_size++;

	}
}

//check precedence of operator
int check_precedence(token *t){

	if(	strncmp(t->type, "T_ASTERIX", 9) == 0 ||
		strncmp(t->type, "T_FSLASH", 8) == 0 ||
		strncmp(t->type, "T_MOD", 5) == 0 
	  ){
		return 3;
	}else if(
		strncmp(t->type, "T_PLUS", 6) == 0 ||
		strncmp(t->type, "T_MINUS", 7) == 0
		){
		return 2;
	}else{
		return 1;
	}

}

//infix to prefix
token_list* infix_to_prefix(token_list *list){

	token_list *rev;
	//rev = reverse_token_list(list);
	
	/*final = new_token_list();

	token *t = rev->first_token;

	stack *s = new_stack();

	if(t->next_token == NULL){
		return NULL;
	}

	while(t->next_token != NULL){
	
		if(is_operator(t) == 1){
		
			if( s->stack_size == 0 ||
			    check_precdence(get_stack_top(s)) < check_precdence(t) ){
				push(s,t);
			}else if( check_precdence(get_stack_top(s)) > check_precdence(t)){
				while(s->stack_size > 0){
					
					add_new_token(final,pop(s));

				}

				push(s,t);

			}

		}else{
			add_new_token(final, t);
		}
		t = t->next_token;
	}*/
	
	return rev;

}

/*/create expression ast
expr_ast* create_new_expression_ast(token_list *list){

}*/

//print token list
void print_token_list(token_list *list){

	token *t = list->first_token;

	while(t != NULL){
		fprintf(stdout,"content->%s, type->%s\n", t->content, t->type);
		t = t->next_token;
	}

}
