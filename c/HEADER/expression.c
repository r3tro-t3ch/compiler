#include <stdlib.h>
#include "expression.h"
#include <string.h>
#include <stdio.h>
#include "symbol_table.h"
#include <ctype.h>

int is_expression_token(token *t){

	if( strncmp(t->type, "T_IDENTIFIER", 12) == 0 ||
		strncmp(t->type, "T_CONSTANT", 10) == 0 ||
		strncmp(t->type, "T_PLUS", 6) == 0 ||
		strncmp(t->type, "T_MINUS", 7) == 0 ||
		strncmp(t->type, "T_ASTERIX", 9) == 0 ||
		strncmp(t->type, "T_FSLASH", 8) == 0 ||
		strncmp(t->type, "T_MOD", 5) == 0 ||
		strncmp(t->type, "T_STRING", 8) == 0 ||
		strncmp(t->type, "T_KEYWORD", 9) == 0
	  ){

		if(strncmp(t->type, "T_KEYWORD", 9) == 0){

			if( strncmp(t->content,"HIGH", 4) == 0 || 
				strncmp(t->content, "LOW", 3) == 0 ){

				return 1;

			}

		}

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

//check if given token in a logical expression token or not
int is_logical_expression_token(token *t){

	if( strncmp(t->type, "T_IDENTIFIER", 12) == 0 ||
		strncmp(t->type, "T_CONSTANT", 10) == 0 ||
		strncmp(t->type, "T_KEYWORD", 9) == 0 ||
		strncmp(t->type, "T_STRING", 8) == 0 || 
		is_logical_operator(t) == 1 
	  ){

		if(strncmp(t->type, "T_KEYWORD", 9) == 0){
	
			if( strncmp(t->content,"HIGH", 4) == 0 || 
				strncmp(t->content, "LOW", 3) == 0 ){

				return 1;

			}

		}
		
		return 1;

	}

	return 0;

}

//check if operator is a logical operator
int is_logical_operator(token *t){

	if( strncmp(t->type, "T_EE", 4) == 0 ||
		strncmp(t->type, "T_NE", 4) == 0 ||
		strncmp(t->type, "T_GE", 4) == 0 ||
		strncmp(t->type, "T_LE", 4) == 0 ||
		strncmp(t->type, "T_GREATER", 9) == 0 ||
		strncmp(t->type, "T_LESSER", 8 ) == 0 ||
		strncmp(t->type, "T_LOR", 5) == 0 ||
		strncmp(t->type, "T_LAND", 6) == 0 ||
		strncmp(t->type, "T_BOR", 5) == 0 ||
		strncmp(t->type, "T_BAND", 6) == 0 ||
		strncmp(t->type, "T_LNOT", 6) == 0
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

//create new operand
operand *new_operand(char *value, char *data_type){

	operand *o = calloc(1, sizeof(operand));
	o->value = value;

	if( strncmp(data_type, "T_STRING", 8) == 0 ||
		strncmp(data_type, "STRING", 6) == 0 ){

		o->data_type = "STRING";

	}else if( strncmp(data_type, "T_BOOLEAN", 9) == 0 ){

		o->data_type = "BOOL";

	}else{

		o->data_type = "NUMBER";

	}

	return o;

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
		s->stack_size++;

	}else{
	
		t->prev_token = s->top;
		s->top->next_token = t;
		s->top = t;
		s->stack_size++;

	}
}

//check if a string is present in in given expression
int string_present(token *list, symbol_table *table){

	//print_symbol_table(table);

	int flag = 0;

	token *t = list;

	while(t != NULL){
	
//		printf("token -> %s \n", t->content);

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

//check for undeclared var in expr
int is_undeclared_var_present(token_list *list, symbol_table *table, error_list *err_list, int ast_node_index){

	int FLAG = 0;

	symbol *s;

	token *t = list->first_token;

	while(t != NULL){

		if( strncmp(t->type, "T_IDENTIFIER", 12) == 0 ){

			s = search_symbol(table, t->content);

			if( s == NULL ){

				FLAG = 1;
			
				size_t err_msg_len = strlen(t->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

				char *err_msg = calloc(err_msg_len, sizeof(char));

				snprintf(err_msg, err_msg_len,
						 "variable %s is not declared\n",
						 t->content);

				add_new_error(err_list, new_error(err_msg, ast_node_index));


				break;
			}

		}
		t = t->next_token;

	}

	return FLAG;

}

//checking if given expression is a simple expression or not
int is_simple_expr(token_list *list){

	if(list->token_count == 3){
		return 1;
	}

	return 0;

}

//checking if there is any var defined inside asm
int is_DSEG(token_list *list, symbol_table *table){

	token *t = list->first_token;

	int flag = 0;

	while(t != NULL){

		if( strncmp(t->type, "T_IDENTIFIER", 12) == 0){

			symbol *s = search_symbol(table, t->content);

			if(s != NULL){

				if( strncmp(s->data_type, "DSEG_VAR", 8) == 0){

					flag = 1;
					break;

				}

			}

		}
	
		t = t->next_token;

	}

	return flag;
}

//evaluate expression tree and return the answer
char* evaluate_expression_ast(token_list *node, error_list *err_list, symbol_table *table , size_t line, int *STRING_FLAG, symbol_table *parent_symbol_table){

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
					strncmp(t->type, "T_STRING", 7) == 0 ||
					strncmp(t->type,"T_KEYWORD", 9) == 0){

	
					if( strncmp(t->content, "HIGH", 4) == 0 ){

							push(STACK, new_token("T_CONSTANT", "1"));

					}else if( strncmp(t->content, "LOW", 3) == 0 ){

							push(STACK, new_token("T_CONSTANT", "0"));

					}else{
						
						push(STACK, t);

					}

				}else if( strncmp(t->type, "T_IDENTIFIER", 12) == 0 ){

					symbol *temp = search_symbol(table, t->content);

					symbol *parent_temp = NULL;

					if( parent_symbol_table != NULL )
						parent_temp = search_symbol(parent_symbol_table, t->content);

					if(temp != NULL || parent_temp != NULL){

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
							
							if(s == NULL){

								s = search_symbol(parent_symbol_table, left->content);

							}
							
							left_operand = s->value;
							right_operand = right->content;

						}else if( strncmp(right->type, "T_IDENTIFIER", 12) == 0 &&
						  	      strncmp(left->type, "T_IDENTIFIER", 12) != 0){

							symbol *s = search_symbol(table, right->content);

							if(s == NULL){

								s = search_symbol(parent_symbol_table, right->content);

							}

							right_operand = s->value;
							left_operand = left->content;

						}else{

							symbol *l = search_symbol(table, left->content);
							symbol *r = search_symbol(table, right->content);

							if( l == NULL ){

								l = search_symbol(parent_symbol_table, left->content);

							}

							if( r == NULL ){

								r = search_symbol(parent_symbol_table, right->content);

							}

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

				if( temp == NULL ){

					temp = search_symbol(parent_symbol_table, t->content);

				}

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

						if( s == NULL ){

							s = search_symbol(parent_symbol_table, left->content);

						}

						left_operand = atoi(s->value);
						right_operand = atoi(right->content);

					}else if( strncmp(right->type, "T_IDENTIFIER", 12) == 0 &&
					  	      strncmp(left->type, "T_IDENTIFIER", 12) != 0){

						symbol *s = search_symbol(table, right->content);

						if( s == NULL ){

							s = search_symbol(parent_symbol_table, right->content);

						}

						right_operand = atoi(s->value);
						left_operand = atoi(left->content);

					}else{

						symbol *l = search_symbol(table, left->content);
						symbol *r = search_symbol(table, right->content);

						if( l == NULL ){

							l = search_symbol(parent_symbol_table, left->content);

						}

						if( r == NULL ){

							r = search_symbol(parent_symbol_table, right->content);

						}
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

					sprintf(answer,"%d", right_operand - left_operand);
					push(STACK, new_token("T_CONSTANT", answer));

				}else if( strncmp(t->type, "T_ASTERIX", 9) == 0 ){

					sprintf(answer,"%d", left_operand * right_operand);
					push(STACK, new_token("T_CONSTANT", answer));

				}else if( strncmp(t->type,"T_FSLASH", 8) == 0 ){

					sprintf(answer,"%d", right_operand / left_operand);
					push(STACK, new_token("T_CONSTANT", answer));
				}
			}

			t = t->next_token;

		}

	}
	return STACK->top->content;

}

//evaluate expression tree and return the answer
char* evaluate_predetermined_logical_expression(token_list *node, error_list *err_list, symbol_table *table , size_t line, symbol_table *parent_symbol_table){

	token *t = node->first_token;

	stack *STACK = new_stack();

	int error_flag = 0;
	
	while( t != NULL){

		if( strncmp(t->content, "HIGH", 4) == 0 ){

			push(STACK, new_token("T_CONSTANT", "1"));

		}else if( strncmp(t->content, "LOW", 3) == 0 ){

			push(STACK, new_token("T_CONSTANT", "0"));

		}else if( is_logical_operator(t) != 1 ){

			//operand
			push(STACK, t);
		
		}else{

			//operators

			token *right_operand = pop(STACK);	
			token *left_operand = pop(STACK);	
			
			operand *left, *right;


			if( strncmp(left_operand->type, "T_IDENTIFIER", 12) == 0 ||
				strncmp(right_operand->type, "T_IDENTIFIER", 12) == 0){

				if( strncmp(left_operand->type, "T_IDENTIFIER", 12) == 0 &&
					strncmp(right_operand->type, "T_IDENTIFIER", 12) != 0 ){

					symbol *s = search_symbol(table, left_operand->content);

					symbol *parent_s = NULL ;

					if( parent_symbol_table != NULL ){
						parent_s = search_symbol(parent_symbol_table, left_operand->content);
					}

					if( s != NULL  && parent_s == NULL){

						left = new_operand(s->value, s->data_type);
						right = new_operand(right_operand->content, right_operand->type);

					}else if( parent_s != NULL  && s == NULL){

						left = new_operand(parent_s->value, parent_s->data_type);
						right = new_operand(right_operand->content, right_operand->type);

					}else{

						//variable not present error

						size_t err_msg_len = strlen(left_operand->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

						char *err_msg = calloc(err_msg_len, sizeof(char));

						snprintf(err_msg, err_msg_len,
								 "variable %s is not declared\n",
								 left_operand->content);

						add_new_error(err_list, new_error(err_msg, line));

						error_flag = 1;
					}

				}else if(
					strncmp(left_operand->type, "T_IDENTIFIER", 12) != 0 &&
					strncmp(right_operand->type, "T_IDENTIFIER", 12) == 0){

					symbol *s = search_symbol(table, right_operand->content);

					symbol *parent_s = NULL ;

					if( parent_symbol_table != NULL ){
						parent_s = search_symbol(parent_symbol_table, left_operand->content);
					}

					if( s != NULL && parent_s == NULL ){

						left = new_operand(left_operand->content, left_operand->type);
						right = new_operand(s->value, s->data_type);

					}else if( parent_s != NULL  && s == NULL){

						left = new_operand(left_operand->content, left_operand->type);
						right = new_operand(parent_s->value, parent_s->data_type);

					}else{

						//variable not present error
						size_t err_msg_len = strlen(right_operand->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

						char *err_msg = calloc(err_msg_len, sizeof(char));

						snprintf(err_msg, err_msg_len,
								 "variable %s is not declared\n",
								 right_operand->content);

						add_new_error(err_list, new_error(err_msg, line));

						error_flag = 1;
					}
				}else{

					symbol *l = search_symbol(table, left_operand->content);
					symbol *r = search_symbol(table, right_operand->content);

					symbol *parent_l = NULL;
					symbol *parent_r = NULL;

					if(parent_symbol_table != NULL){

						parent_l = search_symbol(parent_symbol_table, left_operand->content);
						parent_r = search_symbol(parent_symbol_table, right_operand->content);

					}

					if( (l != NULL && r != NULL) || (parent_l != NULL && parent_r != NULL) ||
						(l != NULL && parent_r != NULL) || (parent_l != NULL && r != NULL)){

						if( (l != NULL && r != NULL) && (parent_l == NULL && parent_r == NULL) ){

							left = new_operand(l->value, l->data_type);
							right = new_operand(r->value, r->data_type);
						
						}else if( (l == NULL && r == NULL) && (parent_l != NULL && parent_r != NULL) ){

							left = new_operand(parent_l->value, parent_l->data_type);
							right = new_operand(parent_r->value, parent_r->data_type);
						
						}else if( ( l != NULL && parent_r != NULL) && (parent_l == NULL && r == NULL) ){
							
							left = new_operand(l->value, l->data_type);
							right = new_operand(parent_r->value, parent_r->data_type);

						}else if((l == NULL && parent_r == NULL) && (parent_l != NULL && r != NULL)){

							left = new_operand(parent_l->value, parent_l->data_type);
							right = new_operand(r->value, r->data_type);

						}

					}else{

						//variable not present error
						if( l == NULL && r != NULL ){

							size_t err_msg_len = strlen(left_operand->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

							char *err_msg = calloc(err_msg_len, sizeof(char));

							snprintf(err_msg, err_msg_len,
									 "variable %s is not declared\n",
									 left_operand->content);

							add_new_error(err_list, new_error(err_msg, line));

						}else if( l != NULL  && r == NULL){
	
							size_t err_msg_len = strlen(right_operand->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

							char *err_msg = calloc(err_msg_len, sizeof(char));

							snprintf(err_msg, err_msg_len,
									 "variable %s is not declared\n",
									 right_operand->content);

							add_new_error(err_list, new_error(err_msg, line));

						}else{

							size_t err_msg_len = strlen(left_operand->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

							char *err_msg = calloc(err_msg_len, sizeof(char));

							snprintf(err_msg, err_msg_len,
									 "variable %s is not declared\n",
									 left_operand->content);

							add_new_error(err_list, new_error(err_msg, line));

							err_msg_len = strlen(right_operand->content) + ERR_MSG_VAR_NOT_PRESENT_LEN;

							err_msg = calloc(err_msg_len, sizeof(char));

							snprintf(err_msg, err_msg_len,
									 "variable %s is not declared\n",
									 right_operand->content);

							add_new_error(err_list, new_error(err_msg, line));

						}

						error_flag = 1;
					}

				}

			}else{

				//both constants
				left = new_operand(left_operand->content, left_operand->type);
				right = new_operand(right_operand->content, right_operand->type);

			}

			if(error_flag == 1){
				continue;
			}

			if( strncmp(t->type, "T_EE", 4) == 0 ){
			
				//"=="
				if( strncmp(left->data_type, right->data_type, strlen(left->data_type)) == 0 && 
					strncmp(left->value, right->value, strlen(left->value)) == 0 ){

					push(STACK, new_token("T_BOOLEAN","true"));

				}else{
	
					push(STACK, new_token("T_BOOLEAN","false"));

				}

			}else if( strncmp(t->type, "T_GREATER", 9) == 0 ){

				//">"
				if( strncmp(left->data_type, "NUMBER", strlen(left->data_type)) == 0 &&
					strncmp(left->data_type, "NUMBER", strlen(left->data_type)) == 0){

					int l = atoi(left->value);	
					int r = atoi(right->value);	
	
					if( l > r ){
					
						push(STACK, new_token("T_BOOLEAN","true"));

					}else{

						push(STACK, new_token("T_BOOLEAN","false"));

					}

				}else{

					add_new_error(err_list, new_error("cannot compare numbers to bool or strings", line));
					error_flag = 1;
					continue;

				}

			}else if( strncmp(t->type, "T_LESSER", 8) == 0 ){

				//"<"
				if( strncmp(left->data_type, "NUMBER", strlen(left->data_type)) == 0 &&
					strncmp(left->data_type, "NUMBER", strlen(left->data_type)) == 0){

					int l = atoi(left->value);	
					int r = atoi(right->value);	
	
					printf("\nl -> %d, r-> %d \n\n", l, r);
					if( l < r ){
				
						push(STACK, new_token("T_BOOLEAN","true"));

					}else{

						push(STACK, new_token("T_BOOLEAN","false"));

					}

				}else{

					add_new_error(err_list, new_error("cannot compare numbers to bool or strings", line));
					error_flag = 1;
					continue;

				}
			}else if( strncmp(t->type, "T_GE", 4) == 0 ){

				//">="
				if( strncmp(left->data_type, "NUMBER", strlen(left->data_type)) == 0 &&
					strncmp(left->data_type, "NUMBER", strlen(left->data_type)) == 0){

					int l = atoi(left->value);	
					int r = atoi(right->value);	
	
					if( l >= r ){
					
						push(STACK, new_token("T_BOOLEAN","true"));

					}else{

						push(STACK, new_token("T_BOOLEAN","false"));

					}

				}else{

					add_new_error(err_list, new_error("cannot compare numbers to bool or strings", line));
					error_flag = 1;
					continue;

				}
			}else if( strncmp(t->type, "T_LE", 4) == 0 ){

				//"<="
				if( strncmp(left->data_type, "NUMBER", strlen(left->data_type)) == 0 &&
					strncmp(left->data_type, "NUMBER", strlen(left->data_type)) == 0){

					int l = atoi(left->value);	
					int r = atoi(right->value);	
	
					if( l <= r ){
					
						push(STACK, new_token("T_BOOLEAN","true"));

					}else{

						push(STACK, new_token("T_BOOLEAN","false"));

					}

				}else{

					add_new_error(err_list, new_error("cannot compare numbers to bool or strings", line));
					error_flag = 1;
					continue;

				}

			}else if( strncmp(t->type, "T_NE", 4) == 0 ){

				//"!="
				if( strncmp(left->data_type, right->data_type, strlen(left->data_type)) != 0 || 
					strncmp(left->value, right->value, strlen(left->value)) != 0 ){

					push(STACK, new_token("T_BOOLEAN","true"));

				}else{

					push(STACK, new_token("T_BOOLEAN","false"));

				}
				
			}else if( strncmp(t->type, "T_LAND", 6) == 0 ){

				//"&&"
				if( strncmp( left->value, "true", 4) == 0 && 
					strncmp(right->value, "true", 4) == 0 ){
		
						push(STACK, new_token("T_BOOLEAN","true"));

				}else{

					push(STACK, new_token("T_BOOLEAN","false"));

				}


			}else if( strncmp(t->type, "T_LOR", 5) == 0 ){

				//"||"
				if( strncmp( left->value, "true", 4) == 0 ||
						strncmp(right->value, "true", 4) == 0){
	
						push(STACK, new_token("T_BOOLEAN","true"));

				}else{

					push(STACK, new_token("T_BOOLEAN","false"));

				}

			}


		}

		t = t->next_token;

	}

	if(error_flag == 1){
		return NULL;
	}

	return STACK->top->content;

}

//evaluate expression tree and return the answer
char* evaluate_logical_expression(token_list *node, error_list *err_list, symbol_table *table , size_t line, int *STRING_FLAG);


//check precedence of operator
int check_precedence(token *t){

	if(
		strncmp(t->type,"T_LNOT", 6) == 0
	  ){
		return 10;
	}else if(	
		strncmp(t->type, "T_ASTERIX", 9) == 0 ||
		strncmp(t->type, "T_FSLASH", 8) == 0 ||
		strncmp(t->type, "T_MOD", 5) == 0 
	  ){
		return 9;
	}else if(
		strncmp(t->type, "T_PLUS", 6) == 0 ||
		strncmp(t->type, "T_MINUS", 7) == 0
		){
		return 8;
	}else if(
		strncmp(t->type,"T_LE", 4) == 0 ||
		strncmp(t->type,"T_GE", 4) == 0 ||
		strncmp(t->type,"T_GREATER", 9) == 0 ||
		strncmp(t->type,"T_LESSER", 8) == 0 
		){

		return 7;

	}else if(
		strncmp(t->type,"T_EE", 4) == 0 ||
		strncmp(t->type,"T_NE", 4) == 0
		){
		return 6;
	}else if(
		strncmp(t->type,"T_BAND", 6) == 0
		){
		return 5;
	}else if(
		strncmp(t->type,"T_BOR", 5) == 0
		){
		return 4;
	}else if(
		strncmp(t->type,"T_LAND", 6) == 0
		){
		return 3;
	}else if(
		strncmp(t->type,"T_LOR", 5) == 0
		){
		return 2; 
	}else{
		return 1;
	}

}

//infix to prefix
token_list* infix_to_postfix(token_list *list){

	//reverse_token_list(list);

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
			strncmp(t->type,"T_STRING", 8) == 0 ||
			strncmp(t->type, "T_KEYWORD", 9) == 0){
		

				if( strncmp(t->content, "HIGH", 4) == 0 ){

					add_new_token(postfix_expression, new_token("T_CONSTANT", "1"));

					}else if( strncmp(t->content, "LOW", 3) == 0 ){

					add_new_token(postfix_expression, new_token("T_CONSTANT", "0"));

				}else{
			
					add_new_token(postfix_expression, new_token(t->type, t->content));
				
				}

		}else if( strncmp(t->type,"T_LPAREN", 8) == 0 ){

			push(STACK, t);		

		}else if( strncmp(t->type,"T_RPAREN", 8) == 0 ){

			while( strncmp( get_stack_top(STACK)->type,"T_LPAREN",8) != 0){

				add_new_token(postfix_expression, new_token(get_stack_top(STACK)->type, get_stack_top(STACK)->content));
				pop(STACK);

			}

			pop(STACK);

		}else{
			if( is_operator(t) == 1 || is_logical_operator(t) == 1 ){

				while( check_precedence(t) <= check_precedence(get_stack_top(STACK)) ){

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

//postfix to infix
token_list* postfix_to_infix(token_list *list){

	char *infix_expr;

	token *t = list->first_token;

	stack *s = new_stack();

	while( t != NULL ){

		//check if given operatort is an operand
		if( is_operator(t) == 0 ){

			//if it is an operand push it ot stack
			push(s, t);

		}else{

/*
			if(counter > 0){

			token *r = pop(s);
			token *l = pop(s);

			right = new_token(r->type, r->content);
			left = new_token(l->type, l->content);
			op = new_token(t->type, t->content);

			}else{

				right = pop(s);		
				left = pop(s);		
			op = new_token(t->type, t->content);

			}

			//right->next_token = r->next_token;

			if(counter == 0){

				right->next_token = NULL;

			}

			left->next_token = op;
			op->prev_token = left;
			op->next_token = right;
			right->prev_token = op;

			push(s, left);
*/

			token *right = pop(s);
			token *left = pop(s);

			infix_expr = calloc(list->token_count, sizeof(char));

			strncat(infix_expr, left->content, strlen(left->content));
			strncat(infix_expr, " ", 2);
			strncat(infix_expr, t->content, strlen(t->content));
			strncat(infix_expr, " ", 2);
			strncat(infix_expr, right->content, strlen(right->content));
			strncat(infix_expr, " ", 2);

			token *temp = new_token("T_EXPR", infix_expr);


			push(s,temp);


		}

		t = t->next_token;

	}

	//printf("%s ", infix_expr);

	//printf("\n");
	return str_to_token_list(infix_expr);

}

//check if postfix expression is valid or not
int is_postfix_valid(token_list* list){

	if(list->token_count == 1){

		return 1;

	}

	int operand_count = 0, operator_count = 0;
	
	token *t = list->first_token;

	while(t != NULL){

		if( is_operator(t) == 1 || is_logical_operator(t) == 1 ){

			operator_count++;

		}else if(
				strncmp(t->content, "HIGH", 4) == 0 ||
				strncmp(t->content, "LOW", 3) == 0
				){

			operand_count++;

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

//get identifer from string list
//char* get_identifier_from_string(char *expr,){



//}

//convert string to token list
token_list* str_to_token_list(char *expr){

	token_list* list = new_token_list();

	for(size_t i = 0; i < strlen(expr); i++){

		if( isalnum(expr[i]) ){
	
			char *identifier = calloc(1,sizeof(char));
	
			int j = 0;

			while( isalnum(expr[i]) ){

				identifier = realloc(identifier, j + sizeof(char));
        		identifier[j] = expr[i];
        		j++;
      			i++;

			}

			if( isdigit(*identifier)){
			
				add_new_token(list, new_token("T_CONSTANT", identifier));
			
			}else{

				add_new_token(list, new_token("T_IDENTIFIER", identifier));

			}
		}

		if(expr[i] == ' '){
			continue;
		}

		if(expr[i] == '+'){

			add_new_token(list, new_token("T_PLUS", "+"));

		}else if(expr[i] == '-'){

			add_new_token(list, new_token("T_MINUS", "-"));

		}else if(expr[i] == '*'){

			add_new_token(list, new_token("T_ASTERIX", "*"));

		}else if(expr[i] == '/'){

			add_new_token(list, new_token("T_FSLASH", "/"));

		}

	}

	return list;

}

//print token list
void print_token_list(token_list *list){

	token *t = list->first_token;

	while(t != NULL){
		fprintf(stdout,"content->%s, type->%s\n", t->content, t->type);
		t = t->next_token;
	}

}
