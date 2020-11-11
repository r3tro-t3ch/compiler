#include <stdlib.h>
#include "expression.h"
#include <string.h>
#include <stdio.h>
#include "symbol_table.h"


int is_expression_token(token *t){

	if( strncmp(t->type, "T_IDENTIFIER", 12) == 0 ||
		strncmp(t->type, "T_CONSTANT", 10) == 0 ||
		strncmp(t->type, "T_PLUS", 6) == 0 ||
		strncmp(t->type, "T_MINUS", 7) == 0 ||
		strncmp(t->type, "T_ASTERIX", 9) == 0 ||
		strncmp(t->type, "T_FSLASH", 8) == 0 ||
		strncmp(t->type, "T_MOD", 5) == 0 ||
		strncmp(t->type, "T_STRING", 8) == 0
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

//check if operator is a logical operator
int is_logical_operator(token *t);


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

	if(s->stack_size >= 0){
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

//check if a string is present in in given expression
int string_present(token *list, symbol_table *table){

	int flag = 0;

	token *t = list;

	while(t != NULL){
		
		if( strncmp( t->type, "T_STRING", 8 ) == 0){

			flag = 1;
			break;

		}else if( strncmp( t->type, "T_IDENTIFIER", 12 )  == 0){

			symbol *s = search_symbol(table, t->content);		

			if( strncmp(s->data_type, "STRING", 6) == 0){

				flag = 1;
				break;

			}

		}

		t = t->next_token;

	}

	return flag;

}

//check if the string expression only contains + ot T_PLUS
int is_valid_string_expr(token *list){

	int flag = 0;

	token *t = list;

	while(t != NULL){
	
		if( strncmp( t->type , "T_ASTERIX", 9) == 0 ||
			strncmp( t->type, "T_MINUS",7 ) == 0 ||
			strncmp( t->type, "T_FSLASH", 8 ) == 0){

			flag = 1;
			break;

		}

		t = t->next_token;

	}

	return flag;

}

//evaluate expression tree and return the answer
char* evaluate_expression_ast(token_list *node, error_list *err_list, symbol_table *table , size_t line, int *STRING_FLAG){

	if(node->token_count == 1){

		if(string_present(node->first_token, table) == 1){
			if(is_valid_string_expr(node->first_token) == 0){
				*STRING_FLAG = 1;
			}
		}

		return node->first_token->content;

	}

	token *t = node->first_token;

	char *answer = calloc(1, sizeof(char));

	stack *STACK = new_stack();

	//check if the exporession has a string value

	if(string_present(t, table) == 1){

		//checking if the string only has + or T_PLUS operator

		if(is_valid_string_expr(t) == 0){

			*STRING_FLAG = 1;

			while( t != NULL ){
				
				if( strncmp(t->type, "T_CONSTANT", 10) == 0 ||
					strncmp(t->type, "T_STRING", 7) == 0){

					push(STACK, t);

				}else if( strncmp(t->type, "T_IDENTIFIER", 12) == 0 ){

					symbol *temp = search_symbol(table, t->content);

					if(temp != NULL){

						push(STACK, t);

					}else{

						size_t err_msg_len = strlen(t->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

						char *err_msg = calloc(err_msg_len, sizeof(char));

						snprintf(err_msg, err_msg_len,
								 "variable %s is not declared\n",
								 t->content);

						add_new_error(err_list, new_error(err_msg, line));


						return NULL;
					}

				}else{

					//add all the string

					char *answer, *left_operand, *right_operand;

					token *left = pop(STACK);
					token *right = pop(STACK);

					if(  strncmp(left->type, "T_IDENTIFIER", 12) == 0 || 
					 	strncmp(right->type, "T_IDENTIFIER", 12) == 0){

						if( strncmp(left->type, "T_IDENTIFIER", 12) == 0 &&
							strncmp(right->type, "T_IDENTIFIER", 12) != 0){
				
							symbol *s = search_symbol(table, left->content);
							left_operand = s->value;
							right_operand = right->content;

						}else if( strncmp(right->type, "T_IDENTIFIER", 12) == 0 &&
						  	      strncmp(left->type, "T_IDENTIFIER", 12) != 0){

							symbol *s = search_symbol(table, right->content);
							right_operand = s->value;
							left_operand = left->content;

						}else{

							symbol *l = search_symbol(table, left->content);
							symbol *r = search_symbol(table, right->content);
	
							left_operand = l->value;
							right_operand = r->value;

						}
 
					}else{

						left_operand = left->content;
						right_operand = right->content;

					}

					if( strncmp(t->type, "T_PLUS", 6 ) == 0){

						answer = calloc( strlen(left_operand) + strlen(right_operand), sizeof(char));

						snprintf(answer, strlen(left_operand) + strlen(right_operand) + 1,
										"%s%s",
										left_operand,
										right_operand);

						push(STACK, new_token("T_STRING", answer));

					}

				}						

				t = t->next_token;

			}


			return STACK->top->content;

		}else{

			error *e = new_error("Invalid expression", line);

			add_new_error(err_list, e);

			return NULL;

		}


	}else{

		while( t != NULL ){

			if( strncmp(t->type, "T_CONSTANT", 10) == 0 ){

				push(STACK, t);

			}else if( strncmp(t->type, "T_IDENTIFIER", 12) == 0 ){

				symbol *temp = search_symbol(table, t->content);

				if(temp != NULL){

					push(STACK, t);

				}else{


					size_t err_msg_len = strlen(t->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

					char *err_msg = calloc(err_msg_len, sizeof(char));

					snprintf(err_msg, err_msg_len,
							 "variable %s is not declared\n",
							 t->content);

					add_new_error(err_list, new_error(err_msg, line));


					return NULL;
				}

			}else{

				token *left = pop(STACK);
				token *right = pop(STACK);

				int left_operand, right_operand;

				if(  strncmp(left->type, "T_IDENTIFIER", 12) == 0 || 
					 strncmp(right->type, "T_IDENTIFIER", 12) == 0){

					if( strncmp(left->type, "T_IDENTIFIER", 12) == 0 &&
						strncmp(right->type, "T_IDENTIFIER", 12) != 0){
				
						symbol *s = search_symbol(table, left->content);
						left_operand = atoi(s->value);
						right_operand = atoi(right->content);

					}else if( strncmp(right->type, "T_IDENTIFIER", 12) == 0 &&
					  	      strncmp(left->type, "T_IDENTIFIER", 12) != 0){

						symbol *s = search_symbol(table, right->content);
						right_operand = atoi(s->value);
						left_operand = atoi(left->content);

					}else{

						symbol *l = search_symbol(table, left->content);
						symbol *r = search_symbol(table, right->content);

						left_operand = atoi(l->value);
						right_operand = atoi(r->value);

					}
 
				}else{

					left_operand = atoi(left->content);
					right_operand = atoi(right->content);

				}

			
				if( strncmp(t->type, "T_PLUS", 6) == 0 ){

					sprintf(answer,"%d", left_operand + right_operand);
					push(STACK, new_token("T_CONSTANT", answer));

				}else if( strncmp(t->type, "T_MINUS", 7) == 0 ){

					sprintf(answer,"%d", left_operand - right_operand);
					push(STACK, new_token("T_CONSTANT", answer));

				}else if( strncmp(t->type, "T_ASTERIX", 9) == 0 ){

					sprintf(answer,"%d", left_operand * right_operand);
					push(STACK, new_token("T_CONSTANT", answer));

				}else if( strncmp(t->type,"T_FSLASH", 8) == 0 ){

					sprintf(answer,"%d", left_operand / right_operand);
					push(STACK, new_token("T_CONSTANT", answer));
				}
			}

			t = t->next_token;

		}

	}
	return STACK->top->content;

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
token_list* infix_to_postfix(token_list *list){

	reverse_token_list(list);

	token *temp = new_token("T_LPAREN", "(");

	temp->next_token = list->first_token;
	list->first_token->prev_token = temp;
	list->first_token = temp;

	temp = new_token("T_RPAREN", ")");

	list->last_token->next_token = temp;
	temp->prev_token = list->last_token;
	list->last_token = temp;

	token *t = list->first_token;

	token_list *postfix_expression = new_token_list();

	stack *STACK = new_stack();

	//infix to postfix

	while( t != NULL ){

		if( strncmp(t->type,"T_CONSTANT",11) == 0 ||
			strncmp(t->type,"T_IDENTIFIER", 12) == 0 ||
			strncmp(t->type,"T_STRING", 8) == 0){

			add_new_token(postfix_expression, new_token(t->type, t->content));

		}else if( strncmp(t->type,"T_LPAREN", 8) == 0 ){

			push(STACK, t);		

		}else if( strncmp(t->type,"T_RPAREN", 8) == 0 ){

			while( strncmp( get_stack_top(STACK)->type,"T_LPAREN",8) != 0){

				add_new_token(postfix_expression, new_token(get_stack_top(STACK)->type, get_stack_top(STACK)->content));
				pop(STACK);

			}

			pop(STACK);

		}

		else{
			if( is_operator(t) == 1 ){

				while(check_precedence(t) <= check_precedence(get_stack_top(STACK))){

					add_new_token(postfix_expression, get_stack_top(STACK));
					pop(STACK);

				}

				push(STACK, t);

			}
		}

		t = t->next_token;
	}
		
	free(STACK);

	return postfix_expression;

}

//check if postfix expression is valid or not
int is_postfix_valid(token_list* list){

	if(list->token_count == 1){

		return 1;

	}

	int operand_count = 0, operator_count = 0;
	
	token *t = list->first_token;

	while(t != NULL){

		if( is_operator(t) == 1 ){

			operator_count++;

		}else{

			operand_count++;

		}

		t = t->next_token;

	}

	//postfix expression validation
	//1 -> first two elements are operand
	//2 -> last element is always an operator
	//3 -> for every n operands there are n-1 operators

	if( 
		is_operator(list->first_token) == 0 &&
		is_operator(list->first_token->next_token) == 0 &&
		operand_count == operator_count+1 &&
		is_operator(list->last_token) == 1
	  ){

		return 1;

	}
	
	return 0;
	
}

//print token list
void print_token_list(token_list *list){

	token *t = list->first_token;

	while(t != NULL){
		fprintf(stdout,"content->%s, type->%s\n", t->content, t->type);
		t = t->next_token;
	}

}
